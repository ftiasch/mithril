#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 200;
const int L = 100000 + 1;

int n, m;
string patterns[N];
char buffer[L];

typedef long long LL;

struct Matrix {
    LL matrix[N][N];

    LL* operator[](int i) {
        return matrix[i];
    }
    
    const LL* operator[](int i) const {
        return matrix[i];
    }
};

const LL INF = 1000000000000000000LL;

Matrix operator *(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            LL ret = INF;
            for (int k = 0; k < n; ++ k) {
                ret = min(ret, a[i][k] + b[k][j]);
            }
            c[i][j] = ret;
        }
    }
    return c;
}

char text[L];
int fail[L];

Matrix powMod(const Matrix &a, int n) {
    if (n == 1) {
        return a;
    }
    Matrix ret = powMod(a, n >> 1);
    ret = ret * ret;
    if ((n & 1) == 1) {
        ret = ret * a;
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", buffer);
        patterns[i] = buffer;
    }
    Matrix transfer;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            int length = 0;
            for (int k = 0; k < (int)patterns[j].size(); ++ k) {
                text[length ++] = patterns[j][k];
            }
            for (int k = 0; k < (int)patterns[i].size(); ++ k) {
                text[length ++] = patterns[i][k];
            }
            fail[0] = -1;
            for (int k = 1; k < length; ++ k) {
                fail[k] = -1;
                int j = k - 1;
                while (j != -1) {
                    j = fail[j];
                    if (text[k] == text[j + 1]) {
                        fail[k] = j + 1;
                        break;
                    }
                }
            }
            int k = fail[length - 1];
            if (i == j) {
                while (k + 1 >= (int)patterns[i].size()) {
                    k = fail[k];
                }
                transfer[i][i] = (int)patterns[i].size() - (k + 1);
            } else {
                while (k + 1 > (int)patterns[i].size() || k + 1 > (int)patterns[i].size()) {
                    k = fail[k];
                }
                transfer[i][j] = (int)patterns[j].size() - (k + 1);
            }
        }
    }
    Matrix init;
    for (int i = 0; i < n; ++ i) {
        init[0][i] = (int)patterns[i].size();
    }
    if (m > 1) {
        init = init * powMod(transfer, m - 1);
    }
    LL result = INF;
    for (int i = 0; i < n; ++ i) {
        result = min(result, init[0][i]);
    }
    cout << result << endl;
    return 0;
}
