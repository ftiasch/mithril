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
    
    void rotate(double angle) {
        double co = cos(angle), si = sin(angle);
        double tx = x, ty = y;
        x = tx * co - ty * si;
        y = tx * si + ty * co;
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

inline double dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
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

inline bool operator <(const Point &a, const Point &b)
{
    return a.x + eps < b.x || a.x < b.x + eps && a.y + eps < b.y;
}

const int maxn = 105;
const int maxT = 45;

int x[maxn], holes[maxn], broken[maxn][maxT], id[maxn];
double f[maxn][maxT];

inline bool byX(const int &i, const int &j)
{
    return x[i] < x[j];
}

map<Point, int> hash;
vector<Point> points;

inline int add(Point a)
{
    if (hash.count(a)) {
        return hash[a];
    }
    int newid = hash.size();
    points.push_back(a);
    return hash[a] = newid;
}

double R;

inline double getDist(Point s, double x, double y)
{
    if (s.x > x) {
        s.x = 2 * x - s.x;
    }
    if (s.y < y) {
        s.y = y * 2 - s.y;
    }
    double ang = atan2(fabs(y - s.y), fabs(x - s.x));
    Point center = Point(x, y + R);
    double d = (s - center).norm();
    
    //return sqrt(d * d - R * R) + (asin(R / d) - ang) * R;
    
    double cut = sqrt(d * d - R * R);
    Point dir = s - center;
    double angle = acos(R / d);
    dir.rotate(angle);
    dir = dir.normalize() * R;
    angle = acos( dot(Point(0, -R), dir) / R / dir.norm());
    return cut + angle * R;
}

inline double getDist(double x1, double y1, double x2, double y2)
{
    if (y1 < y2) {
        y2 = y1 * 2 - y2;
    }
    //double ang = atan2(fabs(y1 - y2), fabs(x1 - x2));
    Point o1 = Point(x1, y1 - R), o2 = Point(x2, y2 + R);
    double d = (o1 - o2).norm();
    double angle = acos(2 * R / d);
    Point dir = o2 - o1;
    dir.rotate(angle);
    dir = dir.normalize() * R;
    angle = acos( dot(Point(0, R), dir) / R / dir.norm());
    
    return sqrt(d * d - 4 * R * R) + angle * R * 2;
}

int main()
{
    double h, w;
    int nWall;
    scanf("%lf%lf", &h, &w);
    scanf("%lf%d", &R, &nWall);
    Point s(R, h / 2), t(w - R, h / 2);
    
    if (nWall == 0) {
        printf("%.10f\n", (s - t).norm());
        return 0;
    }
    
    for (int i = 0; i < nWall; ++ i) {
        scanf("%d%d", &holes[i], &x[i]);
        for (int j = 0; j < holes[i]; ++ j) {
            scanf("%d", &broken[i][j]);
            f[i][j] = 1e100;
        }
        id[i] = i;
    }
    sort(id, id + nWall, byX);
    
    int first = id[0];
    for (int i = 0; i < holes[first]; ++ i) {
        f[0][i] = getDist(s, x[first], broken[first][i] - R);
//printf("%lf\n", f[0][i]);
    }
    
    for (int i = 0; i + 1 < nWall; ++ i) {
        int a = id[i];
        int b = id[i + 1];
        for (int u = 0; u < holes[a]; ++ u) {
            for (int v = 0; v < holes[b]; ++ v) {
                f[i + 1][v] = min( f[i + 1][v], f[i][u] + getDist(x[a], broken[a][u] - R, x[b], broken[b][v] - R));
            }
        }
    }
    
    double ans = 1e100;
    int last = id[nWall - 1];
    for (int i = 0; i < holes[last]; ++ i) {
        double tmp = f[nWall - 1][i] + getDist(t, x[last], broken[last][i] - R);
        ans = min(ans, tmp);
    }
    printf("%.10f\n", ans);
    
    return 0;
}

