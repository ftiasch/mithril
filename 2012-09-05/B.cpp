#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}

    int norm2() const {
        return x * x + y * y;
    }
};

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y;
}

int det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

const int N = 201;
const int M = 40001;

int n, m, cost[N], value[N];
Point point[N];

int order[N], maximum[N][M];

bool compare(int i, int j) {
    int ret = det(point[i], point[j]);
    if (ret == 0) {
        return point[i].norm2() < point[j].norm2();
    }
    return ret > 0;
}

int main() {
    int testCount =0;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; ++ i) {
            cin >> point[i] >> cost[i] >> value[i];
        }
        for (int i = 0; i < n; ++ i) {
            order[i] = i;
        }
        sort(order, order + n, compare);
        memset(maximum, 0, sizeof(maximum));
        for (int i = n - 1; i >= 0; -- i) {
            int j = i;
            while (j < n && det(point[order[i]], point[order[j]]) == 0) {
                j ++;
            }
            for (int k = 0; k <= m; ++ k) {
                maximum[i][k] = maximum[j][k];
                int iter = order[i];
                if (k >= cost[iter]) {
                    maximum[i][k] = max(maximum[i][k], maximum[i + 1][k - cost[iter]] + value[iter]);
                }
            }
        }
        printf("Case %d: %d\n", ++ testCount, maximum[0][m]);
    }
    return 0;
}
