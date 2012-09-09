#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

#pragma comment(linker, "/STACK:32000000")

const int N = 100000;

int n, m, x[N], y[N];

const int M = 100000 << 1;

int edgeCount, firstEdge[N], to[M], capacity[M], nextEdge[M], currentEdge[N];
int source, target, flow, pre[N], sign;

void addEdge(int u, int v, int w) {
    to[edgeCount] = v;
    capacity[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

int level[N], queue[N];

bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    sign=t;
    level[t] = 0;
    int tail = 0;
    queue[tail ++] = t;
    int head = 0;
    while (head != tail && level[s] == -1) {
        int v = queue[head ++];
        for (int iter = firstEdge[v]; iter != -1; iter = nextEdge[iter]) {
            if (capacity[iter ^ 1] > 0 && level[to[iter]] == -1) {
                level[to[iter]] = level[v] + 1;
                queue[tail ++] = to[iter];
            }
        }
    }
    return level[s] != -1;
}

inline void push()
{
    int delta=INT_MAX,u,p;
    for (u=target;u!=source;u=to[p]){
        p=pre[u];
        delta=min(delta,capacity[p]);
        p^=1;
    }
    
    for (u=target;u!=source;u=to[p]){
        p=pre[u];
        capacity[p]-=delta;
        if (!capacity[p]){
            sign=to[p^1];
        }
        capacity[p^=1]+=delta;
    }
    flow+=delta;
}

void dfs(int u) {
    if (u == target) {
        push();
        return;
    }
    for (int &iter = currentEdge[u]; iter != -1; iter = nextEdge[iter]) {
        if (capacity[iter] > 0 && level[u] == level[to[iter]] + 1) {
            pre[to[iter]]=iter;
            dfs(to[iter]);
            if (level[sign]>level[u]) return;
            sign=target;
        }
    }
    level[u]=-1;
}

int main() {
    int testCount;
    scanf("%d", &testCount);
    while (testCount > 0) {
        testCount --;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", x + i, y + i);
        }
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
        source = min_element(x, x + n) - x;
        target = max_element(x, x + n) - x;
        flow=0;
        while (bfs(source, target)) {
            for (int i = 0; i < n; ++ i) {
                currentEdge[i] = firstEdge[i];
            }
            dfs(source);
        }
        printf("%d\n", flow);
    }
    return 0;
}
