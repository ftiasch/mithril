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
#include <climits>
using namespace std;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const long long MOD = INT_MAX;

long long inv(long long x)
{
    return x <= 1 ? x : (MOD - MOD / x) * inv(MOD % x) % MOD;
}

const int maxn = 15;

long long ma[maxn][maxn];

long long binom[100][100];

int main()
{
    freopen("hexagon.in", "r", stdin);
    freopen("hexagon.out", "w", stdout);
    for (int i = 0; i < 100; i++) {
        binom[i][i] = binom[i][0] = 1;
        for (int j = 1; j < i; j++) {
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % MOD;
        }
    }
    int a, b, c, d, e, f;
    scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
    if (a != d || b != e || c != f) {
        puts("0");
        return 0;
    }
    int n = a;
    for (int i = 0; i < n; i++) {
        for (int j  = 0; j < n; j++) {
            int B = b + i - j;
            int C = c + j - i;
            if (B >= 0 && C >= 0) {
                ma[i][j] = binom[B + C][B];
            } else {
                ma[i][j] = 0;
            }
        }
    }
    long long ret = 1;
    for (int i = 0; i < n; i++) {
        int r = i;
        while (r < n && ma[r][i] == 0) {
            r ++;
        }
        if (r == n) {
            ret = 0;
            break;
        }
        if (r > i) {
            ret = (MOD - ret) % MOD;
            for (int j = 0; j < n; j++) {
                swap(ma[i][j], ma[r][j]);
            }
        }
        ret = ret * ma[i][i] % MOD;
        long long invii = inv(ma[i][i]);
        for (int j = 0; j < n; j++) {
            ma[i][j] = ma[i][j] * invii % MOD;
        }
        for (int j = i + 1; j < n; j++) {
            for (int k = n - 1; k >= i; k--) {
                ma[j][k] = (ma[j][k] + MOD - ma[j][i] * ma[i][k] % MOD) % MOD;
            }
        }
    }
    cout << ret << endl;
}
