#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int N = 3000 + 1;

int n, m;
char a[N], b[N];

bool has(int i, int j) {
    return a[(i - 1) % n] == b[(j - 1) % m];
}

const int DELTA[3][2] = {{0, -1}, {-1, -1}, {-1, 0}};

char from[N][N];

int solve() {
    memset(from, 0, sizeof(from));
    int ret = 0;
    for (int i = 1; i <= 2 * n; ++ i) {
        // add row
        from[i][0] = 2;
        int left = 0;
        int up = 0;
        for (int j = 1; j <= m; ++ j) {
            int upleft = up;
            if (!has(i, j)) {
                upleft = INT_MIN;
            } else {
                upleft ++;
            }
            if (from[i - 1][j]) {
                up ++;
            }
            int max = std::max(left, std::max(upleft, up));
            if (left == max) {
                from[i][j] = 0;
            } else if (upleft == max) {
                from[i][j] = 1;
            } else {
                from[i][j] = 2;
            }
            left = max;
        }
        // remove row
        if (i >= n) {
            int count = 0;
            for (int x = i, y = m; y; ) {
                int t = from[x][y];
                count += t == 1;
                x += DELTA[t][0];
                y += DELTA[t][1];
            }
            ret = std::max(ret, count);

            int x = i - n + 1;
            from[x][0] = 0;
            int y = 0;
            while (y <= m && from[x][y] == 0) {
                y ++;
            }
            for (; x <= i; ++ x) {
                from[x][y] = 0;
                if (x == i) {
                    break;
                }
                for (; y <= m; y ++) {
                    if (from[x + 1][y] == 2) {
                        break;
                    }
                    if (y + 1 <= m && from[x + 1][y + 1] == 1) {
                        y ++;
                        break;
                    }
                }
            }
        }
//for (int x = std::max(i - n, 0); x <= i; ++ x) {
//    for (int y = 0; y <= m; ++ y) {
//        if (y) {
//            putchar(from[x][y] == 1 ? '\\' : ' ');
//        }
//        putchar(from[x][y] == 2 ? '|' : ' ');
//    }
//    puts("");
//    for (int y = 0; y <= m; ++ y) {
//        if (y) {
//            putchar(from[x][y] == 0 ? '-' : ' ');
//        }
//        putchar('*');
//    }
//    puts("");
//}
//puts("===");
    }
    return ret;
}

int main() {
    scanf("%s%s", a, b);
    n = strlen(a);
    m = strlen(b);
    int answer = solve();
    std::reverse(b, b + m);
    answer = std::max(answer, solve());
    printf("%d\n", answer * 2);
    return 0;
}
