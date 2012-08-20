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

const int maxn = 1 << 18;

typedef long long LL;

LL n;

vector<LL> factors, divisors;

vector<int> prev[maxn];

LL wys[maxn];
LL nwys[maxn];

void findFactors(LL n)
{
    factors.clear();
    for (LL i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
}

void findDivisors(LL n)
{
    divisors.clear();
    for (LL i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i * i != n) {
                divisors.push_back(n / i);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
}

int main()
{
    int tests;
    cin >> tests;
    while (tests --) {
        cin >> n;
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        findFactors(n);
        findDivisors(n);
        for (int i = 0; i < divisors.size(); i++) {
            prev[i].assign(factors.size(), -1);
            for (int j = 0; j < factors.size(); j++) {
                if (divisors[i] % factors[j] == 0) {
                    prev[i][j] = lower_bound(divisors.begin(), divisors.end(), divisors[i] / factors[j]) - divisors.begin();
                }
            }
        }
        LL ans = 0, last = 0;
        memset(wys, 0, sizeof(*wys) * divisors.size());
        wys[0] = 1;
        while (true) {
            bool found = false;
            for (int i = 0; i < divisors.size(); i++) {
                if (wys[i] != 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                break;
            }
            memcpy(nwys, wys, sizeof(*wys) * divisors.size());
            for (int i = 0; i < factors.size(); i++) {
                for (int j = 0; j < divisors.size(); j++) {
                    if (prev[j][i] >= 0) {
                        wys[j] += wys[prev[j][i]];
                    }
                }
            }
            for (int i = 0; i < divisors.size(); i++) {
                wys[i] -= nwys[i];
            }
            ans += (last + wys[divisors.size() - 1]) * wys[divisors.size() - 1];
            last = wys[divisors.size() - 1];
        }
        cout << ans * 2 << endl;
    }
}
