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
 
const int MOD = 1000000000 - 401;
const int PRIMES[4] = {2, 13, 5281, 7283};
 
int mod_inv(int a, int p)
{
    return a > 1 ? (long long)(p - p / a) * mod_inv(p % a, p) % p : a;
}
 
vector<int> fact[10000];
 
int pow_mod(int a, int b, int p)
{
    a %= p;
    int ret = 1;
    while (b) {
        if (b & 1) {
            ret = (long long)ret * a % p;
        }
        if (b >>= 1) {
            a = (long long)a * a % p;
        }
    }
    return ret;
}
 
// number of primes p in n!
long long calcTimes(int n, int p)
{
    long long ret = 0;
    while (n /= p) {
        ret += n;
    }
    return ret;
}
 
// n! / p^calcTimes(n, p) % p
int calcMod(int n, int p)
{
    if (fact[p].empty()) {
        fact[p].resize(p);
        fact[p][0] = 1;
        for (int i = 1; i < p; i++) {
            fact[p][i] = (long long)fact[p][i - 1] * i % p;
        }
    }
    if (n < p) {
        return fact[p][n];
    }
    int ret = pow_mod(fact[p][p - 1], n / p, p);
    ret = (long long)ret * fact[p][n % p] % p;
    ret = (long long)ret * calcMod(n / p, p) % p;
    return ret;
}
 
int solve(int n, const vector<int> &fs, int p)
{
    int ret = 0;
    FOR (it, fs) {
        int d = *it;
        long long times = 0, mod = 1;
        times += calcTimes(n, p);
        mod = mod * calcMod(n, p) % p;
        times -= calcTimes(d, p) * (n / d);
        mod = mod * pow_mod(mod_inv(calcMod(d, p), p), n / d, p) % p;
        times -= calcTimes(n / d, p);
        mod = mod * mod_inv(calcMod(n / d, p), p);
        if (times == 0) {
            ret = (ret + mod) % p;
        }
    }
    return ret;
}
 
int solve(int n)
{
    vector<int> fs;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            fs.push_back(i);
            if (i * i < n) {
                fs.push_back(n / i);
            }
        }
    }
    int ans[4];
    int M = 1;
    for (int i = 0; i < 4; i ++) {
        ans[i] = solve(n, fs, PRIMES[i]);
        M *= PRIMES[i];
    }
    long long ret = 0;
    for (int i = 0; i < 4; i++) {
        int inv = mod_inv(M / PRIMES[i] % PRIMES[i], PRIMES[i]);
        ret = (ret + (long long)inv * ans[i] % PRIMES[i] * (M / PRIMES[i])) % M;
    }
    return ret;
}
 
int main()
{
    freopen("cliquers.in", "r", stdin);
    freopen("cliquers.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    int ans = solve(n);
    printf("%d\n", pow_mod(m, ans, MOD));
}
