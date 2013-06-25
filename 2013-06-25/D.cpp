#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()

const int N = 200000;

int n, a[N];

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

int prev[N], next[N], occur[N];

int get_id(int l, int r) {
    return l + r | l != r;
}

int delta[N << 1], minimum[N << 1];

void add(int l, int r, int a, int b, int c) {
    if (b < l || r < a) {
        return;
    }
    int id = get_id(l, r);
    if (a <= l && r <= b) {
        delta[id] += c;
        minimum[id] += c;
    } else {
        int m = l + r >> 1;
        add(l, m, a, b, c);
        add(m + 1, r, a, b, c);
        minimum[id] = std::min(minimum[get_id(l, m)], minimum[get_id(m + 1, r)]) + delta[id];
    }
}

const int INF = 1000000000;

int ask(int l, int r, int a, int b) {
    if (b < l || r < a) {
        return INF;
    }
    int id = get_id(l, r);
    if (a <= l && r <= b) {
        return minimum[id];
    }
    int m = l + r >> 1;
    return std::min(ask(l, m, a, b), ask(m + 1, r, a, b)) + delta[id];
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            scanf("%d", a + i);
        }
        relabel(a, n);
        std::fill(occur, occur + n, -1);
        for (int i = 0; i < n; ++ i) {
            prev[i] = occur[a[i]];
            occur[a[i]] = i;
        }
        std::fill(occur, occur + n, n);
        for (int i = n - 1; i >= 0; -- i) {
            next[i] = occur[a[i]];
            occur[a[i]] = i;
        }
        memset(delta, 0, sizeof(delta));
        memset(minimum, 0, sizeof(minimum));
        for (int i = 0; i < n; ++ i) {
            if (prev[i] == -1) {
                add(0, n - 1, i, next[i] - 1, 1);
            }
        }
        bool valid = true;
        for (int i = 0; i < n && valid; ++ i) {
            valid &= ask(0, n - 1, i, n - 1) >= 1;
            add(0, n - 1, i, next[i] - 1, -1);
            if (next[i] < n) {
                add(0, n - 1, next[i], next[next[i]] - 1, 1);
            }
        }
        puts(valid ? "non-boring" : "boring");
    }
    return 0;
}
