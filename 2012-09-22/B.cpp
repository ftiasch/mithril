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

const double EPS = 1e-11;
const double PI = acos(-1.);

struct Point
{
    double x, y;

    Point(){}
    Point(double x, double y) : x(x), y(y) {}
    Point(double a) : x(cos(a)), y(sin(a)) {}

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

    double norm() const {
        return sqrt(x * x + y * y);
    }
    
    Point normalize() const {
        return *this/(norm());
    }
};

inline int signum(double a)
{
    return a < -EPS ? -1 : a > EPS;
}

inline double det(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

inline double dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

inline bool operator<(const Point &a, const Point &b)
{
    return signum(det(a, b)) > 0;
}

inline double det(const Point &a, const Point &b, const Point &c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int L, n;
vector<pair<int,int> > pillars;

double solve(int st, int ed)
{
    st = max(st, 6);
    ed = min(ed, 12);
    if (st >= ed) {
        return 0.0;
    }
    Point minR((st - 6) / 12.0 * PI);
    Point maxR((ed - 6) / 12.0 * PI);
    double ret = 0;
    for (int i = 0; i + 1 < pillars.size(); i++) {
        Point origin(pillars[i].first, 0);
        vector<Point> convex;
        for (int j = i + 1; j < pillars.size(); j++) {
            Point now(pillars[j].first, pillars[j].second);
            while (convex.size() >= 2 && signum(det(convex[convex.size() - 2], convex.back(), now)) >= 0) {
                convex.pop_back();
            }
            convex.push_back(now);
        }
        while (convex.size() >= 2 && signum(convex[convex.size() - 2].y - convex.back().y) >= 0) {
            convex.pop_back();
        }
        while (convex.size() >= 2 && signum(det(convex[convex.size() - 2], convex.back(), origin)) <= 0) {
            convex.pop_back();
        }
        for (int j = 0; j < convex.size(); j++) {
            Point rangeLeft = (convex[j] - origin).normalize();
            if (j + 1 < convex.size()) {
                rangeLeft = (convex[j + 1] - convex[j]).normalize();
            }
            Point rangeRight(0, 1);
            if (j > 0) {
                rangeRight = (convex[j] - convex[j - 1]).normalize();
            }
            rangeLeft = max(rangeLeft, minR);
            rangeRight = min(rangeRight, maxR);
            if (rangeLeft < rangeRight) {
                ret += abs(dot(origin - convex[j], rangeRight - rangeLeft));
            }
        }
    }
    return ret;
}

int main()
{
    while (scanf("%d%d", &L, &n) == 2 && n) {
        int st, ed;
        scanf("%d%d", &st, &ed);
        // sun rise on east
        st = 24 - st;
        ed = 24 - ed;
        swap(st, ed);
        pillars.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pillars[i].first, &pillars[i].second);
        }
        sort(pillars.begin(), pillars.end());
        if (pillars[0].first != 0) {
            pillars.insert(pillars.begin(), make_pair(0, 0));
        }
        if (pillars.back().first != L) {
            pillars.push_back(make_pair(L, 0));
        }
        double ans = 0;
        // morning
        ans += solve(st, ed);
        // afternoon
        for (int i = 0; i < pillars.size(); i++) {
            pillars[i].first = L - pillars[i].first;
        }
        reverse(pillars.begin(), pillars.end());
        ans += solve(24 - ed, 24 - st);
        ans = ans / PI * 12;
        printf("%.5f\n", ans + EPS);
    }
}
