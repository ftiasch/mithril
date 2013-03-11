#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

const int N = 50;
const int INF = 1000000000;

int n, m, d, w, x[N], y[N], c[N];

int square(int x) {
    return x * x;
}

int get_distance(int i, int j) {
    return square(x[i] - x[j]) + square(y[i] - y[j]);
}

const int V = N + 1 << 1;

int capacity[V][V];
double cost[V][V];

void _add_edge(int u, int v, int c, int w) {
    capacity[u][v] = c;
    cost[u][v] = w;
}

void add_edge(int u, int v, int c, int w) {
    _add_edge(u, v, c, w);
    _add_edge(v, u, 0, -w);
}

int need[N + 1], optimum[N + 1];

bool visit[V];
int distance[V], back[V];


int main() {
    scanf("%d%d%d%d", &n, &m, &d, &w);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", x + i, y + i, c + i);
    }
    memset(capacity, 0, sizeof(capacity));
    int source = n << 1;
    int target = source + 1;
    for (int i = 0; i < n; ++ i) {
        add_edge(i, n + i, c[i], 0);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j && get_distance(i, j) <= square(d)) {
                add_edge(n + i, j, INF, 1);
            }
        }
    }
    if (w <= d) {
        add_edge(source, target, INF, 1);
    }
    for (int i = 0; i < n; ++ i) {
        if (y[i] <= d) {
            add_edge(source, i, INF, 1);
        }
        if (w - y[i] <= d) {
            add_edge(n + i, target, INF, 1);
        }
    }
    memset(need, -1, sizeof(need));
    need[0] = 0;
    for (int now = 1; now <= m; ++ now) {
        for (int i = 0; i <= target; ++ i) {
            distance[i] = INT_MAX;
        }
        distance[source] = 0;
        memset(visit, 0, sizeof(visit));
        std::queue <int> queue;
        queue.push(source);
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            visit[u] = false;
            for (int v = 0; v <= target; ++ v) {
                if (capacity[u][v] > 0 && distance[u] + cost[u][v] < distance[v]) {
                    back[v] = u;
                    distance[v] = distance[u] + cost[u][v];
                    if (!visit[v]) {
                        visit[v] = true;
                        queue.push(v);
                    }
                }
            }
        }
        if (distance[target] == INT_MAX) {
            break;
        }
        need[now] = distance[target];
        for (int i = target; i != source; i = back[i]) {
            capacity[back[i]][i] --;
            capacity[i][back[i]] ++;
        }
    }
    if (need[1] == -1) {
        puts("IMPOSSIBLE");
        return 0;
    }
    optimum[0] = 0;
    for (int i = 1; i <= m; ++ i) {
        optimum[i] = INT_MAX;
        for (int j = 1; j <= i; ++ j) {
            if (need[j] != -1) {
                optimum[i] = std::min(optimum[i], std::max(optimum[i - j] + 1, need[j]));
            }
        }
    }
    printf("%d\n", optimum[m]);
    return 0;
}
