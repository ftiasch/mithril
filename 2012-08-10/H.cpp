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

const int maxb = 1 << 18;

typedef unsigned uint;
#define ulong _ulong_
typedef unsigned long long ulong;

namespace ntt
{
    const uint mod = 469762049;
    const uint modp = mod - 2;
    const uint bits = 29;
    const uint mod2 = 1U << bits;
    const uint mod2inv = 411041792;
    const uint mod2mask = mod2 - 1;
    const uint root = 3;
    const uint unit = mod2 % mod;

    inline uint transform(ulong x) {
        return (x << bits) % mod;
    }

    inline uint untransform(ulong x) {
        ulong q = ((x & mod2mask) * modp) & mod2mask;
        uint a = (x + q * mod) >> bits;
        if (a > mod) {
            a -= mod;
        }
        return a;
    }

    inline uint addmod(uint a, uint b) {
        if (a + b >= mod) {
            return a + b - mod;
        }
        return a + b;
    }

    inline uint submod(uint a, uint b) {
        if (a < b) {
            return a + mod - b;
        }
        return a - b;
    }

    inline uint mulmod(uint a, uint b) {
        return untransform((ulong)a * b);
    }

    inline uint powmod(uint a, uint b) {
        uint r = unit;
        while (b) {
            if (b & 1) {
                r = mulmod(r, a);
            }
            if (b >>= 1) {
                a = mulmod(a, a);
            }
        }
        return r;
    }

    inline uint modinv(uint a) {
        return powmod(a, mod - 2);
    }

    void ntt(uint P[], int n, int oper) {
        for (int i = 1, j = 0; i < n - 1; i++) {
            for (int s = n; j ^= s >>= 1, ~j &s; );
            if (i < j) {
                swap(P[i], P[j]);
            }
        }
        for (int d = 0; (1 << d) < n; d++) {
            int m = 1 << d, m2 = m * 2;
            uint unit_p0 = powmod(transform(root), (mod - 1) / m2);
            if (oper < 0) {
                unit_p0 = modinv(unit_p0);
            }
            for (int i = 0; i < n; i += m2) {
                uint u = unit;
                for (int j = 0; j < m; j++) {
                    uint &P1 = P[i + j + m], &P2 = P[i + j];
                    uint t = mulmod(u, P1);
                    P1 = submod(P2, t);
                    P2 = addmod(P2, t);
                    u = mulmod(u, unit_p0);
                }
            }
        }
    }
};

int n;

char SA[maxb], SB[maxb];

uint a[maxb], b[maxb], c[maxb];

int ans[maxb];

const char SIGMA[] = "ATCG";

void solve(char ch)
{
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 0; i < n; i++) {
        if (SA[i] == ch) {
            a[i] = ntt::unit;
        }
        if (SB[i] == ch) {
            b[i] = ntt::unit;
        }
    }
    ntt::ntt(a, n, 1);
    ntt::ntt(b, n, 1);
    for (int i = 0; i < n; i++) {
        c[i] = ntt::mulmod(a[i], b[i]);
    }
    ntt::ntt(c, n, -1);
    uint inv = ntt::modinv(ntt::transform(n));
    for (int i = 0; i < n; i++) {
        c[i] = ntt::mulmod(c[i], inv);
        ans[i] += ntt::untransform(c[i]);
    }
}

int main()
{
    scanf("%d%s%s", &n, SA, SB);
    memset(ans, 0, sizeof(ans));
    reverse(SB, SB + n);
    for (int i = 0; i < 4; i++) {
        solve(SIGMA[i]);
    }
    int maxp = max_element(ans, ans + n) - ans;
    printf("%d %d\n", ans[maxp], (maxp + 1) % n);
}
