#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100000;

int n, edgeCount, firstEdge[N], to[N << 1], nextEdge[N << 1];

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

const int D = 20;

int depth[N], go[N][D], up[N], down[N];

void dfs(int p, int u) {
    depth[u] = p == -1 ? 0 : depth[p] + 1;
    go[u][0] = p;
    for (int i = 0; go[u][i] != -1; ++ i) {
        go[u][i + 1] = go[go[u][i]][i];
    }
    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        int v = to[iter];
        if (v != p) {
            down[v] = down[u] + !(iter & 1);
            up[v] = up[u] + (iter & 1);
            dfs(u, v);
        }
    }
}

int jump(int u, int d) {
    for (int i = D - 1; i >= 0; -- i) {
        if (1 << i <= d) {
            u = go[u][i];
            d -= 1 << i;
        }
    }
    return u;
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        swap(u, v);
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

int main() {
    scanf("%d", &n);
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        addEdge(a, b);
        addEdge(b, a);
    }
    memset(go, -1, sizeof(go));
    up[0] = down[0] = 0;
    dfs(-1, 0);
    int m;
    scanf("%d", &m);
    while (m --) { 
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        int c = lca(a, b);
        puts(up[a] - up[c] + down[b] - down[c] == depth[a] + depth[b] - 2 * depth[c] ? "Yes" : "No");
    }
    return 0;
}
