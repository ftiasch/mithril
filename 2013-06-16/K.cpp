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

struct Point
{
    int x, y;

    Point(){}
    Point(int x, int y) : x(x), y(y){}

    Point rot90() const {
        return Point(y, -x);
    }

    Point operator+(const Point &o) const {
        return Point(x + o.x, y + o.y);
    }

    Point operator-(const Point &o) const {
        return Point(x - o.x, y - o.y);
    }

    double norm() const {
        return hypot((double)x, (double)y);
    }
};

inline int dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

const int maxn = 100;
const int inf = 1000000000;
const double eps = 1e-11;

int n;
Point pts[maxn];

int main()
{
    int cas = 0;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pts[i].x, &pts[i].y);
        }
        double ans = 1e100;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                Point dir = (pts[i] - pts[j]).rot90();
                int minv = inf, maxv = -inf;
                for (int k = 0; k < n; k++) {
                    int val = dot(dir, pts[k]);
                    minv = min(minv, val);
                    maxv = max(maxv, val);
                }
                double len = (maxv - minv) / dir.norm();
                ans = min(ans, len);
            }
        }
        printf("Case %d: %.2f\n", ++cas, ans + 0.005 - eps);
    }
}

