#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100000;
const long long INF = 1000000000000000000LL;

int signum(long long x) {
    return x < 0? -1: x > 0;
}

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}

    Point negate() const {
        return Point(-x, -y);
    }
};

bool operator <(const Point &a, const Point &b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool operator ==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

long long dot(const Point &a, const Point &b) {
    return (long long)a.x * b.x + (long long)a.y * b.y;
}

int n, m, a[N], b[N], c[N];
Point points[N];

bool isValid(const Point &a, const Point &b, const Point &c) {
    return det(b - a, c - b) > 0;
}

void append(vector <Point> &chain, const Point &p) {
    while ((int)chain.size() > 1 && !isValid(chain[(int)chain.size() - 2], chain.back(), p)) {
        chain.pop_back();
    }
    chain.push_back(p);
}

long long findMaximum(vector <Point> &chain, const Point &p) {
    int low = 0;
    int high = (int)chain.size() - 1;
    while (high - low > 3) {
        int middle = (low + high) >> 1;
        if (dot(p, chain[middle]) < dot(p, chain[middle + 1])) {
            low = middle;
        } else {
            high = middle + 1;
        }
    }
    long long result = -INF;
    for (int i = low; i <= high; ++ i) {
        result = max(result, dot(p, chain[i]));
    }
    return result;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", a + i, b + i, c + i);
    }
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }
    sort(points, points + m);
    m = unique(points, points + m) - points;
    vector <Point> lowChain;
    for (int i = 0; i < m; ++ i) {
        append(lowChain, points[i]);
    }
    vector <Point> highChain;
    for (int i = m - 1; i >= 0; -- i) {
        append(highChain, points[i]);
    }
    vector <int> result;
    for (int i = 0; i < n; ++ i) {
        Point p(a[i], b[i]);
        long long maxDot = max(findMaximum(lowChain, p), findMaximum(highChain, p));
        p = p.negate();
        long long minDot = -max(findMaximum(lowChain, p), findMaximum(highChain, p));
        if (signum(c[i] + maxDot) * signum(c[i] + minDot) <= 0) {
            result.push_back(i);
        }
    }
    printf("%d\n", (int)result.size());
    for (int i = 0; i < (int)result.size(); ++ i) {
        printf("%d%c", result[i] + 1, i == (int)result.size() - 1? '\n': ' ');
    }
    return 0;
}
