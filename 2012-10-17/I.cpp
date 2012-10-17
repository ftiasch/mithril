#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;

// {{{ Point class

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}

    Point &operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    int quadrant() const {
        if (x > 0 && y >= 0) {
            return 0;
        }
        if (y > 0 && x <= 0) {
            return 1;
        }
        if (x < 0 && y <= 0) {
            return 2;
        }
        return 3;
    }

    int norm2() const;

    bool in(const Point &, const Point&) const;
};

Point operator -(Point a, const Point &b) {
    return a -= b;
}

long long dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

long long det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

int Point::norm2() const {
    return dot(*this, *this);
}

bool Point::in(const Point &a, const Point &b) const {
    Point p = *this;
    long long area = abs(det(a, b));
    area -= abs(det(Point() - p, a - p));
    area -= abs(det(a - p, b - p));
    area -= abs(det(b - p, Point() - p));
    return area == 0;
}

bool operator <(const Point &a, const Point &b) {
    if (a.quadrant() == b.quadrant()) {
        return det(a, b) > 0;
    }
    return a.quadrant() < b.quadrant();
}

bool operator ==(const Point &a, const Point &b) {
    return a.quadrant() == b.quadrant() && det(a, b) == 0;
}

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y;
}

/// }}}

const int N = 100000;

int n, m;
Point polygon[N];

map <Point, int> farest;

bool check(const Point &p) {
    int low = -1;
    int high = n - 1;
    while (low < high) {
        int middle = (low + high + 1) >> 1;
        if (p < polygon[middle]) {
            high = middle - 1;
        } else {
// polygon[middle] <= p
            low = middle;
        }
    }
//printf("%d, %d\n", low, high);
    int i = (low + n) % n;
    if (polygon[i] == p) {
        return p.norm2() <= farest[p];
    }
//printf("polygon %d = %d %d\n", i, polygon[i].x, polygon[i].y);
    int j = (i + 1) % n;
    return p.in(polygon[i], polygon[j]);
}

int main() {
    freopen("stars.in", "r", stdin);
    freopen("stars.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; ++ i) {
        cin >> polygon[i];
    }
    long long area = 0;
    for (int i = 0; i < n; ++ i) {
        area += det(polygon[i], polygon[(i + 1) % n]);
    }
    if (area < 0) {
        reverse(polygon, polygon + n);
    }
    {
        int i = 0;
        for (int j = 0; j < n; ++ j) {
            if (polygon[j] < polygon[i]) {
                i = j;
            }
        }
        rotate(polygon, polygon + i, polygon + n);
    }
    for (int i = 0; i < n; ++ i) {
        int &ret = farest[polygon[i]];
        ret = max(ret, polygon[i].norm2());
    }
    int result = 0;
    while (m --) {
        Point p;
        cin >> p;
//printf("chech %d %d = %d\n", p.x, p.y, (int)check(p));
        result += check(p);
    }
    cout << result << endl;
    return 0;
}
