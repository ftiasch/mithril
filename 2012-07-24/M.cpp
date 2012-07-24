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

// return (10^n-1) / 9 % m
int solve(int n, int m)
{
    long long mod = m * 9LL;
    long long ret = 1 % mod, tens = 10 % mod;
    while (n) {
        if (n & 1) {
            ret = ret * tens % mod;
        }
        if (n >>= 1) {
            tens = tens * tens % mod;
        }
    }
    assert(ret % 9 == 1);
    return (ret - 1) / 9;
}

const int maxn = 9 << 20;
const int maxp = 2 << 20;

bool isPrime[maxn];
int prime[maxp], primes;

char digits[maxn];

int main()
{
    primes = 0;
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i * i < maxn; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < maxn; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 2; i < maxn; i++) {
        if (isPrime[i]) {
            prime[primes++] = i;
        }
    }
    scanf("%s", digits);
    int n = strlen(digits), sum = 0;
    for (int i = 0; i < n; i++) {
        sum += digits[i] - '0';
    }
    for (int i = 0; i < primes; i++) {
        int p = prime[i];
        if (sum % p == 0 || solve(n, p) == 0) {
            cout << p << endl;
            return 0;
        }
    }
    assert(false);
}
