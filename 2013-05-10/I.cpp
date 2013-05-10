#include <cstdio>
#include <cstring>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000;
const int D = 20;

int n;
std::vector <int> edges[N];

int go[N][D], depth[N];

void dfs(int p, int u) {
    depth[u] = p == -1 ? 0 : depth[p] + 1;
    go[u][0] = p;
    for (int i = 0; go[u][i] != -1; ++ i) {
        go[u][i + 1] = go[go[u][i]][i];
    }
    foreach (iter, edges[u]) {
        int v = *iter;
        if (v != p) {
            dfs(u, v);
        }
    }
}

int jump(int u, int d) {
    for (int i = 0; i < D; ++ i) {
        if (d >> i & 1) {
            u = go[u][i];
        }
    }
    return u;
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        std::swap(v, u);
    }
    v = jump(v, depth[v] - depth[u]);
    if (u == v) {
        return u;
    }
    for (int i = D - 1; i >= 0; -- i) {
        if (go[u][i] != go[v][i]) {
            u = go[u][i];
            v = go[v][i];
        }
    }
    return go[u][0];
}

int get_dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b --;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    memset(go, -1, sizeof(go));
    dfs(-1, 0);
    int q;
    scanf("%d", &q);
    while (q --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a --, b --, c --;
        printf("%d\n", (get_dist(a, c) + get_dist(b, c) - get_dist(a, b)) >> 1);
    }
    return 0;
}
