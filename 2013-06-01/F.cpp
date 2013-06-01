#include <cstdio>
#include <cstring>

const int N = 51;

int sg[N][N];
bool mark[N * N + 1];
char board[N][N];

int main() {
    memset(sg, 0, sizeof(sg));
    for (int i = 1; i < N; ++ i) {
        for (int j = 1; j < N; ++ j) {
            memset(mark, 0, sizeof(mark));
            for (int x = 0; x < i; ++ x) {
                for (int y = 0; y < j; ++ y) {
                    int tmp = sg[x][y] ^ sg[x][j] ^ sg[i][y];
                    if (tmp <= N * N) {
                        mark[tmp] = true;
                    }
                }
            }
            sg[i][j] = 0;
            while (mark[sg[i][j]]) {
                sg[i][j] ++;
            }
        }
    }
    int n, m;
    scanf("%d%d", &n, &m);
    int game = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%s", board[i]);
        for (int j = 0; j < m; ++ j) {
            if (board[i][j] == '1') {
                game ^= sg[i + 1][j + 1];
            }
        }
    }
    if (game) {
        puts("Ann");
    for (int i = 1; i < N; ++ i) {
        for (int j = 1; j < N; ++ j) {
            if (board[i - 1][j - 1] == '1') {
                for (int x = 0; x < i; ++ x) {
                    for (int y = 0; y < j; ++ y) {
                        if ((game ^ sg[i][j] ^ sg[x][j] ^ sg[i][y] ^ sg[x][y]) == 0) {
                            printf("%d %d\n%d %d\n", i, j, x, y);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    } else {
        puts("Betty");
    }
    return 0;
}
