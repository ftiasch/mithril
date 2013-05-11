#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

typedef long long LL;

LL a, n, answer;
std::vector <LL> primes;

void factorize(LL n) {
    for (LL i = 2; i * i <= n; ++ i) {
        if (n % i == 0) {
            primes.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        primes.push_back(n);
    }
}

void dfs(int i, LL d, int sign) {
    if (i < (int)primes.size()) {
        dfs(i + 1, d, sign);
        dfs(i + 1, d * primes[i], -sign);
    } else if (d != 1) {
        answer += sign * ((a + n) / d - a / d);
    }
}

int main() {
    std::cin >> a >> n;
    primes.push_back(2);
    factorize(a);
    std::sort(primes.begin(), primes.end());
    primes.erase(std::unique(primes.begin(), primes.end()), primes.end());
    answer = 0;
    dfs(0, 1, -1);
    std::cout << answer << std::endl;
    return 0;
}
