#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double pi = acos(-1.0);
const double EPS = 1e-8;

inline double sqr(double x)
{
    return x * x;
}

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
    Point(double x, double y): x(x), y(y){}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    double norm() {
        return sqrt(x * x + y * y);
    }
};

inline Point operator + (const Point &a, const Point &b)
{
    return Point(a.x + b.x, a.y + b.y);
}

inline Point operator - (const Point &a, const Point &b)
{
    return Point(a.x - b.x, a.y - b.y);
}

inline Point operator / (const Point &a, const double &b)
{
    return Point(a.x / b, a.y / b);
}

inline double dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

inline double det(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

inline bool pointOnSegment(Point o, Point l, Point r)
{
    double length = (o - l).norm();
    if (signum(length) == 0) {
        return true;
    }
    if (signum(det(o - l, r - l) / length) != 0) {
        return false;
    }
    return signum(dot(o - l, o - r) / length) <= 0;
}

Point circleCenter(Point p0, Point p1, Point p2)
{
    double a1 = p1.x - p0.x, b1 = p1.y - p0.y, c1 = (sqr(a1) + sqr(b1)) / 2;
    double a2 = p2.x - p0.x, b2 = p2.y - p0.y, c2 = (sqr(a2) + sqr(b2)) / 2;
    double d = a1 * b2 - a2 * b1;
    return Point(p0.x + (c1 * b2 - c2 * b1) / d, p0.y + (a1 * c2 - a2 * c1) /d);
}

bool check(Point o, double r, vector<Point> &p, int n)
{
//printf("check: (%lf, %lf) %lf\n", o.x, o.y, r);
    bool valid = true;
    for (int k = 0; k < p.size() && valid; ++ k) {
        double d = (o - p[k]).norm();
        int sign = signum(d - r);
        if (sign == 0) {
            continue;
        }
        valid &= (sign == -1) == (k < n);
    }
    return valid;
}

bool solve(Point a[], Point b[], int n, int m)
{
    vector<Point> p;
    for (int i = 0; i < n; ++ i) {
        p.push_back(a[i]);
    }
    for (int i = 0; i < m; ++ i) {
        p.push_back(b[i]);
    }
    for (int i = 0; i < p.size(); ++ i) {
        for (int j = 0; j < p.size(); ++ j) {
            if (i == j) {
                continue;
            }
            Point x = p[i], y = p[j];
            double length = (x - y).norm();
            vector<Point> left, right;
            
            double mini = -1e100;
            int choice = -1;
            for (int k = 0; k < p.size(); ++ k) {
                if (i == k || j == k) {
                    continue;
                }
                int side = signum(det(y - x, p[k] - x) / length);
                if (side == 0) {
                    if (k < n && !pointOnSegment(p[k], x, y)) {
                        choice = -2;
                        break;
                    }
                } else if (side == 1) {
                    double angle = dot(x - p[k], y - p[k]) / (x - p[k]).norm() / (y - p[k]).norm();
                    if (k < n) {
                        if (angle > mini) {
                            mini = angle;
                            choice = k;
                        }
                    }
                }
            }
            
            if (choice != -2) {
                Point o = (p[i] + p[j]) / 2.0;
                double r = (o - p[i]).norm();
                if (check(o, r, p, n)) {
                    puts("YES");
                    printf("%.10f %.10f %.10f\n", o.x, o.y, r);
                    return true;
                }
            }
            
            if (choice >= 0) {
                Point o = circleCenter(p[i], p[j], p[choice]);
                double r = (o - p[i]).norm();
                if (check(o, r, p, n)) {
                    puts("YES");
                    printf("%.10f %.10f %.10f\n", o.x, o.y, r);
                    return true;
                }
            }
        }
    }
    return false;
}

const int maxn = 120;

int n, m;
Point a[maxn], b[maxn];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        a[i].read();
    }
    for (int i = 0; i < m; ++ i) {
        b[i].read();
    }
    if (!solve(a, b, n, m) && !solve(b, a, m, n)) {
        puts("NO");
    }
    return 0;
}

