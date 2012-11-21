#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <utility>
#include <iostream>
using namespace std;

const double EPS = 1e-9;
const double INF = 1e9;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

// {{{

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}

    double norm2() const {
        return x * x + y * y;
    }

    double norm() const {
        return sqrt(norm2());
    }

    Point normalize() const;

    Point right_rotate() const {
        return Point(-y, x);
    }
};

Point operator + (const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator * (const Point &a, double k) {
    return Point(a.x * k, a.y * k);
}

Point operator / (const Point &a, double k) {
    return Point(a.x / k, a.y / k);
}

Point Point::normalize() const {
    return *this / this->norm();
}

istream &operator >> (istream &in, Point &p) {
    return in >> p.x >> p.y;
}

ostream &operator << (ostream &out, const Point &p) {
    printf("%.8f %.8f", p.x, p.y);
    //return out << p.x << " " << p.y;
    return out;
}

// }}}

double r;
Point target, sources[2];

typedef pair <Point, Point> Pair;

double sqrt_fixed(double x) {
    return sqrt(max(x, 0.0));
}

double sqr(double x) {
    return x * x;
}

Point* find(Point a, double r_1, Point b, double r_2, Point c, double r_3) {
    if (signum((a - b).norm() - (r_1 + r_2)) > 0) {
        return NULL;
    }
    if (signum((a - b).norm() - abs(r_1 - r_2)) < 0) {
        return NULL;
    }
    double x = (sqr(r_1) - sqr(r_2) + (a - b).norm2()) /  2 / (a - b).norm();
    Point m = a + (b - a).normalize() * x;
    Point d = (b - a).normalize().right_rotate() * sqrt_fixed(r_1 * r_1 - x * x);
    if (signum((m + d - c).norm() - r_3) <= 0) {
        assert(signum((m + d - a).norm() - r_1) == 0);
        assert(signum((m + d - b).norm() - r_2) == 0);
        assert(signum((m + d - c).norm() - r_3) <= 0);
        return new Point(m + d);
    }
    if (signum((m - d - c).norm() - r_3) <= 0) {
        assert(signum((m - d - a).norm() - r_1) == 0);
        assert(signum((m - d - b).norm() - r_2) == 0);
        assert(signum((m - d - c).norm() - r_3) <= 0);
        return new Point(m - d);
    }
    return NULL;
}

Point* find_all(const Point &a, double r_1, const Point &b, double r_2, const Point &c, double r_3) {
    Point *ret = find(a, r_1, b, r_2, c, r_3);
    if (ret != NULL) {
        return ret;
    }
    ret = find(b, r_2, c, r_3, a, r_1);
    if (ret != NULL) {
        return ret;
    }
    ret = find(c, r_3, a, r_1, b, r_2);
    if (ret != NULL) {
        return ret;
    }
    return NULL;
}

Pair* check(Point target, Point sources[2]) {
    if (signum((target - sources[0]).norm() - 2 * r) <= 0 && signum((target - sources[1]).norm() - 2 * r) <= 0) {
        return new Pair((sources[0] + target) / 2.0, (sources[1] + target) / 2.0);
    }
/*    if (signum((target - sources[0]).norm() - r) <= 0 && signum((target - sources[1]).norm() - 3 * r) <= 0) {
printf("%lf %lf\n",(target - sources[1]).norm(),r*3);
        return new Pair((sources[1] * 2 + target) / 3.0, (sources[1] + target * 2) / 3.0);
    }*/
    Point *ret = find_all(sources[0], r, sources[1], r, target, r * 2);
    if (ret != NULL) {
        return new Pair(*ret, (*ret + target) / 2.0);
    }
    ret = find_all(sources[0], r, target, r, sources[1], r * 2);
    if (ret != NULL) {
        return new Pair(*ret, (*ret + sources[1]) / 2.0);
    }
    return NULL;
}

int main() {
    cin >> r >> target >> sources[0] >> sources[1];
    Pair* ret = check(target, sources);
    if (ret == NULL) {
        swap(sources[0], sources[1]);
        ret = check(target, sources);
    }
    if (ret == NULL) {
        puts("Death");
    } else {
        puts("Now we have enough power");
        cout << ret->first << endl << ret->second << endl;
    }
    return 0;
}
