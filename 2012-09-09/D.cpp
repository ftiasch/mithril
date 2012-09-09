#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 16;
const int INF = 1000000000;
const double EPSILON = 1e-10;

int n, limit, x[N], y[N], d[N][N], c[N], sum[1 << N], need[1 << N], travel[1 << N][N], weight[1<<N];

int sqr(int x) {
    return x * x;
}

int task1() {
    need[0] = 0;
    for (int mask = 1; mask < 1 << n; ++ mask) {
        need[mask] = INF;
        for (int subMask = mask; subMask > 0; subMask = (subMask - 1) & mask) {
            if (sum[subMask] <= limit) {
                need[mask] = min(need[mask], need[mask ^ subMask] + 1);
            }
        }
    }
    int result = need[(1 << n) - 1];
    return result == INF? -1: result;
}


void update(int &x, int a) {
    if (x == -1 || x > a) {
        x = a;
    }
}

int task2() {
    memset(travel, -1, sizeof(travel));
    for (int i = 0; i < n; ++ i) {
        travel[1 << i][i] = d[i][n];
    }
    memset(weight, -1, sizeof(weight));
    for (int mask = 0; mask < 1 << n; ++ mask) {
        for (int i = 0; i < n; ++ i) {
            if (travel[mask][i] != -1) {
                if (sum[mask] <= limit) {
                    update(weight[mask], travel[mask][i] + d[i][n]);
                }
                for (int j = 0; j < n; ++ j) {
                    if ((mask >> j & 1) == 0) {
                        update(travel[mask | (1 << j)][j], travel[mask][i] + d[i][j]);
                    }
                }
            }
        }
    }
    need[0] = 0;
    for (int mask = 1; mask < 1 << n; ++ mask) {
        need[mask] = INF;
        for (int subMask = mask; subMask > 0; subMask = (subMask - 1) & mask) {
            if (weight[subMask] != -1) {
                need[mask] = min(need[mask], need[mask ^ subMask] + weight[subMask]);
            }
        }
    }
    int result = need[(1 << n) - 1];
    return result == INF? -1: result;
}

int main() {
    while (scanf("%d%d", &n, &limit) == 2) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", x + i, y + i);
        }
        n --;
        swap(x[0], x[n]);
        swap(y[0], y[n]);
        for (int i = 0; i <= n; ++ i) {
            for (int j = 0; j <= n; ++ j) {
                int l=-1,r=1001;
                int xx= sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
                while (l+1<r){
                    int mid=(l+r)/2;
                    if (mid*mid>=xx) r=mid;
                    else l=mid;
                }
                d[i][j] = r;
            }
        }
        for (int i = 0; i <= n; ++ i) {
            scanf("%d", c + i);
        }
        swap(c[0], c[n]);
        sum[0] = 0;
        for (int mask = 1; mask < 1 << n; ++ mask) {
            int i = 0;
            while ((mask >> i & 1) == 0) {
                i ++;
            }
            sum[mask] = sum[mask ^ (1 << i)] + c[i];
        }
        printf("%d %d\n", task1(), task2());
    }
    return 0;
}
