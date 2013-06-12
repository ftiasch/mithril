#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <algorithm>

#define SIZE(v) (int)((v).size())
#define ALL(v) (v).begin(), (v).end()
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

struct Point {
    int x, y, id;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    bool on(const Point &a, const Point &b) {
        return a.x <= x && x <= b.x && a.y <= y && y <= b.y;
    }

    Point &operator -= (const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    double arg() const {
        if (y == 0) {
            return x < 0 ? 0 : 2;
        }
        return y < 0 ? 1 : 3;
    }
};

Point operator - (Point a, const Point &b) {
    return a -= b;
}

bool operator ==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

const int N = 800000;

int n, m;
Point segments[N][2];

bool by_x(const Point &a, const Point &b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool by_y(const Point &a, const Point &b) {
    return a.y < b.y || a.y == b.y && a.x < b.x;
}

int edge_count, first_edge[N], to[N], next_edge[N];
std::vector <Point> points;

void add_edge(int u, int v) {
    to[edge_count] = v;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

int next[N];
bool mark[N];

int main() {
    scanf("%d", &m);
    for (int i = 0; i < m; ++ i) {
        Point a, b;
        scanf("%d%d%d%d",  &a.x, &a.y, &b.x, &b.y);
        segments[i][0] = a;
        segments[i][1] = b;
        std::sort(segments[i], segments[i] + 2, by_x);
        points.push_back(a);
        points.push_back(b);
    }
    std::sort(ALL(points), by_x);
    points.erase(std::unique(ALL(points)), points.end());
    n = SIZE(points);
    for (int i = 0; i < n; ++ i) {
        points[i].id = i;
    }
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
#define ADD(a, b) add_edge(a, b); add_edge(b, a)
    for (int i = 0; i < m; ++ i) {
        if (segments[i][0].x == segments[i][1].x) {
            int j = std::upper_bound(ALL(points), segments[i][0], by_x) - points.begin();
            while (j < n && points[j].on(segments[i][0], segments[i][1])) {
                ADD(points[j - 1].id, points[j].id);
                j ++;
            }
        }
    }
    std::sort(ALL(points), by_y);
    for (int i = 0; i < m; ++ i) {
        if (segments[i][0].y == segments[i][1].y) {
            int j = std::upper_bound(ALL(points), segments[i][0], by_y) - points.begin();
            while (j < n && points[j].on(segments[i][0], segments[i][1])) {
                ADD(points[j - 1].id, points[j].id);
                j ++;
            }
        }
    }
#undef ADD
    std::sort(ALL(points), by_x);
    for (int i = 0; i < n; ++ i) {
        std::vector <std::pair <double, int> > order;
        for (int iter = first_edge[i]; iter != -1; iter = next_edge[iter]) {
            order.push_back(std::make_pair((points[to[iter]] - points[i]).arg(), iter));
        }
        std::sort(ALL(order));
        int t = SIZE(order);
        for (int i = 0; i < t; ++ i) {
            next[order[(i + 1) % t].second ^ 1] = order[i].second;
        }
    }
    std::vector <long double> areas;
    memset(mark, 0, sizeof(mark)); 
    for (int i = 0; i < edge_count; ++ i) {
        if (mark[i]) {
            continue;
        }
        long double now_area = 0;
        int j = i;
        while (!mark[j]) {
            mark[j] = true;
            now_area += det(points[to[j ^ 1]], points[to[j]]);
            j = next[j];
        }
        if (i == j && now_area > 0) {
            areas.push_back(now_area);
        }
    }
    long double total_area = 0;
    foreach (iter, areas) {
        total_area += *iter;
    }
    std::sort(ALL(areas), std::greater <long double>());
    foreach (iter, areas) {
        printf("%.10f\n", (double)(*iter / total_area));
    }
    return 0;
}
