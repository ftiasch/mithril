#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;


struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    Point &operator -=(const Point &o) {
        x -= o.x, y -= o.y;
        return *this;
    }

    double norm() const {
        return sqrt(x * x + y * y);
    }
};

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y;
}

Point operator -(Point a, const Point &b) {
    return a -= b;
}

const double EPS = 1e-8;
const double PI = acos(-1.0);

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double area(double r, Point pa, Point pb) {
    if (pa.norm() < pb.norm()) {
        swap(pa, pb);
    }
    if (pb.norm() < EPS) {
        return 0;
    }
    double a = pb.norm();
    double b = pa.norm();
    double c = (pb - pa).norm();
    double cosB = dot(pb,  pb - pa) / a / c;
    double B = acos(cosB);
    double cosC = dot(pa, pb) / a / b;
    double C = acos(cosC);
    double S = 0.0;
    if (a > r) {
        S = C / 2 * r * r;
        double h = a * b * sin(C) / c;
        if (h < r && B < PI / 2) {
            S -= (acos(h / r) * r * r - h * sqrt(r * r - h * h));
        }
    } else if (b > r) {
        double theta = PI - B - asin(sin(B) / r * a);
        S = 0.5 * a * r * sin(theta) + (C - theta) / 2 * r * r;
    } else {
        S = 0.5 * sin(C) * a * b;
    }
    return S;
}

int sign(double x) {
    return x < -EPS? -1: x > EPS;
}

int main() {
    while (true) {
        double x_0, y_0, v_0, theta, t_0, g, r;
        cin >> x_0 >> y_0 >> v_0 >> theta >> t_0 >> g >> r;
        if (sign(x_0) == 0 && sign(y_0) == 0 
                && sign(v_0) == 0 && sign(theta) == 0 
                && sign(t_0) == 0 && sign(g) == 0 && sign(r) == 0) {
            break;
        }
        theta = theta / 180 * PI;
        double v_x = v_0 * cos(theta);
        double v_y = v_0 * sin(theta);
        x_0 += v_x * t_0;
        y_0 += v_y * t_0 - 0.5 * g * t_0 * t_0;
        int n;
        scanf("%d", &n);
        vector <Point> points(n);
        for (int i = 0; i < n; ++ i) {
            cin >> points[i];
            points[i] -= Point(x_0, y_0);
        }
        double result = 0;
        for (int i = 0; i < n; ++ i) {
            result += area(r, points[i], points[(i + 1) % n])
                * sign(det(points[i], points[(i + 1) % n]));
        }
        printf("%.2f\n", fabs(result));
    }
    return 0;
}
