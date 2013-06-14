#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

const int N = 100;
const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}

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

    Point rotate60();
    
    int layer() const {
        return (int)floor(x / cos(PI / 6) + EPS) + 1;
    }
};

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

bool operator <(const Point &a, const Point &b) {
    if (signum(a.x - b.x) != 0) {
        return signum(a.x - b.x) < 0;
    }
    return signum(a.y - b.y) < 0;
}

bool operator ==(const Point &a, const Point &b) {
    return signum(a.x - b.x) == 0 && signum(a.y - b.y) == 0;
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

Point operator *(const Point &a, const Point &b) {
    return Point(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

Point Point::rotate60() {
    return (*this) * Point(cos(PI / 3), sin(PI / 3));
}

long long answer[N + 1];

int main() {
    std::vector <Point> points;
    Point a(cos(-PI / 6), sin(-PI / 6));
    Point b(cos(PI / 6), sin(PI / 6));
    for (int i = 0; i < N; ++ i) {
        for (int j = 0; i + j < N; ++ j) {
            points.push_back(a * i + b * j);
        }
    }
    std::sort(points.begin(), points.end());
    int m = points.size();
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (i != j) {
                Point p(points[i] + (points[j] - points[i]).rotate60());
                std::vector <Point> :: iterator iter = std::lower_bound(points.begin(), points.end(), p);
                if (iter != points.end() && (*iter) == p) {
                    answer[std::max(p.layer(), std::max(points[i].layer(), points[j].layer()))] ++;
                }
            }
        }
    }
    for (int i = 1; i <= N; ++ i) {
        answer[i] += answer[i - 1];
    }
    for (int i = 2; i <= N; ++ i) {
        printf("%lld, ", answer[i]);
    }
    //int n;
    //while (scanf("%d", &n) == 1 && n) {
    //    std::cout << answer[n] / 3 << std::endl;
    //}
    return 0;
}
