#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <cctype>
#include <sstream>

using namespace std;

#define FOR(it, a) for (__typeof((a).begin()) it=(a).begin(); it != (a).end(); ++it)

const int maxn = 3001;

int prime[55], primes;

bool isPrime(int a)
{
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return a >= 2;
}

int cnt[1 << 16];
int wys[1 << 16];

vector<int> cntP[maxn];

int n, mod;

void update(int &a, int v)
{
    if ((a += v) >= mod) {
        a -= mod;
    }
}

int main()
{
    scanf("%d%d", &n, &mod);
    primes = 0;
    for (int i = 2; i * i <= n; i++) {
        if (isPrime(i)) {
            prime[primes++] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        int mask = 0;
        int t = i;
        for (int j = 0; j < primes; j++) {
            while (t % prime[j] == 0) {
                mask |= 1 << j;
                t /= prime[j];
            }
        }
        if (t == 1) {
            cnt[mask] ++;
        } else {
            cntP[t].push_back(mask);
        }
    }
    int ans = 0;
    wys[0] = 1 % mod;
    for (int i = 1; i < 1 << primes; i++) {
        int mask = i;
        int lowbit = mask & -mask;
        for (int j = mask; j > 0; j = j - 1 & mask) {
            if (j & lowbit) {
                update(wys[i], (long long)wys[i ^ j] * cnt[j] % mod);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cntP[i].size() == 0) {
            continue;
        }
        for (int j = (1 << primes) - 1; j >= 0; j --) {
            update(wys[j], wys[j]);
            FOR (it, cntP[i]) {
                if (*it && (j & *it) == *it) {
                    update(wys[j], wys[j ^ *it]);
                }
            }
        }
    }
    for (int i = 0; i < 1 << primes; i++) {
        update(ans, wys[i]);
    }
    for (int i = 0; i < cnt[0]; i++) {
        ans = ans * 2 % mod;
    }
    printf("%d\n", ans);
}
