#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

const int N = 200 << 1;

int n, dislike[N], order[N][N], like[N][2];

bool relation[N][N], graph[N][N];

int dfsCount, dfn[N], low[N], sccCount, scc[N];
vector <int> stack;

void dfs(int i) {
    if (dfn[i] == -1) {
        int ret = dfn[i] = low[i] = dfsCount ++;
        stack.push_back(i);
        for (int j = 0; j < n << 1; ++ j) {
            if (graph[i][j]) {
                dfs(j);
                ret = min(ret, low[j]);
            }
        }
        low[i] = ret;
        if (dfn[i] == low[i]) {
            while (true) {
                int u = stack.back();
                stack.pop_back();
                low[u] = INT_MAX;
                scc[u] = sccCount;
                if (u == i) {
                    break;
                }
            }
            sccCount ++;
        }
    }
}

bool check(int limit) {
    memset(relation, 0, sizeof(relation));
    for (int i = 0; i < n; ++ i) {
        for (int k = 0; k < limit; ++ k) {
            int j = order[i][k];
            relation[i][j] = true;
        }
    }
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < n << 1; ++ i) {
        for (int j = 0; j < n << 1; ++ j) {
            if ((i >> 1) != (j >> 1) && !(relation[i >> 1][j >> 1] && relation[j >> 1][i >> 1]) && like[i >> 1][i & 1] == like[j >> 1][j & 1]) {
                graph[i][j ^ 1] = true;
            }
        }
    }
    dfsCount = 0;
    memset(dfn, -1, sizeof(dfn));
    sccCount = 0;
    for (int i = 0; i < n << 1; ++ i) {
        dfs(i);
    }
    for (int i = 0; i < n; ++ i) {
        if (scc[i << 1] == scc[(i << 1) | 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", dislike + i);
        for (int j = 0; j < n - 1; ++ j) {
            scanf("%d", &order[i][j]);
            order[i][j] --;
        }
    }
    for (int i = 0; i < n; ++ i) {
        int total = 0;
        for (int j = 0; j < 3; ++ j) {
            if (j != dislike[i]) {
                like[i][total ++] = j;
            }
        }
    }
    int low = 0;
    int high = n - 1;
    while (low < high) {
        int middle = low + high >> 1;
        if (check(middle)) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }
    printf("%d\n", high);
    return 0;
}
