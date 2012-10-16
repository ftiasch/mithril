#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 20;

int n, m, h, s, grid[N][N];

int getLocation(int x, int y) {
    return x * m + y;
}

const int V = N * N + 2;
const int E = (V * 4 + V * 2) * 2;

int nodeCount, edgeCount, firstEdge[V], to[E], capacity[E], flow[E], cost[E], nextEdge[E];

void myAddEdge(int u, int v, int c, int w) {
    to[edgeCount] = v;
    flow[edgeCount] = 0;
    capacity[edgeCount] = c;
    cost[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void addEdge(int a, int b, int c, int w) {
    myAddEdge(a, b, c, w);
    myAddEdge(b, a, 0, -w);
}

const int DELTA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int visit[V], shortest[V], predecessor[V];

int match[V];
bool occupy[V];
vector <int> order[V];

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

int main() {
    scanf("%d%d%d%d", &n, &m, &h, &s);
    memset(grid, -1, sizeof(grid));
    for (int i = 0; i < h; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        grid[-- x][-- y] = i;
    }
    for (int i = 0; i < s; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        grid[-- x][-- y] = -2;
    }
    nodeCount = n * m + 2;
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            for (int k = 0; k < 4; ++ k) {
                int x = i + DELTA[k][0];
                int y = j + DELTA[k][1];
                if (0 <= x && x < n && 0 <= y && y < m) {
                    addEdge(getLocation(i, j), getLocation(x, y), INT_MAX, 1);
                }
            }
        }
    }
    int source = n * m;
    int target = n * m + 1;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (grid[i][j] >= 0) {
                addEdge(source, getLocation(i, j), 1, 0);
            }
            if (grid[i][j] == -1) {
                addEdge(getLocation(i, j), target, 1, 0);
            }
        }
    }
    while (true) {
        for (int i = 0; i < nodeCount; ++ i) {
            visit[i] = false;
            shortest[i] = INT_MAX;
        }
        visit[source] = true;
        shortest[source] = 0;
        queue <int> opened;
        opened.push(source);
        while(!opened.empty()) {
            int u = opened.front();
            opened.pop();
            visit[u] = false;
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                if (flow[iter] < capacity[iter] && shortest[u] + cost[iter] < shortest[to[iter]]) {
                    shortest[to[iter]] = shortest[u] + cost[iter];
                    predecessor[to[iter]] = iter;
                    if (!visit[to[iter]]) {
                        visit[to[iter]] = true;
                        opened.push(to[iter]);
                    }
                }
            }
        }
        if (shortest[target] == INT_MAX) {
            break;
        }
        for (int i = target; i != source; i = to[predecessor[i] ^ 1]) {
            flow[predecessor[i]] ++;
            flow[predecessor[i] ^ 1] --;
        }
    }
    memset(occupy, 0, sizeof(occupy));
    for (int _ = 0; _ < h; ++ _) {
        vector <int> path;
        int u = source;
        while (u != target) {
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                if (flow[iter] > 0) {
                    flow[iter] --;
                    path.push_back(u = to[iter]);
                    break;
                }
            }
        }
        u = path.front();
        path.pop_back();
        occupy[match[grid[u / m][u % m]] = path.back()] = true;
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (grid[i][j] >= 0) {
                vector <pair <int, pair <int, int> > > list;
                for (int x = 0; x < n; ++ x) {
                    for (int y = 0; y < m; ++ y) {
                        if (grid[x][y] == -1) {
                            list.push_back(make_pair(abs(i - x) + abs(j - y), make_pair(x, y)));
                        }
                    }
                }
                sort(list.begin(), list.end());
                foreach (iter, list) {
                    int x = iter->second.first;
                    int y = iter->second.second;
                    order[grid[i][j]].push_back(getLocation(x, y));
                }
            }
        }
    }
    while (true) {
        bool found = false;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (grid[i][j] >= 0) {
                    int id = grid[i][j];
                    int k = 0;
                    while (match[id] != order[id][k] && occupy[order[id][k]]) {
                        k ++;
                    }
                    if (match[id] != order[id][k]) {
                        found = true;
                        occupy[match[id]] = false;
                        occupy[order[id][k]] = true;
                        match[id] = order[id][k];
                    }
                }
            }
        }
        if (!found) {
            break;
        }
    }
    vector <int> result;
    memset(visit, 0, sizeof(visit));
    memset(occupy, 0, sizeof(occupy));
    for (int _ = 0; _ < h; ++ _) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (grid[i][j] >= 0) {
                    int id = grid[i][j];
                    if (!visit[id]) {
                        int k = 0;
                        while (match[id] != order[id][k] && occupy[order[id][k]]) {
                            k ++;
                        }
                        if (match[id] == order[id][k]) {
                            visit[id] = true;
                            occupy[match[id]] = true;
                            result.push_back(id);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < (int)result.size(); ++ i) {
        printf("%d%c", result[i] + 1, i == (int)result.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
