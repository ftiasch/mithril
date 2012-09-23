#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int SEARCH_TIME = 50;
const double EPS = 1e-9;

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    double norm() const {
        return sqrt(x * x + y * y);
    }

    double to(const Point &, const Point&) const;
};

istream &operator >>(istream &in, Point &p) { return in >> p.x >> p.y; }

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

const int N = 8;

int n, delta[3];
bool valid[N][N];
Point points[N];

double lambda;

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

int sign(double x) {
    return x < -EPS? -1: x > EPS;
}

bool cute(const Point &a, const Point &b) {
    if (sign(a.norm()) <= 0) {
        return true;
    }
    return sign(dot(a, b) / a.norm()) >= 0;
}

double Point::to(const Point &a, const Point &b) const {
    Point p = *this;
    double result = min((p - a).norm(), (p - b).norm());
    if (cute(p - a, b - a) && cute(p - b, a - b)) {
        result = min(result, abs(det(a - p, b - p) / (a - b).norm()));
    }
    return result;
}

bool check(int a, int b, int c, int d) {
    if (points[b].to(points[c], points[d]) <= lambda
     && points[a].to(points[c], points[d]) <= lambda) {
     //&& points[c].to(points[a], points[b]) <= lambda
     //&& points[d].to(points[a], points[b]) <= lambda) {
        return true;
    }
    return false;
}

void dfs(int i, int j) {
    if (valid[i][j]) {
        return;
    }
    valid[i][j] = true;
    for (int x = 0; x < 3; ++ x) {
        for (int y = 0; y < 3; ++ y) {
            if (i == j && x == y) continue;
            if (check(i, (i + delta[x]) % n, j, (j + delta[y]) % n)) {
                dfs((i + delta[x]) % n, (j + delta[y]) % n);
            }
        }
    }
}

bool check() {
    for (int start = 0; start < n; ++ start) {
        memset(valid, 0, sizeof(valid));
        dfs(start, start);
        for (int target = 0; target < n; ++ target) {
            if (start != target && valid[target][target]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    while (scanf("%d", &n) == 1 && n > 0) {
        for (int i = 0; i < n; ++ i) {
            cin >> points[i];
        }
        delta[0] = 1;
        delta[1] = n - 1;
        double low = 0.0;
        double high = 400000.0;
        for (int _ = 0; _ < SEARCH_TIME; ++ _) {
            double middle = (low + high) / 2.0;
            lambda = middle;
            if (check()) {
                high = middle;
            } else {
                low = middle;
            }
        }
        double middle = (low + high) / 2.0;
        printf("%.2f\n", middle);
    }
    return 0;
}
