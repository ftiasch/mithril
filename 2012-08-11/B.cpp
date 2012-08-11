#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10000;
const int M = 100000;

int n, m, a[M], b[M], firstEdge[N], to[M], nextEdge[M], labelCount, label[N], lowest[N], componentCount, componentID[N], visitCount[N], componentSize[N];
bool visit[N];
vector <int> stack, adjacent[N];

void dfs(int u) {
    if (label[u] == -1) {
        int ret = label[u] = lowest[u] = labelCount ++;
        stack.push_back(u);
        for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
            int v = to[iter];
            dfs(v);
            ret = min(ret, lowest[v]);
        }
        lowest[u] = ret;
        if (label[u] == lowest[u]) {
            while (true) {
                int v = stack.back();
                stack.pop_back();
                lowest[v] = INT_MAX;
                componentID[v] = componentCount;
                componentSize[componentCount] ++;
                if (u == v) {
                    break;
                }
            }
            componentCount ++;
        }
    }
}

void search(int u) {
    if (!visit[u]) {
        visit[u] = true;
        visitCount[u] ++;
        for (vector <int> :: iterator iter = adjacent[u].begin(); iter != adjacent[u].end(); ++ iter) {
            int v = *iter;
            search(v);
        }
    }
}

struct Data {
    int ways;
    bool over;

    Data(int w = 0, bool o = false): ways(w), over(o) {
        if (ways >= 1000000000) {
            over = true;
            ways -= 1000000000;
        }
    }
};

Data operator +(const Data &a, const Data &b) {
    return Data(a.ways + b.ways, a.over | b.over);
}

Data ways[N];

void countWays(int u) {
    if (!visit[u]) {
        visit[u] = true;
        for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
            int v = to[iter];
            countWays(v);
            ways[u] = ways[u] + ways[v];
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d", a + i, b + i);
        a[i] --, b[i] --;
        to[i] = b[i];
        nextEdge[i] = firstEdge[a[i]];
        firstEdge[a[i]] = i;
    }
    labelCount = componentCount = 0;
    memset(label, -1, sizeof(label));
    for (int i = 0; i < n; ++ i) {
        dfs(i);
    }
    memset(visitCount, 0, sizeof(visitCount));
    for (int i = 0; i < m; ++ i) {
        if (componentID[a[i]] != componentID[b[i]]) {
            adjacent[componentID[a[i]]].push_back(componentID[b[i]]);
        }
    }
    memset(visit, 0, sizeof(visit));
    search(componentID[0]);
    for (int i = 0; i < componentCount; ++ i) {
        adjacent[i].clear();
    }
    for (int i = 0; i < m; ++ i) {
        if (componentID[a[i]] != componentID[b[i]]) {
            adjacent[componentID[b[i]]].push_back(componentID[a[i]]);
        }
    }
    memset(visit, 0, sizeof(visit));
    search(componentID[1]);
    for (int i = 0; i < componentCount; ++ i) {
        if (componentSize[i] > 1 && visitCount[i] == 2) {
            puts("inf");
            return 0;
        }
    }
    memset(visit, 0, sizeof(visit));
    ways[1] = Data(1, false);
    countWays(0); 
    Data result = ways[0];
    printf(result.over? "%09d\n": "%d\n", result.ways);
    return 0;
}
