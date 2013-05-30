#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()
#define SIZE(v) (int)(v).size()

const double EPS = 1e-8;
const double PI = acos(-1.0);
const double INF = 1e100;
const int TRIES = 50;

// {{{ Point class
inline int signum(double x)
{
    if (x < -EPS) {
        return -1;
    }
    return x > EPS;
}

struct Point
{
    double x, y;
    Point(){}
    Point(double x, double y):x(x), y(y) {
    }
    double norm() const {
        return sqrt(x * x + y * y);
    }
    void read() {
        scanf("%lf%lf", &x, &y);
    }

    bool on(const Point &, const Point &) const;
    bool in(Point *, int) const;
};

bool operator <(const Point &a, const Point &b) {
    if (signum(a.x - b.x) != 0) {
        return signum(a.x - b.x) < 0;
    }
    return signum(a.y - b.y) < 0;
}

inline Point operator + (const Point &a, const Point &b)
{
    return Point(a.x + b.x, a.y + b.y);
}

inline Point operator - (const Point &a, const Point &b)
{
    return Point(a.x - b.x, a.y - b.y);
}

inline Point operator * (const Point &a, const double &b)
{
    return Point(a.x * b, a.y * b);
}

inline Point operator * (double b, const Point &a) 
{
    return Point(b * a.x, b * a.y);
}

inline Point operator / (const Point &a, const double &b)
{
    return Point(a.x / b, a.y / b);
}

inline double det(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

inline double dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

double dist(const Point &a, const Point &b) {
    return (a - b).norm();
}
// }}}

bool Point::on(const Point &a, const Point &b) const {
    const Point &p = *this;
    double length = (a - p).norm();
    if (signum(length) == 0) {
        return true;
    }
    return signum(det(a - p, b - p) / length) == 0 && signum(dot(a - p, b - p) / length) <= 0;
}

bool Point::in(Point *points, int n) const {
    const Point &p = *this;
    int count = 0;
    for (int i = 0; i < n; ++ i) {
        if (p.on(points[i], points[(i + 1) % n])) {
            return false;
        }
        int k = signum(det(points[i] - p, points[(i + 1) % n] - p) / (points[i] - p).norm());
        int d1 = signum(points[i].y - p.y);
        int d2 = signum(points[(i + 1) % n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) {
            count ++;
        }
        if (k < 0 && d2 <= 0 && d1 > 0) {
            count --;
        }
    }
    return count != 0;
}

bool intersect(const Point &a, const Point &b, const Point &c, const Point &d, Point &e) {
    double s_1 = det(b - a, c - a);
    double s_2 = det(b - a, d - a);
    if (signum(s_1 - s_2) == 0) {
        return false;
    }
    e = (s_2 * c - s_1 * d) / (s_2 - s_1);
    return true;
}

const int N = 100 + 2;

int n;
double v_l, v_p;
Point polygon[N];

bool is_reachable(const Point &a, const Point &b, Point *points, int n) {
    std::vector <Point> intersections;
    intersections.push_back(a);
    intersections.push_back(b);
    for (int i = 0; i < n; ++ i) {
        const Point &c = points[i];
        const Point &d = points[(i + 1) % n];
        Point p;
        if (intersect(a, b, c, d, p) && p.on(a, b)) {
            intersections.push_back(p);
        }
    }
    std::sort(ALL(intersections));
    for (int i = 1; i < SIZE(intersections); ++ i) {
        if (((intersections[i - 1] + intersections[i]) / 2.0).in(polygon, n)) {
            return false;
        }
    }
    return true;
}

Point normalize(const Point &p) {
    return p / p.norm();
}

double total_length;
bool reachable[N][N];

double shortest[N];
bool visit[N];

bool check(double t) {
    double delta = fmod(t * v_l, total_length);
    for (int i = 0; i < n; ++ i) {
        if (i != n - 1 && dist(polygon[i], polygon[(i + 1) % n]) < delta) {
            delta -= dist(polygon[i], polygon[(i + 1) % n]);
        } else {
            polygon[n + 1] = polygon[i] + normalize(polygon[(i + 1) % n] - polygon[i]) * delta;
            break;
        }
    }
    for (int i = 0; i <= n; ++ i) {
        reachable[i][n + 1] = reachable[n + 1][i] = is_reachable(polygon[i], polygon[n + 1], polygon, n);
    }
    memset(visit, 0, sizeof(visit));
    std::fill(shortest, shortest + (n + 2), INF);
    shortest[n] = 0;
    while (true) {
        int u = -1;
        for (int i = 0; i <= n + 1; ++ i) {
            if (!visit[i] && (u == -1 || shortest[i] < shortest[u])) {
                u = i;
            }
        }
        if (u == -1 || shortest[u] > 1e50) {
            break;
        }
        visit[u] = true;
        for (int v = 0; v <= n + 1; ++ v) {
            if (reachable[u][v] && shortest[u] + dist(polygon[u], polygon[v]) < shortest[v]) {
                shortest[v] = shortest[u] + dist(polygon[u], polygon[v]);
            }
        }
    }
    return shortest[n + 1] / v_p <= t;
}

int main() {
    int test_count = 0;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++ i) {
            polygon[i].read();
        }
        total_length = 0.0;
        for (int i = 0; i < n; ++ i) {
            total_length += dist(polygon[i], polygon[(i + 1) % n]);
        }
        polygon[n].read();
        for (int i = 0; i <= n; ++ i) {
            for (int j = 0; j <= n; ++ j) {
                reachable[i][j] = is_reachable(polygon[i], polygon[j], polygon, n);
            }
        }
        scanf("%lf%lf", &v_l, &v_p);
        v_l /= 60;
        v_p /= 60;
        double low = 0.0;
        double high = 1e9;
        for (int _ = 0; _ < TRIES; ++ _) {
            double middle = (low + high) / 2.0;
            if (check(middle)) {
                high = middle;
            } else {
                low = middle;
            }
        }
        int answer = (int)(high + 0.5 + EPS);
        printf("Case %d: Time = %d:%02d\n", ++ test_count, answer / 60, answer % 60);
    }
    return 0;
}
