#include <cstdio>
#include <cstring>
#include <cassert>

typedef long long LL;

LL multiply(LL a, LL b, LL m) {
    assert(a >= 0 && b >= 0);
    LL ret = 0;
    while (b) {
        if (b & 1) {
            (ret += a) %= m;
        }
        (a += a) %= m;
        b >>= 1;
    }
    return ret;
}

LL pow(LL a, LL n, LL m) {
    assert(n >= 0);
    LL ret = 1 % m;
    while (n) {
        if (n & 1) {
            ret = multiply(ret, a, m);
        }
        a = multiply(a, a, m);
        n >>= 1;
    }
    return ret;
}

LL factorial(int n) {
    LL ret = 1;
    for (int i = 1; i <= n; ++ i) {
        ret *= i;
    }
    return ret;
}

const int K = 10;

LL binom[K + 1][K + 1];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    if (k > n) {
        puts("0");
    } else {
        LL mod = factorial(k) * 2007;
        memset(binom, 0, sizeof(binom));
        for (int i = 0; i <= k; ++ i) {
            binom[i][0] = 1;
            for (int j = 1; j <= i; ++ j) {
                binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
            }
        }
        LL answer = 0;
        for (int i = 0; i <= k; ++ i) {
            LL t = multiply(pow(k - i, n, mod), binom[k][i], mod);
            if (i & 1) {
                (answer -= t) %= mod;
            } else {
                (answer += t) %= mod;
            }
        }
        assert(answer % factorial(k) == 0);
        printf("%d\n", ((answer / factorial(k)) % 2007 + 2007) % 2007);
    }
    return 0;
}
