#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxP = 1000000;

bool isPrime[maxP];
vector <int> primes, factors;
vector <pair <int, int> > primeFactors;

void factorize(int n) {
    primeFactors.clear();
    for (int i = 0; i < (int)primes.size() && (long long)primes[i] * primes[i] <= n; ++ i) {
        if (n % primes[i] == 0) {
            primeFactors.push_back(make_pair(primes[i], 0));
            while (n % primes[i] == 0) {
                primeFactors.back().second ++;
                n /= primes[i];
            }
        }
    }
    if (n > 1) {
        primeFactors.push_back(make_pair(n, 1));
    }
}

void dfs(int i, int d) {
    if (i < (int)primeFactors.size()) {
        for (int k = 0; k <= (int)primeFactors[i].second; ++ k) {
            dfs(i + 1, d);
            d *= primeFactors[i].first;
        }
    } else {
        factors.push_back(d);
    }
}

int main() {
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i < maxP; ++ i) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i + i; j < maxP; j += i) {
                isPrime[j] = false;
            }
        }
    }
    int testCount;
    scanf("%d", &testCount);
    while (testCount > 0) {
        testCount --;
        int n, k;
        scanf("%d%d", &n, &k);
        factorize(n);
        factors.clear();
        dfs(0, 1);
        nth_element(factors.begin(), factors.begin() + k - 1, factors.end());
        printf("%d\n", factors[k - 1]);
    }
    return 0;
}
