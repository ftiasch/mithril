#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;

int signum(double x) {
    return x < -EPS? -1: x > EPS;
}

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}
};

bool operator <(const Point &a, const Point &b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

const int N = 100001;

int n, order[N];
bool burned[N];
long long totalArea[N];
vector <Point> lowerChain[N], upperChain[N];

bool compare(int i, int j) {
    return totalArea[i] < totalArea[j];
}

double getIntersectionY(vector <Point> &chain, int x) {
    int lower = 1;
    int upper = (int)chain.size() - 1;
    while (lower < upper) {
        int mider = (lower + upper) >> 1;
        if (x <= chain[mider].x) {
            upper = mider;
        } else {
            lower = mider + 1;
        }
    }
    // upper - 1, upper
    return chain[upper].y - (double)(chain[upper].x - x) / (chain[upper].x - chain[upper - 1].x) * (chain[upper].y - chain[upper - 1].y);
}

bool isInside(const Point &p, int id) {
    if (id == n) {
        return true;
    }
    if (p.x <= lowerChain[id].front().x || p.x >= upperChain[id].back().x) {
        return false;
    }
    double lowerY = getIntersectionY(lowerChain[id], p.x);
    double upperY = getIntersectionY(upperChain[id], p.x);
    return (signum(p.y - lowerY) > 0) ^ (signum(p.y - upperY) > 0);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        int m;
        scanf("%d", &m);
        vector <Point> points(m);
        for (int j = 0; j < m; ++ j) {
            scanf("%d%d", &points[j].x, &points[j].y);
        }
        totalArea[i] = 0;
        for (int j = 0; j < m; ++ j) {
            totalArea[i] += det(points[j], points[(j + 1) % m]);
        }
        int lowerIndex = min_element(points.begin(), points.end()) - points.begin();
        int upperIndex = max_element(points.begin(), points.end()) - points.begin();
        for (int j = lowerIndex; j != upperIndex; j = (j + 1) % m) {
            lowerChain[i].push_back(points[j]);
        }
        lowerChain[i].push_back(points[upperIndex]);
        for (int j = upperIndex; j != lowerIndex; j = (j + 1) % m) {
            upperChain[i].push_back(points[j]);
        }
        upperChain[i].push_back(points[lowerIndex]);
        reverse(upperChain[i].begin(), upperChain[i].end());
    }
    for (int i = 0; i < n; ++ i) {
        order[i] = i;
    }
    sort(order, order + n, compare);
    memset(burned, 0, sizeof(burned));
    int m;
    scanf("%d", &m);
    while (m > 0) {
        m --;
        Point p;
        scanf("%d%d", &p.x, &p.y);
        int lower = 0;
        int upper = n;
        while (lower < upper) {
            int mider = (lower + upper) >> 1;
            if (isInside(p, order[mider])) {
                upper = mider;
            } else {
                lower = mider + 1;
            }
        }
        burned[upper] = true;
    }
    long long result = 0;
    for (int i = 0; i < n; ++ i) {
        if (burned[i]) {
            long long ret = totalArea[order[i]];
            if (i > 0) {
                ret -= totalArea[order[i - 1]];
            }
            result += ret;
        }
    }
    cout << (result / 2) << ((result & 1)? ".500000": ".000000" ) << endl;
    return 0;
}
