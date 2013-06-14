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

const int maxn = 100011;
const int MOD = 1000000000 + 7;

int mobius[maxn];
int n, k;
long long C;
int seq[maxn], cnt[maxn];

int inverse[maxn], pow2[maxn], binomIK[maxn];

int value1[maxn], value2[maxn];

int main()
{
    inverse[1] = 1;
    for (int i = 2; i < maxn; i++) {
        inverse[i] = (long long)(MOD - MOD / i) * inverse[MOD % i] % MOD;
    }
    pow2[0] = 1;
    for (int i = 1; i < maxn; i++) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
    for (int i = 1; i < maxn; i++) {
        int delta = (i == 1 ? 1 : 0) - mobius[i];
        for (int j = i; j < maxn; j += i) {
            mobius[j] += delta;
        }
        mobius[i] = delta;
    }
    int tests;
    scanf("%d", &tests);
    for (int cas = 1; cas <= tests; ++cas) {
        scanf("%d%lld%d", &n, &C, &k);
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        seq[0] = a;
        seq[1] = b;
        for (int i = 2; i < n; i++) {
            seq[i] = 1 + ((long long)seq[i - 2] * a + (long long)seq[i - 1] * b + c) % 100000;
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            cnt[seq[i]] ++;
        }
        for (int i = 0; i < k; i++) {
            binomIK[i] = 0;
        }
        binomIK[k] = 1;
        for (int i = k + 1; i < maxn; i++) {
            binomIK[i] = (long long)binomIK[i - 1] * i % MOD * inverse[i - k] % MOD;
        }
        for (int g = maxn - 1; g >= 1; g--) {
            int sum = 0;
            for (int i = 1; g * i < maxn; i++) {
                sum += cnt[g * i];
            }
            value1[g] = pow2[sum] - 1;
            value2[g] = binomIK[sum];
        }
        int ans1 = 0, ans2 = 0;
        for (int g = 1; g < maxn; g++) {
            int sum1 = 0, sum2 = 0;
            for (int i = 1; g * i < maxn; i++) {
                (sum1 += mobius[i] * value1[i * g]) %= MOD;
                (sum2 += mobius[i] * value2[i * g]) %= MOD;
            }
            ans1 = (ans1 + (C / g) % MOD * sum1 % MOD) % MOD;
            ans2 = (ans2 + (C / g) % MOD * sum2 % MOD) % MOD;
        }
        ans1 = (ans1 + MOD) % MOD;
        ans2 = (ans2 + MOD) % MOD;
        printf("Case %d: %d %d\n", cas, ans1, ans2);
    }
}

