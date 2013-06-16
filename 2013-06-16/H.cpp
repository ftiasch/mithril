#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 111111;
const int M = 55555;

int n, m;

int edge_count, first_edge[N], to[M << 1], next_edge[M << 1], cnt;

void add_edge(int u, int v) {
    to[edge_count] = v;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

int depth[N], lowest[N], count[N];

int top, stack[N];

int bcc_count;
std::vector <int> bcc[N];

void dfs(int p, int u) {
    lowest[u] = depth[u] = ++ cnt;
    stack[++ top] = u;
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        int v = to[iter];
        if (depth[v] == -1) {
            int tmp = top;
            dfs(u, v);
            lowest[u] = std::min(lowest[u], lowest[v]);
            if (lowest[v] >= depth[u]) {
                bcc[++ bcc_count].clear();
                for (int k = tmp + 1; k <= top; ++ k) {
                    count[stack[k]] ++;
                    bcc[bcc_count].push_back(stack[k]);
                }
                count[u] ++;
                bcc[bcc_count].push_back(u);
                top = tmp;
            }
        } else if (v != p) {
            lowest[u] = std::min(lowest[u], depth[v]);
        }
    }
}

int main() {
    int test_count = 0;
    while (scanf("%d", &m) == 1 && m) {
        n = 0;
        edge_count = 0;
        memset(first_edge, -1, sizeof(first_edge));
        for (int i = 0; i < m; ++ i) {
            int a, b;
            scanf("%d%d", &a, &b);
            n = std::max(a, n);
            n = std::max(b, n);
            add_edge(a, b);
            add_edge(b, a);
        }
        cnt = 0;
        memset(depth, -1, sizeof(depth));
        top = 0;
        bcc_count = 0;
        memset(count, 0, sizeof(count));
        dfs(0, 1);
        int total = 0;
        long long ways = 1;
        for (int i = 1; i <= bcc_count; ++ i) {
            int size = 0;
            foreach (iter, bcc[i]) {
//printf("%d ", *iter);
                size += count[*iter] > 1;
            }
            if (size == 1) {
                total ++;
                ways *= bcc[i].size() - 1;
            }
//puts("");
        }
        if (total == 0) {
            total = 2;
            ways = (long long)n * (n - 1) / 2;
        }
        std::cout << "Case " << (++ test_count) << ": " << total << " " << ways << std::endl;
    }
    return 0;
}
