#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 50001;

int n, m;
pair <int, int> points[N];
long long dp[2][N];

struct Data {
    long long start, slope;

    Data(long long start = 0, long long slope = 0): start(start), slope(slope) {}

    inline long long evaluate(long long x) {
        return start + slope * x;
    }
};

inline double intersect(const Data &a, const Data &b) {
    return -(double)(a.start - b.start) / (a.slope - b.slope);
}

Data queue[N];
double intersections[N];

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%d%d", &points[i].first, &points[i].second);
        }
        sort(points + 1, points + 1 + n);
        int top = 0;
        for (int i = 1; i <= n; ++ i) {
            while (top > 0 && points[top].second <= points[i].second) {
                top --;
            }
            points[++ top] = points[i];
        }
        n = top;
        dp[1][0] = 0;
        for (int i = 1; i <= n; ++ i) {
            dp[1][i] = (long long)points[i].first * points[1].second;
        }
        m = min(n, m);
        for (int k = 2; k <= m; ++ k) {
            int head = 0;
            int tail = 0;
            for (int i = 0; i <= n; ++ i) {
                if (i == 0) {
                    dp[k & 1][i] = 0;
                } else {
                    while (tail - head >= 2) {
                        if (points[i].first < intersections[head + 1]) {
                            break;
                        }
                        head ++;
                    }
                    dp[k & 1][i] = queue[head].evaluate(points[i].first);
                }
                if (i < n) {
                    Data newData(dp[k + 1 & 1][i], points[i + 1].second);
                    while (tail - head >= 2) {
                        if (intersections[tail - 1] < intersect(queue[tail - 1], newData)) {
                            break;
                        }
                        tail --;
                    }
                    queue[tail++] = newData;
                    if (tail - head >= 2) {
                        intersections[tail - 1] = intersect(queue[tail - 2], queue[tail - 1]);
                    }
                }
            }
        }
        cout << dp[m & 1][n] << endl;
    }
    return 0;
}
