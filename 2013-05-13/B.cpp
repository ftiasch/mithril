#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

const int N = 100;
const int K = 100;
const int H = 25;

int n, k, h, height[N][N], init[K][2], limit[H];

const int V = H * N * N * 2 + 2;
const int E = H * N * N * 14;

const int DELTA[5][2] = {{-1, 0}, {0, -1}, {0, 0}, {0, 1}, {1, 0}};

int edge_count, first_edge[V], to[E], capacity[E], next_edge[E];

void my_add_edge(int u, int v, int w) {
    to[edge_count] = v;
    capacity[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

void add_edge(int a, int b, int c) {
    my_add_edge(a, b, c);
    my_add_edge(b, a, 0);
}

int get_id(int day, int x, int y, int type) {
    return ((day * n + x) * n + y) * 2 + type;
}

int level[V];

bool bfs(int source, int target) {
    memset(level, -1, sizeof(level));
    level[target] = 0;
    std::queue <int> queue;
    queue.push(target);
    while (!queue.empty() && level[source] == -1) {
        int u = queue.front();
        queue.pop();
        for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
            if (capacity[iter ^ 1] > 0 && level[to[iter]] == -1) {
                level[to[iter]] = level[u] + 1;
                queue.push(to[iter]);
            }
        }
    }
    return level[source] != -1;
}

int dfs(int u, int target, int limit) {
    if (u == target) { 
        return limit;
    }
    int delta = 0;
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        if (capacity[iter] > 0 && level[u] == level[to[iter]] + 1) {
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
    while (scanf("%d%d%d", &n, &k, &h) == 3 && n + k + h > 0) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                scanf("%d", &height[i][j]);
            }
        }
        for (int i = 0; i < k; ++ i) {
            scanf("%d%d", &init[i][0], &init[i][1]);
        }
        limit[0] = INT_MIN;
        h ++;
        for (int i = 1; i < h; ++ i) {
            scanf("%d", limit + i);
        }
        edge_count = 0;
        memset(first_edge, -1, sizeof(first_edge));
        int source = n * n * h * 2;
        int target = source + 1;
        for (int i = 0; i < h; ++ i) {
            for (int x = 0; x < n; ++ x) {
                for (int y = 0; y < n; ++ y) {
                    if (height[x][y] <= limit[i]) {
                        continue;
                    }
                    add_edge(get_id(i, x, y, 0), get_id(i, x, y, 1), 1);
                    if (i + 1 < h) {
                        for (int k = 0; k < 5; ++ k) {
                            int xx = x + DELTA[k][0];
                            int yy = y + DELTA[k][1];
                            if (0 <= xx && xx < n && 0 <= yy && yy < n) {
                                add_edge(get_id(i, x, y, 1), get_id(i + 1, xx, yy, 0), 1);
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < k; ++ i) {
            add_edge(source, get_id(0, init[i][0], init[i][1], 0), 1);
        }
        for (int x = 0; x < n; ++ x) {
            for (int y = 0; y < n; ++ y) {
                add_edge(get_id(h - 1, x, y, 1), target, 1);
            }
        }
        int answer = 0;
        while (bfs(source, target)) {
            answer += dfs(source, target, INT_MAX);
        }
        printf("%d\n", answer);
    }
    return 0;
}
