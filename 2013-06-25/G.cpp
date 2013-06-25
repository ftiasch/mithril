#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()

const int N = 200000;

int n, m, x[N], y[N], c[N];

void relabel(int *xs, int n) {
    std::vector <int> values;
    for (int i = 0; i < n; ++ i) {
        values.push_back(xs[i]);
    }
    std::sort(ALL(values));
    values.erase(std::unique(ALL(values)), values.end());
    for (int i = 0; i < n; ++ i) {
        xs[i] = std::lower_bound(ALL(values), xs[i]) - values.begin();
    }
}

struct Point {
    int x, y, c;

    Point() {}
    Point(int x, int y, int c) : x(x), y(y), c(c) {}
};

Point points[N];

bool by_x(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool by_y(const Point &a, const Point &b) {
    return a.y < b.y;
}

struct FenwichTree {
    int count[N];

    void clear() {
        memset(count, 0, sizeof(count));
    }

    void add(int k) {
        for (; k < n; k += ~k & k + 1) {
            count[k] ++;
        }
    }

    int ask(int k) {
        int ret = 0;
        for (; k >= 0; k -= ~k & k + 1) {
            ret += count[k];
        }
        return ret;
    }
} fenwich;

std::set <int> color_sets[N];

int find_next(std::set <int> &set, int key) {
    std::set <int> :: iterator iter = set.lower_bound(key);
    if (iter == set.end()) {
        return n;
    }
    return *iter;
}

int find_prev(std::set <int> &set, int key) {
    std::set <int> :: iterator iter = set.upper_bound(key);
    if (iter == set.begin()) {
        return -1;
    }
    iter --;
    return *iter;
}

int last[N];

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d%d", x + i, y + i, c + i);
        }
        relabel(x, n);
        relabel(y, n);
        relabel(c, n);
        for (int i = 0; i < n; ++ i) {
            points[i] = Point(x[i], y[i], c[i]);
        }
        int answer = 0;
        std::sort(points, points + n, by_y);
        fenwich.clear();
        for (int i = 0; i < m; ++ i) {
            color_sets[i].clear();
        }
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && points[i].y == points[j].y) {
                j ++;
            }
            for (int k = i; k < j; ++ k) {
                Point &p = points[k];
                int x_1 = find_prev(color_sets[p.c], p.x) + 1;
                int x_2 = find_next(color_sets[p.c], p.x) - 1;
                if (x_1 <= x_2) {
                    answer = std::max(answer, fenwich.ask(x_2) - fenwich.ask(x_1 - 1));
                }
            }
            for (int k = i; k < j; ++ k) {
                Point &p = points[k];
                fenwich.add(p.x);
                color_sets[p.c].insert(p.x);
            }
            i = j;
        }
        std::sort(points, points + n, by_x);
        memset(last, -1, sizeof(last));
        for (int i = 0; i < n; ++ i) {
            Point &p = points[i];
            if (last[p.c] + 1 <= p.x - 1) {
                answer = std::max(answer, fenwich.ask(p.x - 1) - fenwich.ask(last[p.c]));
            }
            last[p.c] = p.x;
        }
        for (int i = 0; i < m; ++ i) {
            if (last[i] + 1 <= n - 1) {
                answer = std::max(answer, fenwich.ask(n - 1) - fenwich.ask(last[i]));
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}
