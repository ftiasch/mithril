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

const double eps = 1e-11;

inline int signum(double a)
{
    return a < -eps ? -1 : a > eps ? 1 : 0;
}

struct Point
{
    double x, y;

    Point() {}
    Point(double x, double y) {}

    void read() {
        scanf("%lf%lf", &x, &y);
    }

    bool operator<(const Point &o) const {
        return x + eps < o.x || x < o.x + eps && y + eps < o.y;
    }

    double distTo(const Point &o) const {
        return sqrt((x - o.x) * (x - o.x) + (y - o.y) * (y - o.y));
    }
};

inline double det(double x1, double y1, double x2, double y2)
{
    return x1 * y2 - x2 * y1;
}

inline double det(const Point &a, const Point &b, const Point &c)
{
    return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

bool intersect(const Point &a1, const Point &a2, const Point &b1, const Point &b2, Point &x)
{
    double z1 = det(a1, a2, b1);
    double z2 = det(a1, a2, b2);
    if (signum(z1) * signum(z2) >= 0) {
        return false;
    }
    z1 = det(b1, b2, a1);
    z2 = det(b1, b2, a2);
    if (signum(z1) * signum(z2) >= 0) {
        return false;
    }
    x.x = (a1.x * z2 - a2.x * z1) / (z2 - z1);
    x.y = (a1.y * z2 - a2.y * z1) / (z2 - z1);
    return true;
}

const int maxn = 100;

int n;
Point a[maxn], b[maxn];

int main()
{
    int cas = 0;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            a[i].read();
            b[i].read();
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            vector<Point> pts;
            pts.push_back(a[i]);
            pts.push_back(b[i]);
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                Point res;
                if (intersect(a[i], b[i], a[j], b[j], res)) {
                    pts.push_back(res);
                }
            }
            sort(pts.begin(), pts.end());
            for (int j = 1; j < pts.size(); j++) {
                ans += (int)((pts[j].distTo(pts[j - 1]) + (j == 1 ? 25 : 0) + (j + 1 == pts.size() ? 25 : 0)) / 50 + eps);
            }
        }
        printf("Map %d\nTrees = %d\n", ++cas, ans);
    }
}
