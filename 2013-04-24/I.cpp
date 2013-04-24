#include <cstdio>
#include <cstring>

const int N = 100000;

int n, m, a[N], b[N];

struct Matrix {
    int matrix[2][2];

    Matrix(bool id = false) {
        memset(matrix, 0, sizeof(matrix));
        if (id) {
            matrix[0][0] = matrix[1][1] = 1;
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
    for (int i = 0; i < 2; ++ i) {
        for (int j = 0; j < 2; ++ j) {
            for (int k = 0; k < 2; ++ k) {
                (c[i][j] += (long long)a[i][k] * b[k][j] % m) %= m;
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
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", b + i);
    }
    int answer = 0;
    for (int i = 0; i < n; ++ i) {
        Matrix transform;
        transform[0][0] = 10;
        transform[1][0] = a[i];
        transform[1][1] = 1;
        Matrix seed;
        seed[0][0] = answer;
        seed[0][1] = 1;
        seed = seed * pow(transform, b[i]);
        answer = seed[0][0];
    }
    printf("%d\n", answer);
    return 0;
}
