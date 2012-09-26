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

const int MOD = 1000 * 1000 * 1000 + 7;
const int MAXN = 1024;

int choose[MAXN][MAXN];
int factorial[MAXN];
int wys[MAXN][MAXN];

int inverse(int a)
{
    return a <= 1 ? a : (MOD - MOD / a) * 1LL * inverse(MOD % a) % MOD;
}

inline void add(int &a, int v)
{
    if ((a += v) >= MOD) {
        a -= MOD;
    }
}

inline void subtract(int &a, int v)
{
    if ((a -= v) < 0) {
        a += MOD;
    }
}

int tmp[MAXN];

int solve(int n, int k)
{
    k = n - k;
    for (int i = k; i <= n; i++) {
        tmp[i] = wys[n][i] * 1LL * factorial[n - i] % MOD;
    }
    for (int i = n - 1; i >= k; i--) {
        for (int j = i + 1; j <= n; j++) {
            subtract(tmp[i], tmp[j] * 1LL * choose[j][i] % MOD);
        }
    }
    return tmp[k];
}

int bruteforce(int n, int k)
{
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    int ret = 0;
    do {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > i) {
                cnt ++;
            }
        }
        if (cnt == k) {
            ret ++;
        }
    } while (next_permutation(a.begin(), a.end()));
    return ret;
}

int main()
{
    for (int i = 0; i < MAXN; i++) {
        choose[i][0] = choose[i][i] = 1;
        for (int j = 1; j < i; j++) {
            choose[i][j] = (choose[i-1][j-1] + choose[i-1][j]) % MOD;
        }
    }
    factorial[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        factorial[i] = factorial[i - 1] * 1LL * i % MOD;
    }
    wys[0][0] = 1;
    for (int i = 0; i + 1 < MAXN; i++) {
        for (int j = 0; j <= i; j++) {
            add(wys[i + 1][j], wys[i][j]);
            add(wys[i + 1][j + 1], wys[i][j] * 1LL * (i + 1 - j) % MOD);
        }
    }
    int n, k;
    while (scanf("%d%d", &n, &k) == 2) {
        printf("%d\n", solve(n, k));
        //printf("%d\n", bruteforce(n, k));
    }
}
