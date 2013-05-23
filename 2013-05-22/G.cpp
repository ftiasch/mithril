#include <cstdio>
#include <cstring>
 
const int MOD = 1000000000 + 9;
 
const int N = 20;
 
int n, m, k, d;
 
struct Matrix {
    int matrix[N][N];
 
    Matrix(bool id = false) {
        memset(matrix, 0, sizeof(matrix));
        if (id) {
            for (int i = 0; i < n; ++ i) {
                matrix[i][i] = 1;
            }
        }
    }
 
    int* operator[](int i) {
        return matrix[i];
    }
 
    const int* operator[](int i) const {
        return matrix[i];
    }
};
 
Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            long long tmp = 0;
            for (int k = 0; k < n; ++ k) {
                tmp += (long long)a[i][k] * b[k][j] % MOD;
            }
            c[i][j] = tmp % MOD;
        }
    }
    return c;
}
 
Matrix pow(Matrix a, int n) {
    Matrix ret(true);
    while (n) {
        if (n & 1) {
            ret = ret * a;
        }
        a = a * a;
        n >>= 1;
    }
    return ret;
}
 
Matrix adjacent;
 
int main() {
    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &k, &d);
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b --;
        adjacent[a][b] ++;
        adjacent[b][a] ++;
    }
    int answer = 0;
    for (int mask = 0; mask < 1 << k; ++ mask) {
        Matrix now;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if ((mask >> i & 1) || (mask >> j & 1)) {
                    continue;
                }
                now[i][j] = adjacent[i][j];
            }
        }
        int ways = 0;
        if (d == 1) {
            for (int i = 0; i < n; ++ i) {
                if (~mask >> i & 1) {
                    ways ++;
                }
            }
        } else {
            now = pow(now, d - 1);
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < n; ++ j) {
                    (ways += now[i][j]) %= MOD;
                }
            }
        }
        if (__builtin_popcount(mask) & 1) {
            (answer += MOD - ways) %= MOD;
        } else {
            (answer += ways) %= MOD;
        }
    }
    printf("%d\n", answer);
    return 0;
}
