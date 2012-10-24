#include <cstdio>
#include <cstring>
#include <climits>
#include <deque>
using namespace std;

const int N = 200;

int n, a, b, minimum[N + 1][N + 1][N + 1], predecessor[N + 1][N + 1][N + 1];
char text[N + 1];

int main() {
    scanf("%d%d%d%s", &n, &a, &b, text);
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; i + j <= n; ++ j) {
            for (int k = 0; i + j + k <= n; ++ k) {
                minimum[i][j][k] = INT_MAX;
            }
        }
    }
    minimum[0][0][0] = 0;
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; i + j <= n; ++ j) {
            for (int k = 0; i + j + k <= n; ++ k) {
                if (minimum[i][j][k] == INT_MAX) {
                    continue;
                }
                int id = i + j + k;
                if (id == n) {
                    continue;
                }
                int token = text[id] - '0';
                if (minimum[i][j][k] + (token != 0) < minimum[i + 1][j][k]) {
                    minimum[i + 1][j][k ] = minimum[i][j][k] + (token != 0);
                    predecessor[i + 1][j][k] = 0;
                }
                if (minimum[i][j][k] + (token != 1) < minimum[i][j + 1][k]) {
                    minimum[i][j + 1][k] = minimum[i][j][k] + (token != 1);
                    predecessor[i][j + 1][k] = 1;
                }
                if (minimum[i][j][k] + (token != 2) < minimum[i][j][k + 1]) {
                    minimum[i][j][k + 1] = minimum[i][j][k] + (token != 2);
                    predecessor[i][j][k + 1] = 2;
                }
            }
        }
    }
    if (a + b > n || minimum[a][b][n - a - b] == INT_MAX) {
        puts("-1");
    } else {
        printf("%d\n", minimum[a][b][n - a - b]);
        deque <int> result;
        for (int i = a, j = b, k = n - a - b; i || j || k; ) {
            result.push_front(predecessor[i][j][k]);
            if (predecessor[i][j][k] == 0) {
                i --;
            } else if (predecessor[i][j][k] == 1) {
                j --;
            } else {
                k --;
            }
        }
        for (int i = 0; i < (int)result.size(); ++ i) {
            printf("%d", result[i]);
        }
        puts("");
    }
    return 0;
}
