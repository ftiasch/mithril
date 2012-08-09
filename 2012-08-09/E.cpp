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

const int N = 16;

typedef long long matrix[N][N];

int mod;

void mul(matrix a, matrix b)
{
    static matrix tmp;
    memset(tmp, 0, sizeof(matrix));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                tmp[i][j] += a[i][k] * b[k][j] % mod;
            }
            tmp[i][j] %= mod;
        }
    }
    memcpy(a, tmp, sizeof(matrix));
}

void pow(matrix a, matrix r, long long p)
{
    if (p == 0) {
        memset(r, 0, sizeof(matrix));
        for (int i = 0; i < N; i++) {
            r[i][i] = 1 % mod;
        }
    } else {
        pow(a, r, p >> 1);
        mul(r, r);
        if (p & 1) {
            mul(r, a);
        }
    }
}

matrix a, b, c;

int k;
int f[N];
long long lo, hi;

int solve(long long x)
{
    pow(a, b, x);
    mul(b, c);
    return b[k][0];
}

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        memset(a, 0, sizeof(matrix));
        memset(c, 0, sizeof(matrix));
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            scanf("%d", f + i);
        }
        scanf("%lld%lld%d", &lo, &hi, &mod);
        for (int i = 0; i < k; i++) {
            c[i][0] = (f[i] % mod + mod) % mod;
        }
        c[k][0] = 0;
        for (int i = 1; i < k; i++) {
            a[i - 1][i] = 1 % mod;
        }
        for (int i = 0; i < k; i++) {
            a[k - 1][i] = 1 % mod;
        }
        a[k][0] = 1 % mod;
        a[k][k] = 1 % mod;
        int res = ((solve(hi + 1) - solve(lo)) % mod + mod) % mod;
        printf("%d\n", res);
    }
}
