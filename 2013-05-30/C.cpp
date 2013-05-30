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

const double pi = acos(-1.0);
const double eps = 1e-11;

struct Point
{
    int x, y, part;

    Point(int x, int y) : x(x), y(y) {
        if (y != 0) {
            part = y < 0 ? -1 : 1;
        } else if (x != 0) {
            part = x < 0 ? -1 : 1;
        } else {
            part = 0;
        }
    }

    Point rotL() const {
        return Point(y, -x);
    }

    Point rotR() const {
        return Point(-y, x);
    }

    bool operator<(const Point &o) const {
        return part < o.part || part == o.part && (long long)x * o.y > (long long)y * o.x;
    }

    double ang() const {
        return atan2(y, x);
        //return -part * acos(x / hypot(x, y));
    }
};

void checkmin(double &a, double b)
{
    if (fabs(a) > fabs(b) + eps || fabs(a) + eps > fabs(b) && a < b) {
        a = b;
    }
}

bool cmp(const pair<Point,int> &a, const pair<Point,int> &b)
{
    return a.first < b.first || !(b.first < a.first) && a.second > b.second;
}

const int maxn = 11111;

int n, theta;
int x[maxn], y[maxn];

int main()
{
    int cas = 0;
    while (scanf("%d%d", &n, &theta) == 2 && n) {
        x[0] = y[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", x + i, y + i);
        }
        vector<pair<Point,int> > events;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            Point dir(x[i + 1] - x[i], y[i + 1] - y[i]);
            Point lo = dir.rotL(), hi = dir.rotR();
            if (hi < lo) {
                sum ++;
            }
            events.push_back(make_pair(lo, +1));
            events.push_back(make_pair(hi, -1));
        }
        events.push_back(make_pair(Point(1, 0), 0));
        sort(events.begin(), events.end(), cmp);
        double ans = 1e100;
        if (sum == n) {
            checkmin(ans, pi);
        }
        FOR (it, events) {
            if (sum == n) {
                checkmin(ans, it->first.ang());
            }
            sum += it->second;
            if (sum == n) {
                checkmin(ans, it->first.ang());
            }
        }
        printf("Case %d: ", ++cas);
        if (theta == 0 || fabs(ans) < eps) {
            puts("Acceptable as proposed");
        } else if (fabs(ans) > 1e50) {
            puts("Unacceptable");
        } else {
            printf("Acceptable after %s rotation of %.2f degrees\n", ans > 0 ? "clockwise" : "counterclockwise", fabs(ans) / pi * 180);
        }
        puts("");
    }
}
