#include <cstdio>
#include <cstring>
#include <cmath>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const double EPS = 1e-11;

// {{{ 

int signum(double x) {
    return x < -EPS? -1: x > EPS;
}

double sqr(double x) {
    return x * x;
}

double sqrt2(double x) {
    return sqrt(max(x, 0.0));
}

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    double norm2() const;
    double norm() const;
    Point normalize() const;
    Point rotate() const;
    Point project(const Point &, const Point &) const;
    Point reflect(const Point &, const Point &) const;
};

istream &operator >> (istream &in, Point &p) {
    return in >> p.x >> p.y;
}

bool operator <(const Point &a, const Point &b) {
    if (signum(a.x - b.x) == 0) {
        return signum(a.y - b.y) < 0;
    }
    return signum(a.x - b.x) < 0;
}

bool operator ==(const Point &a, const Point &b) {
    return signum(a.x - b.x) == 0 && signum(a.y - b.y) == 0;
}

Point operator +(const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator *(const Point &a, double k) {
    return Point(a.x * k, a.y * k);
}

Point operator *(double k, const Point &a) {
    return Point(k * a.x, k * a.y);
}

Point operator /(const Point &a, double k) {
    return Point(a.x / k, a.y / k);
}

double Point::norm2() const {
    return sqr(x) + sqr(y);
}

double Point::norm() const {
    return sqrt2(norm2());
}

Point Point::normalize() const {
    return *this / norm();
}

Point Point::rotate() const {
    return Point(-y, x);
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

Point Point::project(const Point &a, const Point &b) const {
    return a + dot(*this - a, b - a) / (b - a).norm2() * (b - a);
}

Point Point::reflect(const Point &a, const Point &b) const {
    Point p = this->project(a, b);
    return p * 2 - *this;
}

static const Point ORIGIN(0.0, 0.0);

struct Circle {
    Point o;
    double r;

    Circle(Point o = ORIGIN, double r = 0.0): o(o), r(r) {}
    Circle(Point a, Point b): o((a + b) / 2.0), r((b - a).norm() / 2.0) {}
};

istream &operator >> (istream &in, Circle &c) {
    return in >> c.o >> c.r;
}

Point intersect(const Circle &a, const Circle &b) {
    Point r = (b. o - a.o).normalize();
    double d = (b.o - a.o).norm();
    double x = 0.5 * ((sqr(a.r) - sqr(b.r)) / d + d);
    double h = sqrt2(sqr(a.r) - sqr(x));
    return a.o + r * x + r.rotate() * h;
}

Point tangent(const Point &p, const Circle &c) {
    return intersect(Circle(p, c.o), c);
}

// }}}

const Point DIRECTIONS[4] = {Point(-1, 0), Point(0, -1), Point(0, 1), Point(1, 0)};

const int N = 500;

int n;
Circle circles[N];
vector <pair <Point, int> > points;

bool leftTurn(const Point &a, const Point &b, const Point &c) {
    if (a == b || b == c) {
        return false;
    }
    return signum(det(b - a, c - b) / (b - a).norm()) > 0;
}

double solve() {
    vector <pair <Point, int> > hull;
    for (int i = 0; i < (int)points.size(); ++ i) {
        while ((int)hull.size() > 1 && !leftTurn(hull[(int)hull.size() - 2].first, hull.back().first, points[i].first)) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    double result = 0;
    for (int i = 0; i + 1< (int)hull.size(); ++ i) {
        Point a = hull[i].first;
        Point b = hull[i + 1].first;
        if (hull[i].second == hull[i + 1].second) {
            int id = hull[i].second;
            a = a - circles[id].o;
            b = b - circles[id].o;
            double alpha = acos(dot(a, b) / (a.norm() * b.norm()));
            result += circles[id].r * alpha;
        } else {
            result += (a - b).norm();
        }
    }
    return result;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> circles[i];
    }
    for (int i = 0; i < n; ++ i) {
        for (int k = 0; k < 4; ++ k) {
            points.push_back(make_pair(circles[i].o + circles[i].r * DIRECTIONS[k], i));
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j) {
                Circle a = circles[i];
                Circle b = circles[j];
                if (signum(a.r - b.r) == 0) {
                    Point r = (b.o - a.o).normalize().rotate() * a.r;
                    points.push_back(make_pair(a.o + r, i));
                    points.push_back(make_pair(b.o + r, j));
                    points.push_back(make_pair(a.o - r, i));
                    points.push_back(make_pair(b.o - r, j));
                }
                if (signum(a.r - b.r) < 0) {
                    Point p = a.o;
                    Point q = tangent(a.o, Circle(b.o, b.r - a.r));
                    Point r = (q - b.o).normalize() * a.r;
                    p = p + r;
                    q = q + r;
                    points.push_back(make_pair(p, i));
                    points.push_back(make_pair(q, j));
                    p = p.reflect(a.o, b.o);
                    q = q.reflect(a.o, b.o);
                    points.push_back(make_pair(p, i));
                    points.push_back(make_pair(q, j));
                }
            }
        }
    }
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
//for (int i = 0; i < (int)points.size(); ++ i) {
//    printf("(%.10f, %.10f), %d\n", points[i].first.x, points[i].first.y, points[i].second);
//}
    double result = solve();
    reverse(points.begin(), points.end());
    result += solve();
    printf("%.10f\n", result);
    return 0;
}
