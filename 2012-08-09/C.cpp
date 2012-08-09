#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 102;

int n, a[N], g[N][N], capacity[N][N], cost[N][N], dist[N], pre[N];
bool visit[N];

int main() {
    scanf("%d", &n);
    int total = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        total += a[i];
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%d", &g[i][j]);
        }
    }
    for (int k = 0; k < n; ++ k) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    total /= n;
    int source = n;
    int target = n + 1;
    memset(cost, 0, sizeof(cost));
    memset(capacity, 0, sizeof(capacity));
    for (int i = 0; i < n; ++ i) {
        if (a[i] > total) {
            capacity[source][i] += a[i] - total;
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (a[i] < total) {
            capacity[i][target] += total - a[i];
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (a[i] > total) {
            for (int j = 0; j < n; ++ j) {
                if (a[j] < total) {
                    capacity[i][j] = INT_MAX;
                    cost[i][j] = g[i][j];
                    cost[j][i] = -g[i][j];
                }
            }
        }
    }
    int result = 0;
    while (true) {
        for (int i = 0; i < n + 2; ++ i) {
            dist[i] = INT_MAX;
        }
        dist[source] = 0;
        memset(visit, 0, sizeof(visit));
        visit[source] = true;
        queue <int> q;
        q.push(source);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            visit[u] = false;
            for (int v = 0; v < n + 2; ++ v) {
                if (capacity[u][v] > 0 && dist[u] + cost[u][v] < dist[v]) {
                    pre[v] = u;
                    dist[v] = dist[u] + cost[u][v];
                    if (!visit[v]) {
                        visit[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        if (dist[target] == INT_MAX) {
            break;
        }
        int delta = INT_MAX;
        for (int v = target; v != source; v = pre[v]) {
            delta = min(delta, capacity[pre[v]][v]);
        }
        for (int v = target; v != source; v = pre[v]) {
            capacity[pre[v]][v] -= delta;
            capacity[v][pre[v]] += delta;
            result += delta * cost[pre[v]][v];
        }
    }
    printf("%d\n", result);
    return 0;
}
