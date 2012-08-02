#include <cstdio>
#include <cstring>
using namespace std;

const int N = 100000;
const int M = 400000;

int n, m, edgeCount, firstEdge[N], to[M], nextEdge[M], degree[N], result[M], timeStamp;
bool visit[M], used[N];

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void dfs(int u) {
    if (!used[u]) {
        used[u] = true;
        for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
            if (!visit[iter >> 1]) {
                visit[iter >> 1] = true;
                result[iter >> 1] = ++ timeStamp;
                int v = to[iter];
                dfs(v);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b --;
        degree[a] ++;
        degree[b] ++;
        addEdge(a, b);
        addEdge(b, a);
    }
    if (n == 2 && m == 1) {
        puts("1");
    } else {
        int degreeOneCount = 0;
        for (int i = 0; i < n; ++ i) {
            degreeOneCount += degree[i] == 1;
        }
        if (degreeOneCount > 1) {
            puts("-1");
        } else {
            int root = 0;
            if (degreeOneCount == 1) {
                while (degree[root] != 1) {
                    root ++;
                }
            }
            timeStamp = 0;
            memset(used, 0, sizeof(used));
            memset(visit, 0, sizeof(visit));
            dfs(root);
            for (int i = 0; i < m; ++ i) {
                printf("%d\n", result[i]);
            }
        }
    }
    return 0;
}
