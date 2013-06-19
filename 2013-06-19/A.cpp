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

long long mulmod(long long a, long long b, long long mod)
{
    a %= mod;
    long long ret = 0;
    while (b) {
        if (b & 1) {
            ret = (ret + a) % mod;
        }
        if (b >>= 1) {
            a = (a + a) % mod;
        }
    }
    return ret;
}

long long powmod(long long a, long long b, long long mod)
{
    a %= mod;
    long long ret = 1;
    while (b) {
        if (b & 1) {
            ret = mulmod(ret, a, mod);
        }
        if (b >>= 1) {
            a = mulmod(a, a, mod);
        }
    }
    return ret;
}

int p, n, m;
long long mod;

int main()
{
    while (cin >> p >> n >> m) {
        mod = (long long)m * n;
        int tmp = n;
        vector<int> factors;
        for (int i = 2; i * i <= tmp; i++) {
            if (tmp % i == 0) {
                factors.push_back(i);
                while (tmp % i == 0) {
                    tmp /= i;
                }
            }
        }
        if (tmp > 1) {
            factors.push_back(tmp);
        }
        long long ret = 0;
        for (int i = 0; i < (1 << factors.size()); i++) {
            int N = n;
            int mobius = 1;
            for (int j = 0; j < factors.size(); j++) {
                if (i >> j & 1) {
                    mobius = -mobius;
                    N /= factors[j];
                }
            }
            ret += mobius * powmod(p, N, mod);
            ret %= mod;
        }
        ret += mod;
        ret %= mod;
        assert(ret % n == 0);
        cout << ret / n << endl;
    }
}
