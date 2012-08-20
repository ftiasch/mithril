#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1000;
const int MOD =  100000007;

int ways[N + 1][2 * N + 1][2], result[N + 1][2 * N + 1];

void add(int a, int &x) {
    x += a;
    x %= MOD;
}

int main() {
    memset(ways, 0, sizeof(ways));
    ways[1][0][0] = ways[1][0][1] = 1;
    for (int i = 1; i + 1 <= N; ++ i) {
        for (int j = 0; j <= 2 * (i - 1); ++ j) {
            add(ways[i][j][0], ways[i + 1][j][0]);
            add(ways[i][j][0], ways[i + 1][j + 1][0]);
            add(ways[i][j][0], ways[i + 1][j + 1][1]);
            add(ways[i][j][0] * 2, ways[i + 1][j][1]);

            //add(ways[i][j][1], ways[i + 1][j][0]);
            add(ways[i][j][1] * 2, ways[i + 1][j + 1][0]);
            add(ways[i][j][1], ways[i + 1][j + 2][0]);

            add(ways[i][j][1], ways[i + 1][j][1]);
            add(ways[i][j][1], ways[i + 1][j + 2][1]);
            add(ways[i][j][1] * 2, ways[i + 1][j + 1][1]);
        }
    }
    memset(result, 0, sizeof(result));
    for (int i = 1; i <= N; ++ i) {
        for (int j = 0; j <= 2 * (i - 1); ++ j) {
            for (int k = 0; k < 2; ++ k) {
                add(ways[i][j][k], result[i][j + k + 1]);
            }
        }
    }
    int testCount;
    scanf("%d", &testCount);
    while (testCount --) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("%d\n", result[n][k]);
    }
    return 0;
}
