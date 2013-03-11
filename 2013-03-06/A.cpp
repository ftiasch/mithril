#include <cstdio>
#include <cstring>
#include <algorithm>

const int K = 5;

const int N = 20;

int n, m, k, length[K];
int map[N][N];
int id[N * N];

bool found = false;

bool graph[N * N][N * N];

void orz(int x, int y) {
    graph[x][y] = graph[y][x] = true;
}

void dfs(int x, int y, int total) {
    if (found) {
        return;
    }
    if (y == m) {
        dfs(x + 1, 0, total);
    } else {
        if (x == n) {
            found = true;
            memset(id, -1, sizeof(id));
            puts("YES");
            memset(graph, 0, sizeof(graph));
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < m; ++ j) {
                    if (i + 1 < n) {
                        orz(map[i][j], map[i + 1][j]);
                    }
                    if (j + 1 < m) {
                        orz(map[i][j], map[i][j + 1]);
                    }
                }
            }
            for (int i = 0; i < total; ++ i) {
                id[i] = 0;
                while (true) {
                    bool conflict = false;
                    for (int j = 0; j < total; ++ j) {
                        if (graph[i][j] && i != j && id[i] == id[j]) {
                            conflict = true;
                        }
                    }
                    if (!conflict) {
                        break;
                    }
                    id[i] ++;
                }
            }
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < m; ++ j) {
                    putchar('a' + id[map[i][j]]);
                }
                puts("");
            }
        }
        if (!found) {
            if (map[x][y] == -1) {
                for (int i = 0; i < k; ++ i) {
                    if (y + length[i] <= m) {
                        bool valid = true;
                        for (int j = 0; j < length[i]; ++ j) {
                            valid &= map[x][y + j] == -1;
                        }
                        if (valid) {
                            for (int j = 0; j < length[i]; ++ j) {
                                map[x][y + j] = total;
                            }
                            dfs(x, y + 1, total + 1);
                            for (int j = 0; j < length[i]; ++ j) {
                                map[x][y + j] = -1;
                            }
                        }
                    }
                    if (x + length[i] <= n) {
                        bool valid = true;
                        for (int j = 0; j < length[i]; ++ j) {
                            valid &= map[x + j][y] == -1;
                        }
                        if (valid) {
                            for (int j = 0; j < length[i]; ++ j) {
                                map[x + j][y] = total;
                            }
                            dfs(x, y + 1, total + 1);
                            for (int j = 0; j < length[i]; ++ j) {
                                map[x + j][y] = -1;
                            }
                        }
                    }
                }
            } else {
                dfs(x, y + 1, total);
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < k; ++ i) {
        scanf("%d", length + i);
    }
    std::sort(length, length + k);
    int gcd = 0;
    for (int i = 0; i < k; ++ i) {
        gcd = std::__gcd(gcd, length[i]);
    }
    if (n * m % gcd != 0) {
        puts("NO");
    } else {
        memset(map, -1, sizeof(map));
        dfs(0, 0, 0);
        if (!found) {
            puts("NO");
        }
    }
    return 0;
}
