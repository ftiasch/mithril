#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int N = 500;
const long long INF = 1000000000000000000LL;

int n, sum[N + 1];
std::pair <int, int> a[N];
long long cost[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    std::sort(a, a + n);
    sum[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        sum[i] = sum[i + 1] + a[i].second;
    }
    for (int i = n - 1; i >= 0; -- i) {
        for (int j = i; j < n; ++ j) {
            cost[i][j] = INF;
            for (int k = i; k <= j; ++ k) {
                long long tmp = 0;
                if (i <= k - 1) {
                    tmp += cost[i][k - 1];
                }
                if (k + 1 <= j) {
                    tmp += cost[k + 1][j];
                }
                cost[i][j] = std::min(cost[i][j], tmp);
            }
            cost[i][j] += sum[i] - sum[j + 1];
        }
    }
    std::cout << cost[0][n - 1] - sum[0] << std::endl;
    return 0;
}
