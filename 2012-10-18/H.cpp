#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;

const char *ESCAPE = "Mouse can escape at (%.8f, %.8f).\n";
const char *DRAW = "There can be draw at (%.8f, %.8f).\n";
const char *BAD = "Something bad will happen!\n";

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

double sqr(double x) {
    return x * x;
}

double sqrt2(double x) {
    if (signum(x) <= 0) {
        return 0.0;
    }
    return sqrt(x);
}

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    Point &operator +=(const Point &o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    Point &operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    Point &operator *=(double k) {
        x *= k;
        y *= k;
        return *this;
    }

    Point &operator /=(double k) {
        x /= k;
        y /= k;
        return *this;
    }

    double norm2() const {
        return sqr(x) + sqr(y);
    }

    double norm() const {
        return sqrt2(norm2());
    }

    Point normalize() const;

    bool on2(const Point&, const Point&) const;
    bool onRay(const Point&, const Point &) const;

    double to(const Point &, const Point&) const;

    Point project(const Point &, const Point &) const;
};

istream &operator >> (istream &in, Point &p) {
    return in >> p.x >> p.y;
}

Point operator +(Point a, const Point &b) {
    return a += b;
}

Point operator -(Point a, const Point &b) {
    return a -= b;
}

Point operator *(Point a, double k) {
    return a *= k;
}

Point operator *(double k, Point a) {
    return a *= k;
}

Point operator /(Point a, double k) {
    return a /= k;
}

bool operator == (const Point &a, const Point &b) {
    return signum(a.x - b.x) == 0 && signum(a.y - b.y) == 0;
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

bool Point::on2(const Point &a, const Point &b) const {
    const Point &p = *this;
    if (a == p || b == p) {
        return true;
    }
    return signum(dot(p - a, p - b) / (p - b).norm()) <= 0;
}

bool Point::onRay(const Point &a, const Point &b) const {
    const Point &p = *this;
    return signum(dot(p - a, b - a) / (b - a).norm()) >= 0;
}

double Point::to(const Point &a, const Point &b) const {
    const Point &p = *this;
    return abs(det(p - a, p - b) / (a - b).norm());
}

Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    double s_1 = det(b - a, c - a);
    double s_2 = det(b - a, d - a);
    return (s_2 * c - s_1 * d) / (s_2 - s_1);
}

bool has_intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    return signum(det(a - b, c -  d) / (c - d).norm()) != 0;
}

Point division(const Point &a, const Point &b, double lambda) {
    return a + (b - a) * lambda;
}

Point Point::normalize() const {
    return *this / this->norm();
}

Point Point::project(const Point &a, const Point &b) const {
    const Point &p = *this;
    return a + dot(p - a, b - a) / (b - a).norm2() * (b - a);
}

struct Circle {
    Point o;
    double r;

    Circle(): r(0.0) {}

    Circle(const Point &a, const Point &b): o((a + b) / 2.0), r((a - b).norm() / 2.0) {}
};

Point intersect(const Circle &c, const Point &a, const Point &b) {
    double x = sqrt2(sqr(c.r) - sqr(c.o.to(a, b)));
    return c.o.project(a, b) + (a - b).normalize() * x;
}

const int N = 100;

int n;
double v_cat, v_mouse;
Point polygon[N], cat, mouse;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

int main() {
    int test_count = 0;
    while (scanf("%d", &n) == 1 && n) {
        printf("Arena %d: ", ++ test_count);
        for (int i = 0; i < n; ++ i) {
            cin >> polygon[i];
        }
        cin >> cat >> v_cat >> mouse >> v_mouse;
        if (signum(v_cat - v_mouse) <= 0) {
            for (int i = 0; i < n; ++ i) {
                Point &a = polygon[i];
                Point &b = polygon[(i + 1) % n];
                if (has_intersect(cat, mouse, a, b)) {
                    Point p = intersect(cat, mouse, a, b);
                    if (p.on2(a, b) && p.onRay(cat, mouse)) {
                        printf(ESCAPE, p.x, p.y);
                        break;
                    }
                }
            }
        } else {
            Circle c;
            {
                Point a = division(cat, mouse, v_cat / (v_cat + v_mouse));
                Point b = division(cat, mouse, v_cat / (v_cat - v_mouse));
//printf("(%.8f, %.8f)\n", a.x, a.y);
//printf("(%.8f, %.8f)\n", b.x, b.y);
                c = Circle(a, b);
            }
//printf("(%.8f, %.8f) %.8f\n", c.o.x, c.o.y, c.r);
            Point *escape = NULL;
            Point *draw = NULL;
            for (int i = 0; i < n; ++ i) {
                Point &a = polygon[i];
                Point &b = polygon[(i + 1) % n];
                vector <Point> events;
                events.push_back(a);
                events.push_back(b);
                if (signum(c.o.to(a, b) - c.r) <= 0) {
                    {
                        Point p = intersect(c, a, b);
                        if (p.on2(a, b)) {
                            events.push_back(p);
                        }
                    }
                    {
                        Point p = intersect(c, b, a);
                        if (p.on2(a, b)) {
                            events.push_back(p);
                        }
                    }
                }
                foreach (he, events) {
                    foreach (she, events) {
                        Point p = (*he + *she) / 2.0;
                        double d = (p - cat).norm() / v_cat - (p - mouse).norm() / v_mouse;
                        if (signum(d) == 0 && draw == NULL) {
                            draw = new Point(p.x, p.y);
                        }
                        if (signum(d) > 0 && escape == NULL) {
                            escape = new Point(p.x, p.y);
                        }
                    }
                }
            }
            if (escape != NULL) {
                printf(ESCAPE, escape->x, escape->y);
            } else if (draw != NULL) {
                printf(DRAW, draw->x, draw->y);
            } else {
                printf(BAD);
            }
        }
    }
    return 0;
}
