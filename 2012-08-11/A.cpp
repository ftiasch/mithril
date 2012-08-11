#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 3333;

int n, edgeCount, firstEdge[N], to[N << 1], nextEdge[N << 1], destroyed[N], 
    size[N], maxSubTree[N], result[N], minimum[N][N], degree[N];
vector <int> nodes;

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void search(int p, int u) {
    nodes.push_back(u);
    size[u] = 1;
    maxSubTree[u] = 0;
    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        int v = to[iter];
        if (!destroyed[v] && v != p) {
            search(u, v);
            size[u] += size[v];
            maxSubTree[u] = max(maxSubTree[u], size[v]);
        }
    }
}

void dfs(int p, int u) {
    size[u] = 1;
    nodes.push_back(u);
    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        int v = to[iter];
        if (!destroyed[v] && v != p) {
            dfs(u, v);
            size[u] += size[v];
        }
    }
}

void divide(int root) {
    nodes.clear();
    search(-1, root);
    int allSize = size[root];
    int newRoot = -1;
    int newRootSize = INT_MAX;
    for (vector <int> :: iterator iter = nodes.begin(); iter != nodes.end(); ++ iter) {
        int ret = max(maxSubTree[*iter], allSize - size[*iter]);
        if (ret < newRootSize) {
            newRoot = *iter;
            newRootSize = ret;
        }
    }
    nodes.clear();
    dfs(-1, newRoot);
    int n = nodes.size();
    minimum[n][0] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        int s = n - i;
        for (int j = 0; j <= s; ++ j) {
            minimum[i][j] = INT_MAX;
            int v = i + size[nodes[i]];
            if (j <= n - v) {
                minimum[i][j] = min(minimum[i][j], minimum[v][j]);
            }
            if (j > 0) {
                minimum[i][j] = min(minimum[i][j], minimum[i + 1][j - 1] + degree[nodes[i]]);
            }
        }
    }
    for (int i = 1; i <= n; ++ i) {
        result[i] = min(result[i], minimum[0][i]);
    }
    destroyed[newRoot] = true;
    for (int iter = firstEdge[newRoot]; iter != -1; iter = nextEdge[iter]) {
        int v = to[iter];
        if (!destroyed[v]) {
            divide(v);
        }
    }
}

int main() {
    scanf("%d", &n);
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b --;
        addEdge(a, b);
        addEdge(b, a);
        degree[a] ++;
        degree[b] ++;
    }
    memset(destroyed, 0, sizeof(destroyed));
    for (int i = 0; i <= n; ++ i) {
        result[i] = INT_MAX;
    }
    divide(0);
    int queryCount;
    scanf("%d", &queryCount);
    while (queryCount > 0) {
        queryCount --;
        int size;
        scanf("%d", &size);
        printf("%d\n", result[size] - (size - 1) * 2);
    }
    return 0;
}
