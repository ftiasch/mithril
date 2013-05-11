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

const int MAXN = 5010;
const int MOD = 1000000000 + 7;

int n, t;
int whichN, whichT;

int a[MAXN];
int fact[MAXN];

int inv(int v)
{
    return v <= 1 ? v : (long long)(MOD - MOD / v) * inv(MOD % v) % MOD;
}

int binom(int n, int m)
{
    return n >= 0 && 0 <= m && m <= n ? (long long)fact[n] * inv((long long)fact[m] * fact[n - m] % MOD) % MOD : 0;
}

int main()
{
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (long long)fact[i - 1] * i % MOD;
    }
    scanf("%d%d", &n, &t);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    scanf("%d%d", &whichN, &whichT);
    whichN --, whichT --;
    int smaller = 0, equals = 0, larger = 0;
    for (int i = 0; i < n; i++) {
        if (i == whichN) {
            continue;
        } else if (a[i] == a[whichN]) {
            equals ++;
        } else if (a[i] < a[whichN]) {
            smaller ++;
        } else {
            larger ++;
        }
    }
    int leftHand = whichT, rightHand = t - 1 - whichT;
    int ret = 0;
    for (int i = 0; i <= smaller && i <= leftHand; i++) {
        for (int j = 0; j <= larger && j <= rightHand; j++) {
            int k = leftHand + rightHand - i - j;
            if (k <= equals) {
                ret += (long long)binom(smaller, i) * binom(larger, j) % MOD * binom(equals, k) % MOD;
                if (ret >= MOD) {
                    ret -= MOD;
                }
            }
        }
    }
    printf("%d\n", ret);
}
