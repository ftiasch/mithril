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

const int MOD = 1000000007;

typedef int matrix[32][32];

int n, m, r, sz;

int modinverse(int a)
{
    return a > 1 ? (long long)(MOD - MOD / a) * modinverse(MOD % a) % MOD : a;
}

void mul(matrix a, matrix b)
{
    static matrix tmp;
    memset(tmp, 0, sizeof(matrix));
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            for (int k = 0; k < sz; k++) {
                tmp[i][j] += (long long)a[i][k] * b[k][j] % MOD;
                if (tmp[i][j] >= MOD) {
                    tmp[i][j] -= MOD;
                }
            }
        }
    }
    memcpy(a, tmp, sizeof(matrix));
}

matrix ma[32];
matrix now;

int solve(int n)
{
    if (n <= m) {
        if (::n < m) {
            return 1 << n;
        }
        int ret = 0;
        for (int bits = 0; bits < (1 << n); bits++) {
            bool valid = true;
            for (int offset = 0; offset < n; offset++) {
                int longbitsCntbit = 0;
                for (int i = 0; i < m; i++) {
                    if (bits >> ((offset + i) % n) & 1) {
                        longbitsCntbit ++;
                    }
                }
                if (longbitsCntbit > r) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                ret ++;
            }
        }
        return ret;
    }
    memset(now, 0, sizeof(matrix));
    for (int i = 0; i < sz; i++) {
        now[i][i] = 1;
    }
    for (int i = 0; i < 32; i++) {
        if (n >> i & 1) {
            mul(now, ma[i]);
        }
    }
    int ret = 0;
    for (int i = 0; i < sz; i++) {
        ret += now[i][i];
        if (ret >= MOD) {
            ret -= MOD;
        }
    }
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &r);
    sz = 1 << (m - 1);
    memset(ma, 0, sizeof(ma));
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < 2; j++) {
            int ni = i * 2 + j;
            if (__builtin_popcount(ni) <= r) {
                ni &= sz - 1;
                ma[0][ni][i] ++;
            }
        }
    }
    for (int i = 1; i < 32; i++) {
        memcpy(ma[i], ma[i - 1], sizeof(matrix));
        mul(ma[i], ma[i]);
    }
    vector<int> factors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            if (i * i < n) {
                factors.push_back(n / i);
            }
        }
    }
    sort(factors.begin(), factors.end());
    vector<int> cnt(factors.size());
    int sum = 0;
    for (int i = factors.size() - 1; i >= 0; i--) {
        cnt[i] = n / factors[i];
        for (int j = i + 1; j < factors.size(); j++) {
            if (factors[j] % factors[i] == 0) {
                cnt[i] -= cnt[j];
            }
        }
    }
    for (int i = 0; i < factors.size(); i++) {
        if (factors[i] % 2 == 0) {
            continue;
        }
        int fi = factors[i];
        while (fi <= m && n % fi == 0) {
            int idx = lower_bound(factors.begin(), factors.end(), fi) - factors.begin();
            sum += (long long)solve(fi) * cnt[idx] % MOD;
            if (sum >= MOD) {
                sum -= MOD;
            }
            fi *= 2;
        }
        if (n % fi != 0) {
            continue;
        }
        solve(fi);
        while (n % fi == 0) {
            int idx = lower_bound(factors.begin(), factors.end(), fi) - factors.begin();
            for (int j = 0; j < sz; j++) {
                sum += (long long)now[j][j] * cnt[idx] % MOD;
                if (sum >= MOD) {
                    sum -= MOD;
                }
            }
            mul(now, now);
            fi *= 2;
        }
    }
    sum = (long long)sum * modinverse(n) % MOD;
    printf("%d\n", sum);
}
