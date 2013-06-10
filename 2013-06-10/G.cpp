#include <cstdio>
#include <cstring>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>

int n, m;

namespace gxx
{
const int N = 5001;
const long long INF = 1000000000000000000LL;

int a[N], sum[N], cost[N][N], candidate[N], start[N];
long long minimum[2][N];

inline int get_sum(int i, int j) {
    return sum[i] - sum[j + 1];
}

int main() {
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    std::sort(a, a + n);
    sum[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        sum[i] = sum[i + 1] + a[i];
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = i; j < n; ++ j) {
            int k = i + j >> 1;
            int middle = a[k];
            cost[i][j + 1] = (long long)middle * (k - i + 1) - get_sum(i, k) + get_sum(k + 1, j) - middle * (j - k);
        }
    }
    minimum[0][0] = 0;
    for (int j = 1; j <= n; ++ j) {
        minimum[0][j] = INF;
    }
    for (int j = 0; j < m; ++ j) {
        int top = 0;
        candidate[top] = 0;
        start[top ++] = 0;
        for (int i = 1; i <= n; ++ i) {
            if (minimum[j & 1][i] == INF) {
                continue;
            }
            int p, s;
            while (top) {
                p = candidate[top - 1];
                s = start[top - 1];
                if (s <= i || minimum[j & 1][p] + cost[p][s] < minimum[j & 1][i] + cost[i][s]) {
                    break;
                }
                top --;
            }
            int low = std::max(s, i + 1);
            int high = n + 1;
            while (low < high) {
                int middle = low + high >> 1;
                if (minimum[j & 1][p] + cost[p][middle] > minimum[j & 1][i] + cost[i][middle]) {
                    high = middle;
                } else {
                    low = middle + 1;
                }
            }
            if (low <= n) {
                candidate[top] = i;
                start[top ++] = low;
            }
        }
        minimum[j + 1 & 1][0] = 0;
        for (int i = 1, k = 0, p = -1; i <= n; ++ i) {
            if (k < top && start[k] <= i) {
                p = candidate[k ++];
            }
            minimum[j + 1 & 1][i] = minimum[j & 1][p] + cost[p][i];
        }
    }
    std::cout << minimum[m & 1][n] << std::endl;
    return 0;
}
};

const int N = 5001;
const unsigned INF = 2000000000;

int a[N], sum[N], cost[N][N];
unsigned minimum[2][N], g[2][N];

inline int get_sum(int i, int j) {
    return sum[i] - sum[j + 1];
}

int main() {
    scanf("%d%d", &n, &m);
//    m = 700;
    if (m <= 1000) {
        gxx::main();
        return 0;
    }
    
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    std::sort(a, a + n);
    sum[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        sum[i] = sum[i + 1] + a[i];
    }
    for (int j = 1; j < n; ++ j) {
        int* costj = cost[j + 1];
        for (int i = 0; i < j; ++ i) {
            int k = i + j >> 1;
            int middle = a[k];
            costj[i] = middle * (k - i + 1) - get_sum(i, k) + get_sum(k + 1, j) - middle * (j - k);
        }
    }

    minimum[0][0] = 0;
    for (int j = 1; j <= n; ++ j) {
        minimum[0][j] = INF;
        g[0][j] = 0;
    }
    int now = 0, old = 1;
    for (int j = 1; j <= m; ++ j) {
        now = 1 - now;
        old = 1 - old;
        minimum[now][0] = 0;
        g[now][0] = 0;
        for (int i = 1; i <= n; ++ i) {
            int* costi = cost[i];
            int cnt = 0;
            minimum[now][i] = INF;
            for (int p = std::max(g[now][i - 1], g[old][i]); p < i && cnt <= 50; ++ p) {
                if (minimum[old][p] + costi[p] <= minimum[now][i]) {
                    minimum[now][i] = minimum[old][p] + costi[p];
                    g[now][i] = p;
                    cnt = 0;
                } else {
                    cnt ++;
                }
            }
        }
    }
    std::cout << minimum[now][n] << std::endl;
    return 0;
}

