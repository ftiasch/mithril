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

inline long long mul_mod(long long x, long long y, long long n)
{
    long long d = (long long)((long double)x * y / n + 0.5);
    d = x * y - n * d;
    return (d % n + n) % n;
}

long long pow_mod(long long a, long long p, long long mod)
{
    long long ret = 1;
    while (p) {
        if (p & 1) {
            ret = mul_mod(ret, a, mod);
        }
        if (p >>= 1) {
            a = mul_mod(a, a, mod);
        }
    }
    return ret;
}

bool strong_pseudo_prime_test(long long n, int base)
{
    long long n2 = n - 1, res;
    int s = 0;
    while (n2 % 2 == 0) {
        n2 >>= 1;
        s ++;
    }
    res = pow_mod(base, n2, n);
    if (res == 1 || res == n - 1) {
        return true;
    }
    while (--s >= 0) {
        res = mul_mod(res, res, n);
        if (res == n - 1) {
            return true;
        }
    }
    return false;
}

bool isPrime(long long n)
{
    if (n < 2)
        return false;
    if (n < 4)
        return true;
    if (!strong_pseudo_prime_test(n, 2))
        return false;
    if (!strong_pseudo_prime_test(n, 3))
        return false;
    if (n < 1373653LL)
        return true;
    if (!strong_pseudo_prime_test(n, 5))
        return false;
    if (n < 25326001LL)
        return true;
    if (!strong_pseudo_prime_test(n, 7))
        return false;
    if (n == 3215031751LL)
        return false;
    if (n < 25000000000LL)
        return true;
    if (!strong_pseudo_prime_test(n, 11))
        return false;
    if (!strong_pseudo_prime_test(n, 13))
        return false;
    if (!strong_pseudo_prime_test(n, 17))
        return false;
    if (!strong_pseudo_prime_test(n, 19))
        return false;
    return true;
}

long long pollard_rho(long long n, long long c)
{
    long long x, y;
    x = y = (unsigned)rand() % (n - 1) + 1;
    long long head = 1, tail = 2;
    while (true) {
        x = mul_mod(x, x, n);
        x += c;
        if (x >= n)
            x -= n;
        if (x == y)
            return n;
        long long d = __gcd(x > y ? x - y : y - x, n);
        if (d > 1 && d < n)
            return d;
        if ((++head) == tail) {
            y = x;
            tail <<= 1;
        }
    }
}

vector<long long> factors;

void factor(long long n)
{
    if (n <= 1) {
        return;
    }
    if (isPrime(n)) {
        factors.push_back(n);
        return;
    }
    long long p = n;
    while (p >= n) {
        p = pollard_rho(n, (unsigned)rand() % (n - 1) + 1);
    }
    factor(n / p);
    factor(p);
}

int main()
{
    int cas = 0;
    long long n;
    while (cin >> n && n) {
        factors.clear();
        factor(n);
        vector<pair<long long,int> > fs;
        sort(factors.begin(), factors.end());
        for (int i = 0; i < factors.size(); ) {
            int ni = i;
            while (ni < factors.size() && factors[i] == factors[ni]) {
                ni ++;
            }
            fs.push_back(make_pair(factors[i], ni - i));
            i = ni;
        }
        long long now = 1;
        for (int i = 0; i < fs.size(); i++) {
            int times = (fs[i].second + 1) / 2;
            while (times --)
                now *= fs[i].first;
        }
        cout << "Case " << ++ cas << ": ";
        if (now == n) {
            cout << "Impossible" << endl;
        } else {
            cout << (n - 1) / now * 8 << endl;
        }
    }
}
