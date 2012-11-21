#include <cstdio>
#include <cstring>
using namespace std;

const int N = 5000;
const int MOD = 1000000000 + 7;

int n, ways[2][N + 1];

int main() {
    scanf("%d", &n);
    memset(ways, 0, sizeof(ways));
    ways[0][1] = 1;
    for (int i = 0; i < n; ++ i) {
        int sum = 0;
        for (int j = 1; j <= n; ++ j) {
            ways[i + 1 & 1][j] = 0;
        }
        for (int j = 1; j <= n; ++ j) {
            if (i + 1 <= j) {
                ways[i + 1 & 1][j] += (long long)j * ways[i & 1][j] % MOD;
                (ways[i + 1 & 1][j] += sum) %= MOD;
                (sum += ways[i & 1][j]) %= MOD;
            }
        }
    }

    printf("%d\n", ways[n & 1][n]);
    return 0;
}
