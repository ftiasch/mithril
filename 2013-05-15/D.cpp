#include <cassert>
#include <cstdio>
#include <cstring>

const int M = 40;

int positions[M + 1][M + 1][M + 1];
bool mark[M];

int m, now_position[M + 1];
char text[M + 1], pattern[M + 1], answer[M + 1];

int solve(int n) {
    int count = 0;
    memset(answer, 0, sizeof(answer));
    for (int s = 0; s < m; ++ s) {
        for (int i = 0; i < m; ++ i) {
            memset(mark, 0, sizeof(mark));
            for (int k = 0; k < n; ++ k) {
                pattern[k] = text[(s + positions[m][i][k]) % m];
                mark[(s + positions[m][i][k]) % m] = true;
            }
            for (int t = 0; t < m; ++ t) {
                int total = 0;
                for (int k = 0; k < m; ++ k) {
                    if (!mark[(t + k) % m]) {
                        now_position[total ++] = (t + k) % m;
                    }
                }
                for (int j = i + 1; j < m; ++ j) {
                    bool valid = true;
                    for (int k = 0; k < n && valid; ++ k) {
                        valid &= pattern[k] == text[now_position[positions[m - n][j][k]]];
                    }
                    if (valid) {
                        bool found = false;
                        for (int k = 0; k < n; ++ k) {
                            if (answer[k] != pattern[k]) {
                                found = true;
                                answer[k] = pattern[k];
                            }
                        }
                        if (found) {
                            count ++;
                        }
                        if (count >= 2) {
                            return 2;
                        }
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    for (int length = 1; length <= M; ++ length) {
        for (int delta = 0; delta < M; ++ delta) {
            memset(mark, 0, sizeof(mark));
            mark[positions[length][delta][0] = 0] = true;
            for (int i = 1; i < length; ++ i) {
#define PUSH(now) while (mark[now]) now = (now + 1) % length
                int now = (positions[length][delta][i - 1]) % length;
                int left = delta;
                while (left --) {
                    PUSH(now);
                    now = (now + 1) % length;
                }
                PUSH(now);
                mark[positions[length][delta][i] = now] = true;
            }
#undef PUSH
        }
    }
    int test_count = 0;
    while (scanf("%s", text) == 1 && strcmp(text, "X") != 0) {
        m = strlen(text);
        int n = m / 2;
        int ret = -1;
        while (n) {
            ret = solve(n);
            if (ret) {
                break;
            }
            n --;
        }
        printf("Code %d: ", ++ test_count);
        if (ret > 1) {
            puts("Codeword not unique");
        } else {
            answer[n] = '\0';
            puts(answer);
        }
    }
    return 0;
}
