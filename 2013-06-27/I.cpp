#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

namespace cb
{
    const double eps = 1e-8;
    const double pi = acos(-1.0);
    const double base = 0.442344234423;

    struct Point 
    {
        double x, y;

        Point(){}
        Point(double x, double y) : x(x), y(y){}

        Point operator+(const Point &o) const {
            return Point(x + o.x, y + o.y);
        }

        Point operator-(const Point &o) const {
            return Point(x - o.x, y - o.y);
        }

        Point rot90() const {
            return Point(-y, x);
        }

        Point rot(const Point &a) const;

        void read() {
            scanf("%lf%lf", &x, &y);
        }
    };

    inline double dot(const Point &a, const Point &b)
    {
        return a.x * b.x + a.y * b.y;
    }

    inline double det(const Point &a, const Point &b)
    {
        return a.x * b.y - a.y * b.x;
    }

    inline double det(const Point &a, const Point &b, const Point &c)
    {
        return det(b - a, c - a);
    }

    Point Point::rot(const Point &ang) const
    {
        return Point(dot(ang, *this), det(ang, *this));
    }

    int signum(double a)
    {
        return a < -eps ? -1 : a > eps;
    }

    Point a1, a2, b1, b2;

    bool inRange(double l, double r, double x)
    {
        if (l > r) {
            swap(l, r);
        }
        return l <= x - eps && x <= r - eps;
    }

    pair<double,bool> solve(double ang)
    {
        Point unit(cos(ang), sin(ang));
        Point A1 = a1.rot(unit), A2 = a2.rot(unit);
        Point B1 = b1.rot(unit), B2 = b2.rot(unit);
        double lenX = fabs(A1.x - A2.x);
        double lenY = fabs(B1.y - B2.y);
        bool check = inRange(A1.x, A2.x, B1.x) && inRange(A1.x, A2.x, B2.x) &&
                inRange(B1.y, B2.y, A1.y) && inRange(B1.y, B2.y, A2.y);
        return make_pair(min(lenX, lenY), fabs(lenX - lenY) < eps && check);
    }

    Point pts[4];

    double solve(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        pts[0].x = x0; pts[0].y = y0;
        pts[1].x = x1; pts[1].y = y1;
        pts[2].x = x2; pts[2].y = y2;
        pts[3].x = x3; pts[3].y = y3;
        double ans = -1;
        for (int i = 1; i < 4; i++) {
            swap(pts[1], pts[i]);
            a1 = pts[0], a2 = pts[1];
            b1 = pts[2], b2 = pts[3];
            swap(pts[1], pts[i]);
            const int SEGS = 137;
            for (int it = 0; it < SEGS; it++) {
                double lo = pi * it / SEGS + base;
                double hi = pi * (it + 1) / SEGS + base;
                for (int jt = 0; jt < 100; ++jt) {
                    double mid1 = (lo + lo + hi) / 3;
                    double mid2 = (lo + hi + hi) / 3;
                    if (solve(mid1).first > solve(mid2).first) {
                        hi = mid2;
                    } else {
                        lo = mid1;
                    }
                }
                pair<double,bool> res = solve((lo + hi) / 2);
                if (res.second) {
                    ans = max(ans, res.first);
                }
            }
        }
        return ans;
    }
};

const double EPS = 1e-9;
const double INF = 1e10;

int x[4], y[4], p[4];

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

double sqr(double x) {
    return x * x;
}

int main() {
    //freopen("I.in", "r", stdin);
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        for (int i = 0; i < 4; ++ i) {
            scanf("%d%d", x + i, y + i);
            p[i] = i;
        }
        double answer = cb::solve(x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
        do {
            // (cos(a), sin(a)) - 
            // -sin(a), cos(a)
            int cosCoef = 0;
            int sinCoef = 0;
            cosCoef += x[p[0]]; sinCoef += y[p[0]];
            cosCoef -= x[p[1]]; sinCoef -= y[p[1]];
            sinCoef += x[p[2]]; cosCoef -= y[p[2]];
            sinCoef -= x[p[3]]; cosCoef += y[p[3]];
            // cc * cos(a) + sc * sin(a) = 0
            // - cc / sc = sin(a) / cos(a) = tan(a)
            if (cosCoef == 0 && sinCoef == 0) {
            } else {
                double theta = atan2(sinCoef, cosCoef);
                double xMin = INF;
                double xMax = -INF;
                double yMin = INF;
                double yMax = -INF;
                for (int i = 0; i < 4; ++ i) {
                    double xx = cos(theta) * x[i] + sin(theta) * y[i];
                    double yy = -sin(theta) * x[i] + cos(theta) * y[i];
                    xMin = std::min(xMin, xx);
                    xMax = std::max(xMax, xx);
                    yMin = std::min(yMin, yy);
                    yMax = std::max(yMax, yy);
                }
                bool valid = signum(xMax - xMin - yMax + yMin) == 0;
                for (int i = 0; i < 4; ++ i) {
                    double xx = cos(theta) * x[i] + sin(theta) * y[i];
                    double yy = -sin(theta) * x[i] + cos(theta) * y[i];
                    int count = 0;
                    count += signum(xx - xMin) == 0;
                    count += signum(xx - xMax) == 0;
                    count += signum(yy - yMin) == 0;
                    count += signum(yy - yMax) == 0;
                    valid &= count == 1;
                }
                if (valid) {
//printf("%.10f\n", theta);
                    answer = std::max(answer, xMax - xMin);
                }
            }
        } while (std::next_permutation(p, p + 4));
        printf("Case %d: ", t);
        if (answer < 0) {
            puts("no solution");
        } else {
            printf("%.2f\n", 10 + answer);
        }
    }
    return 0;
}

