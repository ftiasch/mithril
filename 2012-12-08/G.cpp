#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using std::min;
using std::max;

const int N = 10000;
const int M = 20000 << 1;

int n, m, node_cost[N];

int edge_count, first_edge[N], to[M], length[M], next_edge[M];
long long edge_cost[M];

void add_edge(int u, int v, int w) {
    to[edge_count] = v;
    length[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

bool visit[N], used[M];
int label[N], label_count, lowest[N], tree_size[N], total_size;

void count_size(int u) {
    if (!visit[u]) {
        visit[u] = true;
        total_size ++;
        for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
            count_size(to[iter]);
        }
    }
}

void dfs(int u) {
    label[u] = lowest[u] = label_count ++;
    tree_size[u] = 1;
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        if (!used[iter >> 1]) {
            used[iter >> 1] = true;
            edge_cost[iter >> 1] = 0;
            int v = to[iter];
            if (label[v] == -1) {
                dfs(v);
                lowest[u] = min(lowest[u], lowest[v]);
                if (lowest[v] > label[u]) {
                    edge_cost[iter >> 1] = (long long)tree_size[v] * (total_size - tree_size[v]) * length[iter];
                }
                tree_size[u] += tree_size[v];
            } else {
                lowest[u] = min(lowest[u], label[v]);
            }
        }
    }
}

long long left[N];

void construct(int u) {
    if (!visit[u]) {
        visit[u] = true;
        for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
            int v = to[iter];
            long long c = edge_cost[iter >> 1];
            if (c && !visit[v]) {
                construct(v);
                if (c <= left[v]) {
                    left[v] -= c;
                } else {
                    left[u] -= c;
                }
            }
        }
    }
}

bool check(long long limit) {
    for (int i = 0; i < n; ++ i) {
        visit[i] = false;
        left[i] = limit - node_cost[i];
    }
    for (int i = 0; i < n; ++ i) {
        if (!visit[i]) {
            construct(i);
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (left[i] < 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d", node_cost + i);
        }
        edge_count = 0;
        memset(first_edge, -1, sizeof(first_edge));
        for (int i = 0; i < m; ++ i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            a --, b --;
            add_edge(a, b, c);
            add_edge(b, a, c);
        }
        memset(visit, 0, sizeof(visit));
        memset(label, -1, sizeof(label));
        memset(used, 0, sizeof(used));
        label_count = 0;
        for (int i = 0; i < n; ++ i) {
            if (!visit[i]) {
                total_size = 0;
                count_size(i);
                dfs(i);
            }
        }
//for (int i = 0; i < m; ++ i) {
//    printf("cost = %I64d\n", edge_cost[i]);
//}
        long long low = *std::max_element(node_cost, node_cost + n);
        long long high = 20000000000000000LL;
        while (low < high) {
            long long middle = low + high >> 1;
            if (check(middle)) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }
        std::cout << "Case " << t << ": " << high << std::endl;
    }
    return 0;
}
