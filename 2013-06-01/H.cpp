#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

const int maxn = 30;
const int MOD = 239;

typedef int matrix[maxn][maxn];

matrix ma[MOD];

void mul(matrix a, matrix b)
{
    static matrix c;
    memset(c, 0, sizeof(matrix));
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            for (int k = 0; k < maxn; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    memcpy(a, c, sizeof(matrix));
}

void pow(matrix a, matrix r, long long p)
{
    if (p == 0) {
        memset(r, 0, sizeof(matrix));
        for (int i = 0; i < maxn; i++) {
            r[i][i] = 1;
        }
    } else {
        pow(a, r, p >> 1);
        mul(r, r);
        if (p & 1) {
            mul(r, a);
        }
    }
}

matrix row, unit, powered;

int main()
{
    memset(ma, 0, sizeof(ma));
    for (int n = 0; n < MOD; n++) {
        for (int k = 0; k < maxn; k++) {
            ma[n][k][k] = (k + 1) * 2 % MOD;
            if (k + 1 < maxn) {
                ma[n][k][k + 1] = ((n + 1 - (k + 1) * 2) % MOD + MOD) % MOD;
            }
        }
    }
    long long n;
    int k;
    cin >> n >> k;
    memset(row, 0, sizeof(matrix));
    row[0][0] = 1;
    long long ptr = 1;
    while (ptr <= n) {
        if ((n - ptr) % MOD == 0) {
            memset(unit, 0, sizeof(matrix));
            for (int i = 0; i < maxn; i++) {
                unit[i][i] = 1;
            }
            for (int i = 0; i < MOD; i++) {
                mul(unit, ma[(ptr + i) % MOD]);
            }
            pow(unit, powered, (n - ptr) / MOD);
            mul(row, powered);
            break;
        } else {
            mul(row, ma[ptr % MOD]);
            ptr ++;
        }
    }
    cout << row[0][k - 1] << endl;
}
