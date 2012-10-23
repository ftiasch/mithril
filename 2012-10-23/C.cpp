#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 20000;
const int M = 100000 << 1;

int n, m, edgeCount, firstEdge[N], to[M], length[M], nextEdge[M];

void addEdge(int u, int v, int w) {
    to[edgeCount] = v;
    length[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

bool visit[N];
int shortest[N], ways[N];

int forShort[N], forWays[N], backShort[N], backWays[N];

void dijkstra(int source, int mod) {
    for (int i = 0; i < n; ++ i) {
        visit[i] = false;
        shortest[i] = INT_MAX;
    }
    shortest[source] = 0;
    ways[source] = 1;
    priority_queue <pair <int, int> > heap;
    heap.push(make_pair(0, source));
    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (visit[u]) {
            continue;
        }
        visit[u] = true;
        for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
            int v = to[iter];
            int ret = shortest[u] + length[iter];
            if (ret < shortest[v]) {
                ways[v] = 0;
                shortest[v] = ret;
                heap.push(make_pair(-shortest[v], v));
            }
            if (ret == shortest[v]) {
                ways[v] = (ways[v] + ways[u]) % mod;
            }
        }
    }
}

const int MOD = 1000000000 + 7;

int main() {
    scanf("%d%d", &n, &m);
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a --;
        b --;
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    dijkstra(0, MOD);
    for (int i = 0; i < n; ++ i) {
        forShort[i] = shortest[i];
        forWays[i] = ways[i];
    }
    dijkstra(n - 1, MOD);
    for (int i = 0; i < n; ++ i) {
        backShort[i] = shortest[i];
        backWays[i] = ways[i];
    }
    int all = backShort[0];
    int total = backWays[0];
    vector <int> result;
    for (int i = 0; i < edgeCount; i ++) {
        int u = to[i ^ 1];
        int v = to[i];
        if (forShort[u] + length[i] + backShort[v] == all && (long long)forWays[u] * backWays[v] % MOD == total) {
            result.push_back(i >> 1);
        }
    }
    printf("%d\n", (int)result.size());
    for (int i = 0; i < (int)result.size(); ++ i) {
        printf("%d%c", result[i] + 1, i == (int)result.size() - 1 ? '\n': ' ');
    }
    return 0;
}
