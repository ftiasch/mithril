#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 400;
const int V = N + N + 4;
const int E = (N + N * 2 + N) * 3 * 2;

int n, m, relationship[N][N], nodeCount, edgeCount, firstEdge[V], to[E], capacity[E], 
    nextEdge[E], superSource, superTarget, degree[N], currentEdge[V], queue[V], level[V], solution[N];

void myAddEdge(int u, int v, int w) {
    to[edgeCount] = v;
    capacity[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void addEdge(int a, int b, int c) {
    myAddEdge(a, b, c);
    myAddEdge(b, a, 0);
}

void addEdge(int a, int b, int l, int u) {
    addEdge(superSource, b, l);
    addEdge(a, superTarget, l);
    addEdge(a, b, u - l);
}

bool bfs(int source, int target) {
    memset(level, -1, sizeof(level));
    level[target] = 0;
    int tail = 0;
    queue[tail ++] = target;
    int head = 0;
    while (head != tail && level[source] == -1) {
        int v = queue[head ++];
        for (int iter = firstEdge[v]; iter != -1; iter = nextEdge[iter]) {
            if (level[to[iter]] == -1 && capacity[iter ^ 1] > 0) {
                level[to[iter]] = level[v] + 1;
                queue[tail ++] = to[iter];
            }
        }
    }
    return level[source] != -1;
}

int dfs(int source, int target, int limit) {
    if (source == target) {
        return limit;
    }
    int delta = limit;
    for (int &iter = currentEdge[source]; iter != -1; iter = nextEdge[iter]) {
        if (level[source] == level[to[iter]] + 1 && capacity[iter] > 0) {
            int ret = dfs(to[iter], target, min(limit, capacity[iter]));
            delta -= ret;
            capacity[iter] -= ret;
            capacity[iter ^ 1] += ret;
            if (delta == 0) {
                break;
            }
        }
    }
    return limit - delta;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(degree, 0, sizeof(degree));
    memset(relationship, 0, sizeof(relationship));
    for (int i = 0; i < m; ++ i) {
        int k;
        scanf("%d", &k);
        while (k > 0) {
            k --;
            int x;
            scanf("%d", &x);
            relationship[abs(x) - 1][i] = x;
            degree[abs(x) - 1] ++;
        }
    }
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    int source = n + m;
    int target = n + m + 1;
    superSource = n + m + 2;
    superTarget = n + m + 3;
    for (int i = 0; i < n; ++ i) {
        if (degree[i] == 2) {
            addEdge(source, i, 1, 1);
        } else {
            addEdge(source, i, 0, 1);
        }
    }
    for (int i = 0; i < m; ++ i) {
        addEdge(n + i, target, 1, 1);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (relationship[i][j] != 0) {
                addEdge(i, n + j, 0, 1);
            }
        }
    }
    addEdge(target, source, 0, INT_MAX);
    nodeCount = n + m + 4;
    while (bfs(superSource, superTarget)) {
        for (int i = 0; i < nodeCount; ++ i) {
            currentEdge[i] = firstEdge[i];
        }
        dfs(superSource, superTarget, INT_MAX);
    }
    bool valid = true;
    for (int iter = firstEdge[superSource]; iter != -1; iter = nextEdge[iter]) {
        if (capacity[iter] > 0) {
            valid = false;
        }
    }
    memset(solution, 0, sizeof(solution));
    if (valid) {
        puts("YES");
        for (int i = 0; i < n; ++ i) {
            for (int iter = firstEdge[i]; iter != -1; iter = nextEdge[iter]) {
                if (n <= to[iter] && to[iter] < n + m) {
                    solution[i] = (capacity[iter] > 0) ^ (relationship[i][to[iter] - n] > 0);
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            printf("%d%c", solution[i], i == n - 1? '\n': ' ');
        }
    } else {
        puts("NO");
    }
    
    return 0;
}
