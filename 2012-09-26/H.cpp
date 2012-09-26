#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
using namespace std;

const int N = 100;
const int M = 5000 * 5 * 2;

int n, m, limit;
int edgeCount, firstEdge[N], to[M], capacity[M], cost[M], nextEdge[M];
int dist[N], pre[N];
bool visit[N];

void myAddEdge(int u, int v, int c, int w) {
    to[edgeCount] = v;
    capacity[edgeCount] = c;
    cost[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void addEdge(int a, int b, int c) {
    myAddEdge(a, b, 1, c);
    myAddEdge(b, a, 0, -c);
}

int main() {
    while (scanf("%d%d%d", &n, &m, &limit) == 3) {
        edgeCount = 0;
        memset(firstEdge, -1, sizeof(firstEdge));
        for (int i = 0; i < m; ++ i) {
            int u, v, a, c;
            scanf("%d%d%d%d", &u, &v, &a, &c);
            u --;
            v --;
            for (int i = 0; i < c; ++ i) {
                addEdge(u, v, a * ((i + 1) * (i + 1) - i * i));
            }
        }
        int result = 0;
        while (limit > 0) {
            for (int i = 0; i < n; ++ i) {
                dist[i] = INT_MAX;
            }
            dist[0] = 0;
            memset(visit, 0, sizeof(visit));
            queue <int> q;
            q.push(0);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                visit[u] = false;
                for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                    if (capacity[iter] > 0 && dist[u] + cost[iter] < dist[to[iter]]) {
                        pre[to[iter]] = iter;
                        dist[to[iter]] = dist[u] + cost[iter];
                        if (!visit[to[iter]]) {
                            visit[to[iter]] = true;
                            q.push(to[iter]);
                        }
                    }
                }
            }
            if (dist[n - 1] == INT_MAX) {
                break;
            }
            for (int i = n - 1; i != 0; i = to[pre[i] ^ 1]) {
                result += cost[pre[i]];
                capacity[pre[i]] --;
                capacity[pre[i] ^ 1] ++;
            }
            limit --;
        }
        if (limit > 0) {
            puts("-1");
        } else {
            printf("%d\n", result);
        }
    }
    return 0;
}
