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

struct Point
{
    double x, y;

    Point(double x, double y) : x(x), y(y) { }

    Point(){}

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

    Point rot90() const {
        return Point(-y, x);
    }

    double norm2() const {
        return x * x + y * y;
    }

    double norm() const {
        return sqrt(x * x + y * y);
    }
};

struct Circle
{
    Point center;
    double radius;

    Circle(const Point &center, double radius) : center(center), radius(radius) {}

    bool contains(const Point &p) const {
        return (p - center).norm() <= EPS + radius;
    }
};

inline int signum(double v)
{
    return v < -EPS ? -1 : v > EPS;
}

const int MAXN = 20;

int n, m;
Point pts[MAXN];

bool circle_center(const Point &p0, const Point &p1, const Point &p2, Point &cp)
{
    double a1 = p1.x - p0.x, b1 = p1.y - p0.y;
    double a2 = p2.x - p0.x, b2 = p2.y - p0.y;
    double d = a1 * b2 - a2 * b1;
    if (signum(d) == 0) {
        return false;
    }
    double c1 = (a1 * a1 + b1 * b1) / 2;
    double c2 = (a2 * a2 + b2 * b2) / 2;
    cp.x = p0.x + (c1 * b2 - c2 * b1) / d;
    cp.y = p0.y + (a1 * c2 - a2 * c1) / d;
    return true;
}

int opt[1 << MAXN];
bool visited[1 << MAXN];

int Q[1 << MAXN];

bool cmp(const pair<double, int> &a, const pair<double, int> &b)
{
    return a.first + EPS < b.first || (a.first < b.first + EPS &&
            a.second > b.second);
}

int main()
{
    int tests;
    cin >> tests;
    for (int cas = 1; cas <= tests; ++cas) {
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            cin >> pts[i].x >> pts[i].y;
        vector<Circle> circles;
        for (int i = 0; i < n; i++) {
            circles.push_back(Circle(pts[i], 0.0));
            for (int j = 0; j < i; j++) {
                circles.push_back(Circle((pts[i] + pts[j]) / 2, (pts[i] - pts[j]).norm() / 2.));
                for (int k = 0; k < j; k++) {
                    Point x;
                    if (circle_center(pts[i], pts[j], pts[k], x)) {
                        circles.push_back(Circle(x, (pts[i]-x).norm()));
                    }
                }
            }
        }
        vector<pair<double, int> > importants;
        for (int i = 0; i < circles.size(); i++) {
            int mask = 0;
            for (int j = 0; j < n; j++) {
                if (circles[i].contains(pts[j])) {
                    mask |= 1 << j;
                }
            }
            importants.push_back(make_pair(circles[i].radius, mask));
        }
        sort(importants.begin(), importants.end(), cmp);
        memset(visited, false, sizeof(visited[0]) << n);
        int sz = 0;
        for (int i = 0; i < importants.size(); i++) {
            int msk = importants[i].second;
            if (!visited[msk]) {
                importants[sz++] = importants[i];
//printf("%20.10f ", importants[i].first); for (int j = 0; j < n; j++) putchar(importants[i].second >> j & 1 ? 'X' : ' ');puts("");
                queue<int> Q;
                visited[msk] = true;
                Q.push(msk);
                while (!Q.empty()) {
                    msk = Q.front();
                    Q.pop();
                    for (int i = 0; i < n; i++) {
                        if (msk >> i & 1 && !visited[msk ^ (1 << i)]) {
                            visited[msk ^ (1 << i)] = true;
                            Q.push(msk ^ (1 << i));
                        }
                    }
                }
            }
        }
        importants.resize(sz);
        int lo = 0, hi = importants.size() + 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            memset(opt, -1, sizeof(opt[0]) << n);
            opt[0] = 0;
            int head = 0, tail = 0;
            Q[tail++] = 0;
            while (head < tail) {
                int i = Q[head ++];
                for (int j = 0; j < mid; j++) {
                    int ni = i | importants[j].second;
                    if (opt[ni] < 0) {
                        opt[ni] = opt[i] + 1;
                        if (ni + 1 == (1 << n)) {
                            head = tail + 1;
                            break;
                        }
                        if (opt[ni] < m) {
                            Q[tail ++] = ni;
                        }
                    }
                }
            }
//printf("%d %d\n", mid, opt[(1 << n) - 1]);
            if (opt[(1 << n) - 1] >= 0 && opt[(1 << n) - 1] <= m) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        assert(hi - 1 < importants.size());
        printf("Case %d: %.2f\n", cas, importants[hi - 1].first + EPS);
    }
}
