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

const double pi = acos(-1.);

struct Point
{
    double x, y;

    Point(double x, double y) : x(x), y(y) {}

    double dist2(const Point &o) const {
        return hypot(x - o.x, y - o.y);
    }
};

struct Arc
{
    int x, y, r;
    int b, e;

    void read() {
        scanf("%d%d%d%d%d", &x, &y, &r, &b, &e);
    }

    Point get(double arg) {
        return Point(x + cos(arg / 180 * pi) * r, y + sin(arg / 180 * pi) * r);
    }

    bool check(double arg) {
        if (b < e) {
            return b <= arg && arg <= e;
        }
        return b <= arg || arg <= e;
    }

    double dist2(const Point &o) {
        double ret = o.dist2(get(b));
        ret = min(ret, o.dist2(get(e)));
        double arg = atan2(o.y - y, o.x - x) / pi * 180;
        if (arg < 0) {
            arg += 360;
        }
        if (check(arg)) {
            ret = min(ret, o.dist2(get(arg)));
        }
        return ret;
    }
};

int main()
{
    Arc a, b;
    const int SEGS = 10000;
    a.read();
    b.read();
    if (a.e < a.b) {
        a.e += 360;
    }
    double ret = 1e100;
    for (int i = 0; i < SEGS; i++) {
        double lo = (double)i / SEGS;
        double hi = (double)(i + 1) / SEGS;
        lo = lo * (a.e - a.b) + a.b;
        hi = hi * (a.e - a.b) + a.b;
        for (int it = 0; it < 150; ++it) {
            double mid1 = (lo + lo + hi) / 3.0;
            double mid2 = (lo + hi + hi) / 3.0;
            if (b.dist2(a.get(mid1)) < b.dist2(a.get(mid2))) {
                hi = mid2;
            } else {
                lo = mid1;
            }
        }
        ret = min(ret, b.dist2(a.get((lo + hi) / 2.0)));
    }
    printf("%.10f\n", ret);
}
