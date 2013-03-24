#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 51;
const int LIMIT = 100000;

int n, primes[N], l, r;
int memory[N][LIMIT + 1];

int solve(int i, int x) {
    if (x <= LIMIT && memory[i][x] != -1) {
        return memory[i][x];
    }
    if (i == 0) {
        return x;
    }
    int ret = solve(i - 1, x) - solve(i - 1, x / primes[i]);
    if (x <= LIMIT) {
        memory[i][x] = ret;
    }
    return ret;
}

int main() {
    scanf("%d%d%d", &n, &l, &r);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", primes + i);
    }
    std::sort(primes + 1, primes + 1 + n);
    n = std::unique(primes + 1, primes + 1 + n) - (primes + 1);
    memset(memory, -1, sizeof(memory));
    for (int i = 0; i <= n; ++ i) {
        memory[i][0] = 0;
    }
    printf("%d\n", solve(n, r) - solve(n, l - 1));
    return 0;
}
