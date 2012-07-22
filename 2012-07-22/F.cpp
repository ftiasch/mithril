#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 63;

unsigned long long ways[N + 1][N + 1][N + 1][2];

int main() {
    memset(ways, 0, sizeof(ways));
    ways[0][0][0][0] = 1;
    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j) {
            for (int k = 0; k < N; ++ k) {
                for (int x = 0; x < 2; ++ x) {
                    for (int y = 0; y < 2; ++ y) {
                        ways[i + 1][j + y][k + (x ^ y)][y] += ways[i][j][k][x];
                    }
                }
            }
        }
    }
    int testCount = 0;
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n > 0) {
        printf("Case %d: ", ++ testCount);
        unsigned long long result[2];
        memset(result, 0, sizeof(result));
        for (int j = m; j <= N; ++ j) {
            for (int k = 0; k <= N; ++ k) {
                for (int x = 0; x < 2; ++ x) {
                    if (k < j) {
                        result[0] += ways[n][j][k][x];
                    } else if (k > j) {
                        result[1] += ways[n][j][k][x];
                    }
                }
            } 
        }
        cout << result[0] << " " << result[1] << endl;
    }
    return 0;
}
