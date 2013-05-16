#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const double eps = 1e-7;

struct Point
{
    double x, y;

    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    Point &operator+=(const Point &o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    Point &operator-=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    Point &operator*=(double scale) {
        x *= scale;
        y *= scale;
        return *this;
    }

    Point &operator/=(double scale) {
        x /= scale;
        y /= scale;
        return *this;
    }

    bool operator==(const Point &o) const {
        return fabs(x - o.x) < eps && fabs(y - o.y) < eps;
    }

    void read() {
        scanf("%lf%lf", &x, &y);
    }

    double norm() const {
        return sqrt(x * x + y * y);
    }

    Point normalize() const ;
};

Point operator+(Point a, const Point &b)
{
    return a += b;
}

Point operator-(const Point &a)
{
    return Point(-a.x, -a.y);
}

Point operator-(Point a, const Point &b)
{
    return a -= b;
}

Point operator*(Point a, double scale)
{
    return a *= scale;
}

Point operator*(double scale, Point a)
{
    return a *= scale;
}

Point operator/(Point a, double scale)
{
    return a /= scale;
}

Point Point::normalize() const
{
    return *this / norm();
}

inline double dot(double x1, double y1, double x2, double y2)
{
    return x1 * x2 + y1 * y2;
}

inline double dot(const Point &a, const Point &b, const Point &c)
{
    return dot(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

inline double det(double x1, double y1, double x2, double y2)
{
    return x1 * y2 - x2 * y1;
}

inline double det(const Point &a, const Point &b, const Point &c)
{
    return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

// minimize dist(a,x) + dist(x,b)
// a and b on same side of (l, r)
// x on segment (l, r)
inline void solve(const Point &a, const Point &l, Point &x, const Point &r, const Point &b)
{
    if (l == r) {
        x = (l + r) / 2;
        return;
    }
    Point a2 = (dot(l, r, a) / dot(l, r, r)) * (r - l) + l;
    a2 = a2 * 2 - a;
    double za = det(l, r, a2), zb = det(l, r, b);
    if (fabs(zb - za) < eps) {
        x = (l + r) / 2;
        return ;
    }
    x = (a2 * zb - b * za) / (zb - za);
    if (dot(l, r, x) < 0) {
        x = l;
    } else if (dot(r, l, x) < 0) {
        x = r;
    }
}

const int maxn = 1024;

int n;
Point start;
Point a[maxn], b[maxn], c[maxn];
double d[maxn];

Point x[maxn];

double calc()
{
    double ret = (start - x[0]).norm();
    for (int i = 0; i < n; i++) {
        ret += d[i];
        ret += (x[i] + (b[i] - c[i]) - (i + 1 == n ? start : x[i + 1])).norm();
    }
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        a[i].read();
        b[(i + n - 1) % n] = a[i];
    }
    for (int i = 0; i < n; i++) {
        scanf("%lf", d + i);
        c[i] = b[i] + (a[i] - b[i]).normalize() * d[i];
        x[i] = (a[i] + c[i]) / 2;
    }
    start.read();
    int cnt = 0;
    while (cnt < 10000000) {
        for (int i = 0; i < n; i++) {
            cnt ++;
            solve(i == 0 ? start : (x[i - 1] + (b[i - 1] - c[i - 1])), a[i], x[i], c[i], (i + 1 == n ? start : x[i + 1]) + (c[i] - b[i]));
        }
    }
    printf("%.10f\n", calc());
}
