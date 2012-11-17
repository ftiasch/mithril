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

const int MOD = 1000 * 1000 * 1000 + 7;

long long invMod(long long a)
{
    return a <= 1 ? a : (MOD - MOD / a) * invMod(MOD % a) % MOD;
}

long long powMod(long long a, long long p)
{
    a %= MOD;
    long long r = 1;
    while (p) {
        if (p & 1) {
            r = r * a % MOD;
        }
        if (p >>= 1) {
            a = a * a % MOD;
        }
    }
    return r;
}

// sigma_l x^l
long long solveA(long long n, long long x)
{
    if (x <= 1) {
        return x * n;
    }
    return (powMod(x, n + 1) - 1 + MOD) % MOD * invMod(x - 1) % MOD;
}

// sigma_l n^l * ((n + 1)^l - 1^l)
long long solve1(long long n)
{
    long long x = n * (n + 1) % MOD;
    return (solveA(n, x) - solveA(n, n) + MOD)% MOD;
}

// sigma_l \binom{n}{l}x^l
long long solveB(long long n, long long x)
{
    return powMod(1 + x, n);
}

// sigma_l \binom{n}{l} ((n + 1) ^ l - 1 ^ l)
long long solve2(long long n)
{
    return (solveB(n, n + 1) - solveB (n, 1) + MOD) % MOD;
}

long long solve(long long n)
{
    if (n == 1) {
        return 0;
    }
    long long ans = solve1(n) - 2 * solve2(n);
    ans %= MOD;
    ans = ans * (n + 1) % MOD * invMod(2 * n % MOD) % MOD;
    ans = (ans + n * (n + 1) / 2 % MOD) % MOD;
    ans += MOD;
    ans %= MOD;
    return ans;
}

int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    int n;
    while (cin >> n) {
        cout << solve(n) << endl;
    }
}
