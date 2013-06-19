#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int C = 100;
const int MOD = (int)1e9 + 7;

long long n;
int c, m;

struct Matrix {
    int matrix[C][C];

    Matrix(bool id = false) {
        memset(matrix, 0, sizeof(matrix));
        if (id) {
            for (int i = 0; i < c; ++ i) {
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

Matrix operator *(const Matrix &a, const Matrix &b) {
    Matrix ret;
    for (int i = 0; i < c; ++ i) {
        for (int j = 0; j < c; ++ j) {
            long long tmp = 0;
            for (int k = 0; k < c; ++ k) {
                (tmp += (long long)a[i][k] * b[k][j] % MOD) %= MOD;
            }
            ret[i][j] = tmp;
        }
    }
    return ret;
}

Matrix pow(Matrix a, long long n) {
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

int main() {
    std::cin >> n >> c >> m;
    Matrix transfer;
    for (int i = 0; i < c; ++ i) {
        for (int j = 0; j < c; ++ j) {
            transfer[i][j] = 1;
        }
    }
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b --;
        transfer[a][b] = transfer[b][a] = 0;
    }
    Matrix seed;
    for (int i = 0; i < c; ++ i) {
        seed[0][i] = 1;
    }
    seed = seed * pow(transfer, n - 1);
    long long answer = 0;
    for (int i = 0; i < c; ++ i) {
        (answer += seed[0][i]) %= MOD;
    }
    std::cout << answer << std::endl;
    return 0;
}
