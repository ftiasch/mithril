#include <cstdio>
#include <cstring>
using namespace std;

const int N = 101;

int n, m, mod, ways[N][N], choose[N][N];
bool valid[N][N], highlight[N];

int main() {
    scanf("%d%d%d", &n, &m, &mod);
    int size = n / m;
    memset(choose, 0, sizeof(choose));
    for (int i = 0; i <= n; ++ i) {
        choose[i][0] = 1;
        for (int j = 1; j <= i; ++ j) {
            choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % mod;
        }
    }
    memset(highlight, 0, sizeof(highlight));
    for (int i = 0; i < m; ++ i) {
        int row;
        scanf("%d", &row);
        highlight[-- row] = true;
    }
    memset(ways, 0, sizeof(ways));
    memset(valid, 0, sizeof(valid));
    ways[n][0] = 1;
    valid[n][0] = true;
    for (int i = n - 1; i >= 0; -- i) {
        for (int j = 0; j <= n; ++ j) {
            if (highlight[i]) {
                if (j + (size - 1) <= n) {
                    ways[i][j] = ((long long)ways[i + 1][j + (size - 1)] * choose[j + (size - 1)][size - 1]) % mod;
                    valid[i][j] = valid[i + 1][j + (size - 1)];
                }
            } else if (j > 0) {
                ways[i][j] = ways[i + 1][j - 1];
                valid[i][j] = valid[i + 1][j - 1];
            }
        }
    }
    if (!valid[0][0]) {
        puts("-1");
    } else {
        printf("%d\n", ways[0][0]);
    }
    return 0;
}
