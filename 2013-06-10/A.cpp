#include <cassert>
#include <cstdio>
#include <cstring>

const int N = 100000;
const int C = 26;

int n;
char text[N + 1];

int parent[N], go[N + 1][C];

int main() {
    scanf("%s", text);
    n = strlen(text);
    memset(go, -1, sizeof(go));
    parent[0] = -1;
    for (int i = 0; i < n; ++ i) {
        int t = text[i] - 'a';
        go[i][t] = i + 1;
        int p = parent[i];
        while (p != -1 && go[p][t] == -1) {
            go[p][t] = i + 1;
            p = parent[p];
        }
        parent[i + 1] = p == -1 ? 0 : go[p][t];
    }
    //for (int i = 0; i < n; ++ i) {
    //    for (int j = i, p = 0; j < n; ++ j) {
    //        int t = text[j] - 'a';
    //        assert(go[p][t] != -1);
    //        p = go[p][t];
    //    }
    //}
    int count = 0;
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j < C; ++ j) {
            count += go[i][j] != -1;
        }
    }
    printf("%d %d\n", n + 1, count);
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j < C; ++ j) {
            if (go[i][j] != -1) {
                printf("%d %d %c\n", i + 1, go[i][j] + 1, 'a' + j);
            }
        }
    }
    return 0;
}
