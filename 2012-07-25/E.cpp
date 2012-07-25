#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;

int signum(double x) {
    return x < -EPS? -1: x > EPS;
}

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    int quad() const {
        int a = signum(x);
        int b = signum(y);
        if (a > 0 && b >= 0) {
            return 0;
        }
        if (b > 0 && a <= 0) {
            return 1;
        }
        if (a < 0 && b <= 0) {
            return 2;
        }
        return 3;
    }
};

ostream &operator <<(ostream &out, Point &p) {
    return out << "(" << p.x << ", " <<  p.y << ")";
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator *(const Point &a, double k) {
    return Point(a.x * k, a.y * k);
}

Point operator /(const Point &a, double k) {
    return Point(a.x / k, a.y / k);
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    double s_1 = det(a - c, d - c);
    double s_2 = det(b - c, d - c);
    return (a * s_2 - b * s_1) / (s_2 - s_1);
}

struct Plane {
    Point a, b;

    Plane(Point a = Point(0, 0), Point b = Point(0, 0)): a(a), b(b) {}

    Point dir() const {
        return b - a;
    }

    int quad() const {
        return dir().quad();
    }
};

ostream &operator <<(ostream &out, Plane &u) {
    return out << u.a << " -> " << u.b;
}

bool inPlane(const Point &p, const Plane &u) {
    return signum(det(u.b - u.a, p - u.a)) > 0;
}

bool operator <(const Plane &u, const Plane &v) {
    if (u.quad() == v.quad()) {
        int ret = signum(det(u.dir(), v.dir()));
        if (ret == 0) {
            return inPlane(u.a, v);
        }
        return ret > 0;
    }
    return u.quad() < v.quad();
}

bool operator ==(const Plane &u, const Plane &v) {
    return u.quad() == v.quad() && signum(det(u.dir(), v.dir())) == 0;
}

Point intersect(const Plane &u, const Plane &v) {
    return intersect(u.a, u.b, v.a, v.b);
}

bool check(const Plane &u, const Plane &v, const Plane &w) {
    Point p = intersect(u, v);
    return inPlane(p, w);
}

const int N = 100004;

int n;
Plane queue[N];

int main() {
    vector <Plane> planes;
    double x_1, y_1, x_2, y_2;
    scanf("%lf%lf%lf%lf", &x_1, &y_1, &x_2, &y_2);
    planes.push_back(Plane(Point(x_1, y_1), Point(x_2, y_1)));
    planes.push_back(Plane(Point(x_2, y_1), Point(x_2, y_2)));
    planes.push_back(Plane(Point(x_2, y_2), Point(x_1, y_2)));
    planes.push_back(Plane(Point(x_1, y_2), Point(x_1, y_1)));
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        Point o, a, b;
        scanf("%lf%lf%lf%lf%lf%lf", &o.x, &o.y, &a.x, &a.y, &b.x, &b.y);
        if (signum(det(a - o, b - o)) < 0) {
            swap(a, b);
        }
        planes.push_back(Plane(o, a));
        planes.push_back(Plane(b, o));
    }
    sort(planes.begin(), planes.end());
    planes.erase(unique(planes.begin(), planes.end()), planes.end());
//for (int i = 0; i < (int)planes.size(); ++ i) {
//    cout << planes[i] << endl;
//}
    int head = 0;
    int tail = 0;
    for (int i = 0; i < (int)planes.size(); ++ i) {
        while (tail - head > 1 && !check(queue[tail - 2], queue[tail - 1], planes[i])) {
            tail --;
        }
        while (tail - head > 1 && !check(queue[head + 1], queue[head], planes[i])) {
            head ++;
        }
        queue[tail ++] = planes[i];
    }
    while (tail - head > 2 && !check(queue[tail - 2], queue[tail - 1], queue[head])) {
        tail --;
    }
    while (tail - head > 2 && !check(queue[head + 1], queue[head], queue[tail - 1])) {
        head ++;
    }
    if (tail - head < 3) {
        puts("0.00");
    } else {
        vector <Point> polyon;
        for (int i = head; i < tail; ++ i) {
            polyon.push_back(intersect(queue[i], queue[head + (i - head + 1) % (tail - head)]));
        }
        double area = 0;
        for (int i = 0; i < (int)polyon.size(); ++ i) {
            area += det(polyon[i], polyon[(i + 1) % (int)polyon.size()]);
        }
        printf("%.2f\n", area / 2.0);
    }
    return 0;
}
