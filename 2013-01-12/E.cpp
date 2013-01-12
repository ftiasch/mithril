#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

const int N = 10000;
const int M = 6 * N;

int n, m;

int edge_count, first_edge[N], to[M], flow[M], capacity[M], next_edge[M];
int current_edge[N], level[N];

void add_edge(int u, int v, int w) {
    to[edge_count] = v;
    flow[edge_count] = 0;
    capacity[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

bool bfs(int source, int target) {
    std::queue <int> queue;
    queue.push(target);
    memset(level, -1, sizeof(level));
    level[target]  = 0;
    while (!queue.empty() && level[source] == -1) {
        int u = queue.front();
        queue.pop();
        for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
            if (flow[iter ^ 1] < capacity[iter ^ 1] && level[to[iter]] == -1) {
                level[to[iter]] = level[u] + 1;
                queue.push(to[iter]);
            }
        }
    }
    return level[source] != -1;
}

int dfs(int source, int target, int limit) {
    if (source == target) {
        return limit;
    }
    int delta = 0;
    for (int &iter = current_edge[source]; iter != -1; iter = next_edge[iter]) {
        if (flow[iter] < capacity[iter] && level[source] == level[to[iter]] + 1) {
            int tmp = dfs(to[iter], target, std::min(limit - delta, capacity[iter] - flow[iter]));
            flow[iter] += tmp;
            flow[iter ^ 1] -= tmp;
            delta += tmp;
            if (delta == limit) {
                break;
            }
        }
    }
    return delta;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%*d%*d");
    }
    scanf("%d", &m);
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a --;
        b --;
        add_edge(a, b, c);
        add_edge(b, a, c);
    }
    int answer = 0;
    while (bfs(0, n - 1)) {
        for (int i = 0; i < n; ++ i) {
            current_edge[i] = first_edge[i];
        }
        answer += dfs(0, n - 1, INT_MAX);
    }
    printf("%d\n", answer);
    for (int i = 0; i < m; ++ i) {
        int b = to[(i << 1) | 1];
        int a = to[i << 1];
        if (flow[(i << 1) | 1] <= 0) {
            std::swap(a, b);
        }
        printf("%d %d %d\n", 1 + a, 1 + b, std::abs(flow[i << 1]));
    }
    return 0;
}
