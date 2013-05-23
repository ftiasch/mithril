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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int MAXW = 75;
const int MOD = 1000000000 + 9;

typedef int matrix[MAXW][MAXW];

int w;
long long h;

void mul(matrix a, matrix b, bool rhs = false)
{
    static matrix c;
    memset(c, 0, sizeof(matrix));
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < w; k++) {
                c[i][j] += (long long)a[i][k] * b[k][j] % MOD;
                if (c[i][j] >= MOD) {
                    c[i][j] -= MOD;
                }
            }
        }
    }
    if (rhs) {
        memcpy(b, c, sizeof(matrix));
    } else {
        memcpy(a, c, sizeof(matrix));
    }
}

void pow(matrix a, matrix r, long long p)
{
    if (p == 0) {
        memset(r, 0, sizeof(matrix));
        for (int i = 0; i < w; i++) {
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

matrix trans, powered, col;

int main()
{
    int n, cas = 0;
    while (cin >> w >> h >> n && w) {
        map<long long,vector<int> > M;
        M[h - 1].clear();
        for (int i = 0; i < n; i++) {
            int xi;
            long long yi;
            cin >> xi >> yi;
            xi --, yi --;
            if (yi != 0) {
                M[yi].push_back(xi);
            }
        }
        M.erase(0LL);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < w; j++) {
                trans[j][i] = abs(i - j) <= 1 ? 1 : 0;
            }
        }
        memset(col, 0, sizeof(matrix));
        col[0][0] = 1;
        long long lastH = 0;
        FOR (it, M) {
            pow(trans, powered, it->first - lastH);
            mul(powered, col, true);
            FOR (jt, it->second) {
                col[*jt][0] = 0;
            }
            lastH = it->first;
        }
        printf("Case %d: %d\n", ++cas, col[w - 1][0]);
    }
}
