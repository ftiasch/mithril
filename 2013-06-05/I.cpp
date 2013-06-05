#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

const int N = 22;
const int DELTA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int n, m;
char map[N][N + 1];

int get_id(int t, int i, int j) {
    return (i * m + j) * 4 + t;
}

const int V = N * N * 4 + 2;
const int E = N * N * 10;

int edge_count, first_edge[V], to[E], capacity[E], next_edge[E];

void _add_edge(int u, int v, int w) {
    to[edge_count] = v;
    capacity[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

void add_edge(int a, int b, int c) {
//printf("%d->%d\n", a, b);
    _add_edge(a, b, c);
    _add_edge(b, a, 0);
}

int level[V];

bool bfs(int source, int target) {
    memset(level, -1, sizeof(level));
    level[source] = 0;
    std::queue <int> queue;
    queue.push(source);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
            if (capacity[iter] > 0 && level[to[iter]] == -1) {
                level[to[iter]] = level[u] + 1;
                queue.push(to[iter]);
            }
        }
    }
    return level[target] != -1;
}

int dfs(int u, int target, int limit) {
    if (u == target) {
        return limit;
    }
    int delta = 0;
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        if (capacity[iter] > 0 && level[to[iter]] == level[u] + 1) {
            int ret = dfs(to[iter], target, std::min(limit - delta, capacity[iter]));
            delta += ret;
            capacity[iter] -= ret;
            capacity[iter ^ 1] += ret;
            if (delta == limit) {
                break;
            }
        }
    }
    return delta;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", map[i]);
    }
    int source = n * m * 4;
    int target = source + 1;
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (map[i][j] == 'W') {
                add_edge(source, get_id(0, i, j), 1);
            }
            if (map[i][j] == 'I') {
                add_edge(get_id(1, i, j), get_id(2, i, j), 1);
                for (int k = 0; k < 4; ++ k) {
                    int x = i + DELTA[k][0];
                    int y = j + DELTA[k][1];
                    if (0 <= x && x < n && 0 <= y & y < m) {
                        if (map[x][y] == 'W') {
                            add_edge(get_id(0, x, y), get_id(1, i, j), 1);
                        }
                        if (map[x][y] == 'N') {
                            add_edge(get_id(2, i, j), get_id(3, x, y), 1);
                        }
                    }
                }
            }
            if (map[i][j] == 'N') {
                add_edge(get_id(3, i, j), target, 1);
            }
        }
    }
    int answer = 0;
    while (bfs(source, target)) {
        answer += dfs(source, target, INT_MAX);
    }
    printf("%d\n", answer);
    return 0;
}
