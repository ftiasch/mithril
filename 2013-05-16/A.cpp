#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

std::vector <LL> primes, power, answer;
int f[1000];

inline void dfs(int i, int remain, LL now)
{
    if (!remain) {
        answer.push_back(now);
        return;
    }
    int sum = 0;
    for (int j = i; j < power.size(); ++ j) {
        sum += power[j];
    }
    if (sum < remain) {
        return;
    }
    
    for (int j = 0; j <= power[i] && j <= remain; ++ j) {
        dfs(i + 1, remain - j, now);
        now *= primes[i];
    }
}

int main() {
    LL n;
    std::cin >> n;
    for (LL now = n, p = 2; p <= 100; ++ p) {
        if (now % p == 0) {
            primes.push_back(p);
            power.push_back(0);
            while (now % p == 0) {
                now /= p;
                ++ power.back();
            }
        }
    }
    
    f[0] = 1;
    int s = 0;
    for (int i = 0; i < primes.size(); ++ i) {
        for (int j = s; j >= 0; -- j) {
            for (int k = 1; k <= power[i]; ++ k) {
                f[j + k] += f[j];
            }
        }
        s += power[i];
    }
    
    int best = 0;
    for (int i = 0; i <= s; ++ i) {
        if (f[i] > f[best]) {
            best = i;
        }
    }
    
    dfs(0, best, 1LL);
    
    sort(answer.begin(), answer.end());
    printf("%d\n", (int)answer.size());
    for (int i = 0; i < answer.size(); ++ i) {
        if (i) {
            printf(" ");
        }
        printf("%lld", answer[i]);
    }
    printf("\n");
    
    return 0;
}

