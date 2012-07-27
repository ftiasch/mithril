#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 50;
const int V = N + N + 2;
const int E = (N + N + N * N) * 2;

int n, m, a[N][N], edgeCount, firstEdge[V], to[E], capacity[E], cost[E], nextEdge[E], pre[V], dist[V];
bool visit[V];

void myAddEdge(int u, int v, int c, int w) {
    to[edgeCount] = v;
    capacity[edgeCount] = c;
    cost[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void addEdge(int u, int v, int c, int w) {
    myAddEdge(u, v, c, w);
    myAddEdge(v, u, 0, -w);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%d", &a[i][j]);
        }
    }
    int source = n + n;
    int target = n + n + 1;
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < n; ++ i) {
        addEdge(source, i, m, 0);
        addEdge(n + i, target, m, 0);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            addEdge(i, n + j, 1, a[i][j]);
        }
    }
    int nodeCount = n + n + 2;
    int result = 0;
    while (true) {
        for (int i = 0; i < nodeCount; ++ i) {
            dist[i] = INT_MAX;
        }
        dist[source] = 0;
        memset(visit, 0, sizeof(visit));
        queue <int> Q;
        Q.push(source);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            visit[u] = false;
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                if (capacity[iter] > 0 && dist[u] + cost[iter] < dist[to[iter]]) {
                    pre[to[iter]] = iter;
                    dist[to[iter]] = dist[u] + cost[iter];
                    if (!visit[to[iter]]) {
                        visit[to[iter]] = true;
                        Q.push(to[iter]);
                    }
                }
            }
        }
        if (dist[target] == INT_MAX) {
            break;
        }
        for (int i = target; i != source; i = to[pre[i] ^ 1]) {
            capacity[pre[i]] --;
            capacity[pre[i] ^ 1] ++;
            result += cost[pre[i]];
        }
    }
    printf("%d\n", result);
    return 0;
}
