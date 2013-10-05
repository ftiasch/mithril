#include <cstdio>
#include <cstring>

int n, m, a, b, c, t;

const int N = 50;

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

Matrix operator *(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            for (int k = 0; k < n; ++ k) {
                (c[i][j] += a[i][k] * b[k][j]) %= m;
            }
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

int main() {
    while (scanf("%d%d%d%d%d%d", &n, &m, &a, &b, &c, &t) == 6 && n) {
        Matrix seed;
        for (int i = 0; i < n; ++ i) {
            scanf("%d", &seed[0][i]);
        }
        Matrix transfer;
        for (int i = 0; i < n; ++ i) {
            if (i - 1 >= 0) {
                transfer[i][i - 1] = c;
            }
            transfer[i][i] = b;
            if (i + 1 < n) {
                transfer[i][i + 1] = a;
            }
        }
        seed = seed * pow(transfer, t);
        for (int i = 0; i < n; ++ i) {
            printf("%d%c", seed[0][i], i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
