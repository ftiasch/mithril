#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 1001;
const int M = 100001;
const int Q = 200001;
const int INF = 1000000000;

int n, m, q, a[M], b[M], params[Q], dist[N], answer[Q];
bool exists[M];
char type[Q];

std::vector <int> edges[N];

void bfs(int start) {
    std::queue <int> queue;
    queue.push(start);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        foreach (iter, edges[u]) {
            if (dist[u] + 1 < dist[*iter]) {
                dist[*iter] = dist[u] + 1;
                queue.push(*iter);
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; ++ i) {
        scanf("%d%d", a + i, b + i);
    }
    memset(exists, true, sizeof(exists));
    for (int i = 1; i <= q; ++ i) {
        char buffer[2];
        scanf("%s%d", buffer, params + i);
        type[i] = *buffer;
        if (type[i] == 'U') {
            exists[params[i]] = false;
        }
    }
    for (int i = 1; i <= m; ++ i) {
        if (exists[i]) {
            edges[a[i]].push_back(b[i]);
        }
    }
    std::fill(dist, dist + (n + 1), INF);
    dist[1] = 0;
    bfs(1);
    for (int i = q; i >= 1; -- i) {
        if (type[i] == 'E') {
            int u = params[i];
            answer[i] = dist[u] == INF ? -1 : dist[u];
        } else {
            int u = a[params[i]];
            int v = b[params[i]];
            edges[u].push_back(v);
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                bfs(v);
            }
        }
    }
    for (int i = 1; i <= q; ++ i) {
        if (type[i] == 'E') {
            printf("%d\n", answer[i]);
        }
    }
    return 0;
}
