#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

typedef long long LL;

const int N = 1000;

LL n, m, d, config[N];

int main() {
    std::cin >> n >> m >> d;
    
    // init
    LL round = (m - n) / d;
    LL left = m - round * d;
    int pos = round % n;
    std::fill(config, config + n, 1);
    config[pos] += left - n;

    
    LL need = (n + d - 1) / d;
    round /= need;
    for (int i = 0; i < n; ++ i) {
        config[i] += round;
    }
    LL extra = need * d - n;

    LL shift = (n - need) % n;
    LL cycle = n / std::__gcd(shift, n);
    std::vector <int> indices;
    LL times = round / cycle;
    for (int i = 0; i < cycle; ++ i) {
        (pos += shift) %= n;
        indices.push_back(pos);
        config[pos] += times * extra;
    }
    for (int i = 0; i < round % cycle; ++ i) {
        config[indices[i]] += extra;
    }
    for (int i = 0; i < n; ++ i) {
        std::cout << config[i] << (i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
