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

struct Point
{
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    Point rotate(double alpha) const {
        double sina, cosa;
        sincos(alpha, &sina, &cosa);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }

    Point operator+(const Point &o) const {
        return Point(x + o.x, y + o.y);
    }

    Point operator-(const Point &o) const {
        return Point(x - o.x, y - o.y);
    }

    Point operator*(double scale) const {
        return Point(x * scale, y * scale);
    }

    Point operator/(double scale) const {
        return Point(x / scale, y / scale);
    }

};

double det(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

double det(const Point &a, const Point &b, const Point &c)
{
    return det(b - a, c - a);
}

const double INF = 1e8;
const double EPS = 1e-9;
const double PI = acos(-1.0);
const int MAXN = 128;

int signum(double a)
{
    return a < -EPS ? -1 : a > EPS;
}

struct HalfPlane
{
    Point a, b;
    HalfPlane(Point a, Point b) : a(a), b(b) {}
};

int n;
Point a[MAXN], b[MAXN];
double minAlpha, maxAlpha;

double areaConvex(const vector<Point> &pts)
{
    double area = 0;
    for (int i = 0; i < pts.size(); i++) {
        int j = i + 1 == pts.size() ? 0 : i + 1;
        area += det(pts[i], pts[j]);
    }
    return area;
}

vector<Point> cutConvex(const vector<Point> &pts, const Point &a, const Point &b)
{
    vector<Point> ret;
    for (int i = 0; i < pts.size(); i++) {
        int j = i + 1 == pts.size() ? 0 : i + 1;
        double areai = det(a, b, pts[i]);
        double areaj = det(a, b, pts[j]);
        if (signum(areai) >= 0) {
            ret.push_back(pts[i]);
        }
        if (signum(areai) * signum(areaj) < 0) {
            ret.push_back((pts[i] * areaj - pts[j] * areai) / (areaj - areai));
        }
    }
    if (signum(areaConvex(ret)) <= 0 || ret.size() < 3) {
        ret.clear();
    }
    return ret;
}

int main()
{
    cin >> n >> minAlpha >> maxAlpha;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        cin >> b[i].x >> b[i].y;
    }
    double lo = minAlpha / 180 * PI;
    double hi = maxAlpha / 180 * PI;
    bool impossible = true;
    for (int it = 0; it < 128; ++it) {
        double mid = (lo + hi) / 2.0;
        vector<Point> convex;
        convex.push_back(Point(INF, INF));
        convex.push_back(Point(-INF, INF));
        convex.push_back(Point(-INF, -INF));
        convex.push_back(Point(INF, -INF));
        for (int i = 0; i < n; i++) {
            convex = cutConvex(convex, (b[i] - a[i]).rotate(mid / 2) + a[i], a[i]);
            convex = cutConvex(convex, a[i], (b[i] - a[i]).rotate(- mid / 2) + a[i]);
        }
        if (signum(areaConvex(convex)) <= 0) {
            impossible = false;
            lo = mid;
        } else {
            hi = mid;
        }
    }
    if (impossible) {
        puts("IMPOSSIBLE");
    } else { 
        printf("%.10f\n", (lo + hi) / 2 / PI * 180);
    }
}
