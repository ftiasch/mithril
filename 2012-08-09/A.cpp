#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1000001;

int n, mod, power[N], f[N], g[N];

int main() {
    scanf("%d%d", &n, &mod);
    power[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        power[i] = power[i - 1] * 2 % mod;
    }
    f[1] = 2 % mod;
    g[1] = 0;
    for (int i = 2; i <= n; ++ i) {
        g[i] = g[i - 1] * 2 % mod;
        if (i % 2 == 0) {
            g[i] += f[i / 2];
            g[i] %= mod;
        }
        f[i] = (power[i] - g[i] + mod) % mod;
    }
    printf("%d\n", f[n]);
    return 0;
}
