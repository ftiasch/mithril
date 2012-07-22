#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const double EPSILON = 1e-10;
const double RADIUS = 10000;

int signum(double x) {
    return x < -EPSILON? -1: x > EPSILON;
}

const int N = 100000;

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    double norm2() const {
        return x * x + y * y;
    }

    double norm() const {
        return sqrt(norm2());
    }
};

bool operator <(const Point &a, const Point &b) {
    if (signum(a.x - b.x) == 0) {
        return signum(a.y - b.y) < 0;
    }
    return signum(a.x - b.x) < 0;
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator *(const Point &a, double k) {
    return Point(a.x * k, a.y * k);
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

int n, order[N];
bool isGood[N];
Point points[N];

bool valid(const Point &a, const Point &b, const Point &c) {
    if (signum((a - b).norm()) == 0 || signum((b - c).norm()) == 0) {
        return false;
    }
    return signum(det(b - a, c - b) / (b - a).norm()) > 0;
}

void append(vector <Point> &chain, const Point &p) {
    while ((int)chain.size() > 1 && !valid(chain[(int)chain.size() - 2], chain.back(), p)) {
        chain.pop_back();
    }
    chain.push_back(p);
}

bool find(vector <Point> &chain, const Point &p) {
    if (chain.empty()) {
        return false;
    }
    int low = 0;
    int high = (int)chain.size() - 1;
    double result = dot(p, chain[low]);
    for (int i = low; i < high; ++ i) {
        result = max(result, dot(p, chain[i]));
    }
    return signum((result - p.norm2()) / p.norm()) >= 0;
}

void solve(int l, int r) {
    if (l + 1 < r) {
        int m = (l + r) >> 1;
        solve(m, r);
        vector <Point> goodPoints;
        for (int i = m; i < r; ++ i) {
            if (isGood[i]) {
                goodPoints.push_back(points[order[i]]);
            }
        }
        sort(goodPoints.begin(), goodPoints.end());
        vector <Point> lowChain;
        for (int i = 0; i < (int)goodPoints.size(); ++ i) {
            append(lowChain, goodPoints[i]);
        }
        vector <Point> upChain;
        for (int i = (int)goodPoints.size() - 1; i >= 0; -- i) {
            append(upChain, goodPoints[i]);
        }
        for (int i = l; i < m; ++ i) {
            if (isGood[i]) {
                isGood[i] &= !find(lowChain, points[order[i]]);
                isGood[i] &= !find(upChain, points[order[i]]);
            }
        }
        solve(l, m);
    }
}

bool compareByLength(int i, int j) {
    return signum(points[i].norm() - points[j].norm()) < 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%lf%lf", &points[i].x, &points[i].y);
        double l = points[i].norm2();
        points[i] = points[i] * (RADIUS / l);
    }
    for (int i = 0; i < n; ++ i) {
        order[i] = i;
    }
    sort(order, order + n, compareByLength);
    for (int i = 0; i < n; ++ i) {
        isGood[i] = true;
    }
    solve(0, n);
    vector <int> result;
    for (int i = 0; i < n; ++ i) {
        if (isGood[i]) {
            result.push_back(order[i] + 1);
        }
    }
    printf("%d\n", (int)result.size());
    sort(result.begin(), result.end());
    for (int i = 0; i < (int)result.size(); ++ i) {
        printf("%d%c", result[i], i == (int)result.size() - 1? '\n': ' ');
    }
    return 0;
}
