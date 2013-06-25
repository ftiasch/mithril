#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int maxn = 400;

int parent[maxn];

int findRoot(int p)
{
    return parent[p] < 0 ? p : parent[p] = findRoot(parent[p]);
}

bool mergeComp(int a, int b)
{
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) {
        return false;
    }
    parent[a] = b;
    return true;
}

int n, m;

int x[maxn], y[maxn], z[maxn], holes[maxn];

double sqr(double a)
{
    return a * a;
}

double getDist(int a, int b)
{
    return sqrt(sqr(x[a] - x[b]) + sqr(y[a] - y[b]) + sqr(z[a] - z[b]));
}

double cost[maxn][maxn], dist[maxn];
bool visit[maxn];
int holeSum[maxn];

int main()
{
    int cas = 0;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d", x + i, y + i, z + i, holes + i);
        }
        vector<pair<int,pair<int,int> > > edges;
        for (int i = 0; i < m; i++) {
            int ai, bi;
            scanf("%d%d", &ai, &bi);
            ai --, bi --;
            int ci = max(z[ai], z[bi]);
            edges.push_back(make_pair(ci, make_pair(ai, bi)));
        }
        edges.push_back(make_pair(z[n - 1], make_pair(n - 1, n - 1)));
        edges.push_back(make_pair(z[0], make_pair(0, 0)));
        memset(parent, -1, sizeof(parent));
        sort(edges.begin(), edges.end());
        double minCost = 1e100;
        for (int ptr = 0; ptr < edges.size();) {
            int nptr = ptr;
            while (nptr < edges.size() && edges[nptr].first == edges[ptr].first) {
                nptr ++;
            }
            for (int i = ptr; i < nptr; i++) {
                mergeComp(edges[i].second.first, edges[i].second.second);
            }
            if (edges[ptr].first >= max(z[0], z[n - 1])) {
                int sumHoles = 0;
                for (int i = 0; i < n; i++) {
                    if (findRoot(i) == findRoot(0) || findRoot(i) == findRoot(n - 1)) {
                        sumHoles += holes[i];
                    }
                }
                if (findRoot(0) == findRoot(n - 1)) {
                    minCost = min(minCost, sumHoles * 0.5);
                } else {
                    for (int i = 0; i < n; ++ i) {
                        for (int j = 0; j < n; ++ j) {
                            cost[i][j] = 1e100;
                        }
                    }
                    memset(holeSum, 0, sizeof(holeSum));
                    for (int i = 0; i < n; ++ i) {
                        holeSum[findRoot(i)] += holes[i];
                    }
                    for (int i = 0; i < n; ++ i) {
                        for (int j = 0; j < n; ++ j) {
                            if (findRoot(i) != findRoot(j) && holes[i] >= 1 && holes[j] >= 1) {
                                int u = findRoot(i);
                                int v = findRoot(j);
                                if (u == findRoot(0) || holeSum[u] > 1) {
                                    if (v == findRoot(n - 1) || holeSum[v] > 1) {
                                        cost[u][v] = std::min(cost[u][v], getDist(i, j) - 1.0);
                                    }
                                }
                            }
                        }
                    }
                    memset(visit, 0, sizeof(visit));
                    for (int i = 0; i < n; ++ i) {
                        dist[i] = 1e100;
                    }
                    dist[findRoot(0)] = holeSum[findRoot(0)] * 0.5;
                    while (true) {
                        int i = -1;
                        for (int j = 0; j < n; ++ j) {
                            if (findRoot(j) == j && !visit[j] && (i == -1 || dist[j] < dist[i])) {
                                i = j;
                            }
                        }
                        if (i == -1) {
                            break;
                        }
                        visit[i] = true;
                        for (int j = 0; j < n; ++ j) {
                            if (findRoot(j) == j && dist[i] + cost[i][j] + holeSum[j] * 0.5 < dist[j]) {
                                dist[j] = dist[i] + cost[i][j] + holeSum[j] * 0.5;
                            }
                        }
                    }
                    minCost = std::min(minCost, dist[findRoot(n - 1)]);
                }
            }
            ptr = nptr;
        }
        if (minCost > 1e50) {
            printf("Case %d: impossible\n", ++cas);
        } else {
            printf("Case %d: %.4f\n", ++cas, minCost);
        }
    }
}
