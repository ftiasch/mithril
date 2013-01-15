#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 20000;
const int M = 200000 << 1;

int n, m, edge_count, first_edge[N], to[M], next_edge[M];

bool used[M];

void add_edge(int u, int v) {
    to[edge_count] = v;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

int depth[N], lowest[N], size[N];
long long answer[N], binom[N + 1];

void dfs(int p, int u) {
    lowest[u] = depth[u] = p == -1 ? 0 : depth[p] + 1;
    size[u] = 1;
    answer[u] = binom[n - 1];
    int left = n - 1;
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        if (used[iter >> 1]) {
            continue;
        }
        used[iter >> 1] = true;
        if (depth[to[iter]] == -1) {
            dfs(u, to[iter]);
            if (lowest[to[iter]] >= depth[u]) {
                left -= size[to[iter]];
                answer[u] -= binom[size[to[iter]]];
            }
            size[u] += size[to[iter]];
            lowest[u] = std::min(lowest[u], lowest[to[iter]]);
        } else {
            lowest[u] = std::min(lowest[u], depth[to[iter]]);
        }
    }
    answer[u] -= binom[left];
}

int main() {
    scanf("%d%d", &n, &m);
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b --;
        add_edge(a, b);
        add_edge(b, a);
    }
    memset(used, 0, sizeof(used));
    memset(depth, -1, sizeof(depth));
    for (int i = 0; i <= n; ++ i) {
        binom[i] = (long long)i * (i - 1) / 2;
    }
    dfs(-1, 0);
    for (int i = 0; i < n; ++ i) {
        std::cout << answer[i] + n - 1 << std::endl;
    }
    return 0;
}
