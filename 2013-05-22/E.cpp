#include <cstdio>
#include <cstring>
 
const int N = 200 + 1;
 
int n, d, p, inverse[N], ways[N][N], exactly[N][N], tmp[N];
 
int main() {
    freopen("enumeration.in", "r", stdin);
    freopen("enumeration.out", "w", stdout);
    scanf("%d%d%d", &n, &d, &p);
    if (d == 0) {
        printf("%d\n", n == 1);
        return 0;
    }
    inverse[1] = 1;
    for (int i = 2; i <= n; ++ i) {
        inverse[i] = (long long)(p - p / i) * inverse[p % i] % p;
    }
    memset(ways, 0, sizeof(ways));
    memset(exactly, 0, sizeof(exactly));
    ways[0][1] = exactly[0][1] = 1;
    int d2 = d / 2;
    for (int d = 1; d <= d2; ++ d) {
        memset(tmp, 0, sizeof(tmp));
        tmp[0] = 1;
        for (int x = 1; x <= n; ++ x) {
            for (int k = n; k >= 0; -- k) {
                long long binom = 1;
                for (int i = 1; k + x * i <= n; ++ i) {
                    (binom *= (ways[d - 1][x] + i - 1)) %= p;
                    (binom *= inverse[i]) %= p;
                    (tmp[k + x * i] += (long long)tmp[k] * binom % p) %= p;
                }
            }
        }
        for (int k = 1; k <= n; ++ k) {
            ways[d][k] = exactly[d][k] = tmp[k - 1];
            (exactly[d][k] -= ways[d - 1][k]) %= p;
        }
    }
 
    int answer = 0;
    if (d % 2 == 1) {
        for (int i = 1; i < n - i; ++ i) {
            (answer += (long long)exactly[d2][i] * exactly[d2][n - i] % p) %= p;
        }
        if (n % 2 == 0) {
            int n2 = n >> 1;
            (answer += (long long)exactly[d2][n2] * (exactly[d2][n2] + 1) / 2 % p) %= p;
        }
    } else {
        answer = exactly[d2][n];
        for (int i = 1; i <= n - 1; ++ i) {
            (answer -= (long long)exactly[d2 - 1][i] * ways[d2 - 1][n - i] % p) %= p;
        }
    }
    printf("%d\n", (answer + p) % p);
    return 0;
}
