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

const int maxn = 5000;
const int MOD = 1000000007;

int ways[maxn + 1][maxn + 1];

int invMod(int a)
{
    return a <= 1 ? a : (long long)(MOD - MOD / a) * invMod(MOD % a) % MOD;
}

int fact[maxn + 1];
int power2[maxn + 1];

int choose(int n, int m)
{
    if (m < 0 || m > n) {
        return 0;
    }
    return (long long)fact[n] * invMod((long long)fact[m] * fact[n - m] % MOD) % MOD;
}

int main()
{
    fact[0] = power2[0] = 1;
    for (int i = 1; i <= maxn; i++) {
        fact[i] = (long long)fact[i - 1] * i % MOD;
        power2[i] = (long long)power2[i - 1] * 2 % MOD;
    }
    int n, d;
    scanf("%d%d", &n, &d);
    ways[1][1] = 1;
    for (int sz = 1; sz < n; sz++) {
        for (int n0 = 0; n0 <= sz; n0++) {
            if (ways[sz][n0] == 0) {
                continue;
            }
            // n2 + n1 + n0 = sz
            // n2 * 2 + n1 = sz - 1
            // n2 = n0 - 1
            // n1 = sz - n0 - n2
            int n1 = sz - n0 * 2 + 1;
            (ways[sz + 1][n0 + 1] += (long long)ways[sz][n0] * n1 % MOD) %= MOD;
            (ways[sz + 1][n0] += (long long)ways[sz][n0] * n0 % MOD) %= MOD;
        }
    }
    int ans = 0;
    for (int n0 = 0; n0 <= n; n0++) {
        if (ways[n][n0] == 0) {
            continue;
        }
        int n2 = n0 - 1;
        int n1 = n - n0 - n2;
        int n1L = d - n2;
        if (n1L < 0 || n1L > n1) {
            continue;
        }
        (ans += (long long)power2[n2] * choose(n1, n1L) % MOD * ways[n][n0] % MOD) %= MOD;
    }
    printf("%d\n", ans);
}
