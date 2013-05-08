#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

using std::vector;
using std::max;

const int N = 1000000;

int n, parent[N], size[N], depth[N], maximum[N], belongs[N];
long long answer[N];
vector <int> edges[N];

void bfs(int root) {
    vector <int> order;
    order.push_back(root);
    depth[root] = 0;
    belongs[root] = -1;
    memset(parent, -1, sizeof(parent));
    for (int head = 0; head < (int)order.size(); ++ head) {
        int u = order[head];
        foreach (iter, edges[u]) {
            int v = *iter;
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                belongs[v] = belongs[u] == -1 ? v : belongs[u];
                order.push_back(v);
            }
        }
    }
    memset(maximum, 0, sizeof(maximum));
    for (int i = (int)order.size() - 1; i >= 0; -- i) {
        int u = order[i];
        size[u] = 1;
        foreach (iter, edges[u]) {
            int v = *iter;
            if (v != parent[u]) {
                size[u] += size[v];
                maximum[u] = max(maximum[u], size[v]);
            }
        }
        maximum[u] = max(maximum[u], n - size[u]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    bfs(0);
    memset(answer, 0, sizeof(answer));
    for (int i = 0; i < n; ++ i) {
        if (maximum[i] > n >> 1) {
            answer[i] = -1;
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (answer[i] != -1) {
            bfs(i);
            for (int u = 0; u < n; ++ u) {
                answer[i] += depth[u] << 1;
            }
            int should = -1;
            if (maximum[i] == (n >> 1)) {
                foreach (iter, edges[i]) {
                    if (size[*iter] == maximum[i]) {
                        should = *iter;
                    }
                }
            }
            int depest = 0;
            for (int u = 0; u < n; ++ u) {
                if (should == -1 || belongs[u] == should) {
                    depest = max(depest, depth[u]);
                }
            }
            answer[i] -= depest;
        }
        std::cout << answer[i] << std::endl;
    }
    return 0;
}
