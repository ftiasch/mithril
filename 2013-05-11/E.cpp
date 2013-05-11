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

int modInverse(int a, int mod)
{
    return a <= 1 ? a : (long long)(mod - mod / a) * modInverse(mod % a, mod) % mod;
}

long long mulmod(long long a, long long b, long long mod)
{
    a %= mod;
    b %= mod;
    if (mod >> 30) {
        long long t = (long double)a * b / mod + 0.5;
        long long res = a * b - mod * t;
        if (res < 0) {
            res += mod;
        }
        return res;
    } else {
        return a * b % mod;
    }
}

pair<int,long long> gcd(pair<int,long long> a, pair<int,long long> b, long long g)
{
    while (b.first != 0) {
        int times = a.first / b.first;
        a.first -= b.first * times;
        a.second = (a.second % g - mulmod(b.second, times, g) + g) % g;
        swap(a, b);
    }
    a.second %= g;
    return a;
}

long long extgcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        long long g = extgcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}

bool solve(int n, int *a, long long &mod, long long &mul)
{
    if (n == 1) {
        mod = a[0] + 1;
        mul = 1;
        return true;
    }
    for (int i = 1; i < n; i++) {
        if (a[i - 1] == 0 && a[i] != 0) {
            return false;
        }
    }
    int maxv = *max_element(a, a + n);
    long long g = 0;
    int gl = 0;
    for (int i = 1; i < n; i++) {
        gl = __gcd(gl, a[i - 1]);
    }
    for (int i = 2; i < n; i++) {
        long long diff = (long long)a[i - 1] * a[i - 1] - (long long)a[i - 2] * a[i];
        g = __gcd(g, abs(diff));
    }
    if (g == 0) {
        mod = 1000000000 + 7;
        mul = a[0] == 0 ? 1 : ((long long)a[1] * modInverse(a[0], mod) % mod);
        return true;
    }
    pair<int,long long> gpair(0, 0LL);
    for (int i = 1; i < n; i++) {
        gpair = gcd(gpair, make_pair(a[i - 1] / gl, (long long)a[i]), g);
    }
    assert(gpair.first == 1);
    for (int i = 1; i < n; i++) {
        long long v = mulmod(a[i - 1] / gl, gpair.second, g) - a[i];
        g = __gcd(g, abs(v));
    }
    if (g <= maxv) {
        return false;
    }
    mod = g;
    // gl * mul % mod = gpair.second % mod
    // gl * X + mod * Y = gpair.second
    long long X, Y;
    g = extgcd(gl, mod, X, Y);
    if (gpair.second % g != 0) {
        return false;
    }
    mul = mulmod(X, gpair.second / g, mod);
    if (mul < 0) {
        mul += mod;
    }
    return true;
}

const int maxn = 111111;

int n;
int a[maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    int lo = 1, hi = n;
    long long mod, mul;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (solve(mid + 1, a, mod, mul)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    solve(lo, a, mod, mul);
    cout << lo << " " << mod << " " << mul << endl;
    for (int i = 1; i < lo; i++) {
        assert(mulmod(a[i - 1], mul, mod) == a[i]);
    }
}
