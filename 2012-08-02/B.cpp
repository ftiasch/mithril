#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 400000;

int n, x[N], y[N], edgeCount, firstEdge[N], to[N], nextEdge[N], degree[N];
bool used[N], color[N], curColor, xCount[N], yCount[N];
vector <int> xValues, yValues;

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void dfs(int u) {
    for (int &iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        if (!used[iter >> 1]) {
            used[iter >> 1] = true;
            degree[u] --;
            degree[to[iter]] --;
            int backupIter = iter >> 1;
            dfs(to[iter]);
            //assert(backupIter == (iter >> 1));
            color[backupIter] = (curColor ^= 1);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", x + i, y + i);
        xValues.push_back(x[i]);
        yValues.push_back(y[i]);
    }
    sort(xValues.begin(), xValues.end());
    xValues.erase(unique(xValues.begin(), xValues.end()), xValues.end());
    sort(yValues.begin(), yValues.end());
    yValues.erase(unique(yValues.begin(), yValues.end()), yValues.end());
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < n; ++ i) {
        int a = lower_bound(xValues.begin(), xValues.end(), x[i]) - xValues.begin();
        int b = lower_bound(yValues.begin(), yValues.end(), y[i]) - yValues.begin() + xValues.size();
        addEdge(a, b);
        addEdge(b, a);
        degree[a] ++;
        degree[b] ++;
    }
    int v = xValues.size() + yValues.size();
    curColor = 0;
    memset(used, 0, sizeof(used));
    for (int i = 0; i < v; ++ i) {
        if (degree[i] & 1) {
            int u = i;
            while (degree[u] & 1) {
                int &iter = firstEdge[u];
                while (used[iter >> 1]) {
                    iter = nextEdge[iter];
                }
                used[iter >> 1] = true;
                color[iter >> 1] = (curColor ^= 1);
                degree[u] --;
                degree[to[iter]] --;
                u = to[iter];
            }
        }
    }
    for (int i = 0; i < v; ++ i) {
        dfs(i);
    }
    memset(xCount, 0, sizeof(xCount));
    memset(yCount, 0, sizeof(yCount));
    for (int i = 0; i < edgeCount; i += 2) {
        int delta = color[i >> 1]? 1: -1;
        xCount[lower_bound(xValues.begin(), xValues.end(), x[i >> 1]) - xValues.begin()] += delta;
        yCount[lower_bound(yValues.begin(), yValues.end(), y[i >> 1]) - yValues.begin()] += delta;
        assert(used[i >> 1]);
        puts(color[i >> 1]? "ROSE": "CARNATION");
    }
    for (int i = 0; i < xValues.size(); ++ i) {
        assert(abs(xCount[i]) <= 1);
    }
    for (int i = 0; i < yValues.size(); ++ i) {
        assert(abs(yCount[i]) <= 1);
    }
    return 0;
}
