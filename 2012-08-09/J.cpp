#include <cstdio>
#include <cstring>
using namespace std;

int n, p, mask1, mask2;

struct Matrix {
    int data[64][64];

    Matrix(bool id = false) {
        memset(data, 0, sizeof(data));
        if (id) {
            for (int i = 0; i < 64; ++ i) {
                data[i][i] = 1;
            }
        }
    }

    int* operator[](int i) { 
        return data[i];
    }

    const int* operator[](int i) const {
        return data[i];
    }
};

Matrix operator *(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < 64; ++ i) {
        for (int j = 0; j < 64; ++ j) {
            long long ret = 0;
            for (int k = 0; k < 64; ++ k) {
                ret += (long long)a[i][k] * b[k][j];
            }
            c[i][j] = ret % p;
        }
    }
    return c;
}

Matrix powMod(Matrix a, int n) {
    Matrix result(true);
    while (n) {
        if (n & 1) {
            result = result * a;
        }
        a = a * a;
        n >>= 1;
    }
    return result;
}

int main() {
    scanf("%d%d", &n, &p);
    mask1 = mask2 = 0;
    for (int i = 0; i < 3; ++ i) {
        for (int j = 0; j < 3; ++ j) {
            char buffer[2];
            scanf("%s", buffer);
            if (*buffer != 'X') {
                mask1 |= 1 << (i + j * 3);
                mask2 |= (*buffer == '1') << (i + j * 3);
            }
        }
    }
//printf("%d %d\n",mask1,mask2);
    Matrix t;
    for (int mask = 0; mask < 64; ++ mask) {
        for (int i = 0; i < 8; ++ i) {
            int newMask = mask | (i << 6);
            if ((newMask & mask1) != mask2) {
                t[mask][(mask | (i << 6)) >> 3] += 1;
            }
        }
    }
    Matrix a;
    for (int mask = 0; mask < 64; ++ mask) {
        a[0][mask] = 1;
    }
    a = a * powMod(t, n - 2);
    int result = 0;
    for (int mask = 0; mask < 64; ++ mask) {
        result = (result + a[0][mask]) % p;
    }
    printf("%d\n", result);
    return 0;
}
