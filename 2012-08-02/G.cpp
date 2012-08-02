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

int powmod(int a, long long b, int mod)
{
    int r = 1;
    while (b) {
        if (b & 1) {
            r = (long long)r * a % mod;
        }
        if (b >>= 1) {
            a = (long long)a * a % mod;
        }
    }
    return r;
}

long long n;
int k, mod;

int main()
{
    while (cin >> n >> k >> mod) {
        long long res = 0;
        if (n == 1) {
            res = k % mod;
        } else {
            res = powmod(k - 1, n, mod);
            if (n % 2 == 0) {
                res += k - 1;
            } else {
                res -= k - 1;
            }
        }
        res %= mod;
        res += mod;
        res %= mod;
        cout << res << endl;
    }
}
