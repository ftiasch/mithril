#include <cstdio>
#include <cstring>
#include <climits>
#include <deque>
#include <algorithm>
using namespace std;

const int N = 10000;
const int M = 6 * N;
const int DELTA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int n, m, cost;
char map[N], buffer[N];

int firstEdge[N], edgeCount, to[M], length[M], nextEdge[M];
int dist[N];
bool visit[N];

void addEdge(int u, int v, int w) {
    to[edgeCount] = v;
    length[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &cost) == 3) {
        for (int i = 0; i < n; ++ i) {
            scanf("%s", buffer);
            for (int j = 0; j < m; ++ j) {
                map[i * m + j] = buffer[j];
            }
        }
        int nm = n * m;
        int source =-1, target = -1;
        for (int i = 0; i < nm; ++ i) {
            if (map[i] == 'Y') {
                source = i;
                map[i] = '*';
            }
            if (map[i] == 'C') {
                target = i;
                map[i] = '*';
            }
        }
        edgeCount = 0;
        fill(firstEdge, firstEdge + (nm + 1), -1);
        for (int k = 0; k < n * m; ++ k) {
            int i = k / m;
            int j = k % m;
            int ij = i * m + j;
            for (int t = 0; t < 4; ++ t) {
                int x = i + DELTA[t][0];
                int y = j + DELTA[t][1];
                int xy = x * m + y;
                if (0 <= x && x < n && 0 <= y && y < m && map[xy] != '#') {
                    addEdge(ij, xy, map[ij] == 'P'? 0: cost);
                }
                if (map[ij] == 'P') {
                    addEdge(ij, nm, 0);
                    addEdge(nm, ij, 0);
                }
            }
        }
        fill(dist, dist + (nm + 1), INT_MAX);
        dist[source] = 0;
        fill(visit, visit + (nm + 1), false);
        deque <int> q;
        q.push_back(source);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            visit[u] = false;
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                if (dist[u] + length[iter] < dist[to[iter]]) {
                    dist[to[iter]] = dist[u] + length[iter];
                    if (!visit[to[iter]]) {
                        visit[to[iter]] = true;
                        if (length[iter] == 0) {
                            q.push_front(to[iter]);
                        } else {
                            q.push_back(to[iter]);
                        }
                    }
                }
            }
        }
        if (dist[target] == INT_MAX) {
            puts("Damn teoy!");
        } else {
            printf("%d\n", dist[target] - cost);
        }
    }
    return 0;
}
