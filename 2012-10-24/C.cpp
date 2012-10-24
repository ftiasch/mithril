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

const int MOD = 1000000009;
const int MAXN = 512;

int choose[MAXN][MAXN];

inline int addmod(int a, int b)
{
    if (a + b >= MOD) {
        return a + b - MOD;
    }
    return a + b;
}

inline int submod(int a, int b)
{
    if (a < b) {
        return a + MOD - b;
    }
    return a - b;
}

inline int mulmod(int a, int b)
{
    return (long long)a * b % MOD;
}

int n, k;
int A[MAXN], B[MAXN], C[MAXN];

int wys[MAXN][MAXN];
int tuples[MAXN];

int main()
{
    for (int i = 0; i < MAXN; i++) {
        choose[i][i] = choose[i][0] = 1;
        for (int j = 1; j < i; j++) {
            choose[i][j] = addmod(choose[i-1][j-1], choose[i-1][j]);
        }
    }
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", A + i);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", B + i);
    }
    sort(B, B + n);
    reverse(B, B + n);
    for (int i = 0; i < n; i++) {
        C[i] = 0;
        for (int j = 0; j < n; j++) {
            if (A[j] > B[i]) {
                C[i] ++;
            }
        }
    }
    memset(wys, 0, sizeof(wys));
    wys[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            wys[i + 1][j] = addmod(wys[i + 1][j], wys[i][j]);
            if (C[i] > j) {
                wys[i + 1][j + 1] = addmod(wys[i + 1][j + 1], mulmod(C[i] - j, wys[i][j]));
            }
        }
    }
    for (int i = n; i >= 0; i--) {
        int num = wys[n][i];
        for (int j = i + 1; j <= n; j++) {
            num = mulmod(num, n - j + 1);
        }
        tuples[i] = num;
        for (int j = i + 1; j <= n; j++) {
            tuples[i] = submod(tuples[i], mulmod(tuples[j], choose[j][i]));
        }
    }
    if ((n + k) % 2 == 1) {
        printf("%d\n", 0);
        return 0;
    }
    int wins = (n + k) / 2;
    printf("%d\n", tuples[wins]);
}
