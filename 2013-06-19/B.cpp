#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
 
char buffer[51];

const int N = 101;

int n, go[N][2], end[N], fail[N];

long double coef[N][N + 1];

int main() {
    n = 1;
    memset(go, -1, sizeof(go));
    memset(end, 0, sizeof(end));
    for (int i = 0; i < 2; ++ i) {
        scanf("%s", buffer);
        int p = 0;
        for (int j = 0; buffer[j]; ++ j) {
            int t = buffer[j] - '0';
            if (go[p][t] == -1) {
                go[p][t] = n ++;
            }
            p = go[p][t];
        }
        end[p] |= 1 << i;
    }
    std::queue <int> queue;
    for (int t = 0; t < 2; ++ t) {
        int &v = go[0][t];
        if (v == -1) {
            v = 0;
        } else {
            queue.push(v);
            fail[v] = 0;
        }
    }
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        end[u] |= end[fail[u]];
        for (int t = 0; t < 2; ++ t) {
            int &v = go[u][t];
            if (v == -1) {
                v = go[fail[u]][t];
            } else {
                fail[v] = go[fail[u]][t];
                queue.push(v);
            }
        }
    }
    memset(coef, 0, sizeof(coef));
    for (int u = 0; u < n; ++ u) {
        coef[u][u] = 1.0;
        if (end[u] == 1) {
            coef[u][n] = 1.0;
        } else if (end[u] == 2) {
            coef[u][n] = 0.0;
        } else {
            for (int t = 0; t < 2; ++ t) {
                int v = go[u][t];
                coef[u][v] += -0.5;
            }
        }
    }
    for (int j = 0; j < n; ++ j) {
        int i = j;
        for (int p = j; p < n; ++ p) {
            if (fabs(coef[p][j]) > fabs(coef[i][j])) {
                i = p;
            }
        }
        for (int k = 0; k <= n; ++ k) {
            std::swap(coef[i][k], coef[j][k]);
        }
        for (int i = 0; i < n; ++ i) {
            if (i != j) {
                long double tmp = coef[i][j] / coef[j][j];
                for (int k = 0; k <= n; ++ k) {
                    coef[i][k] -= tmp * coef[j][k];
                }
            }
        }
    }
    printf("%.10f\n", (double)(coef[0][n] / coef[0][0]));
    return 0;
}
