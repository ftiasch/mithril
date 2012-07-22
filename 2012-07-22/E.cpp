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

struct Edge
{
    int from, dest;

    int s1, s2, t1, t2;

    int id;

    bool operator<(const Edge &o) const {
        return s1 < o.s1;
    }

    int getCost() const {
        return (s2 - s1) + (t2 - t1);
    }
};

const int maxn = 50000;
const int maxm = 100002;

vector<Edge> adj[maxn];
vector<int> adjS1[maxn];
int edgeFrom[maxm], edgeNum[maxm];

int n, m;
int target, startBonus, targetTime;

bool cmp(int a, int b)
{
    return adjS1[edgeFrom[a]][edgeNum[a]] < adjS1[edgeFrom[b]][edgeNum[b]]
       || (adjS1[edgeFrom[a]][edgeNum[a]] == adjS1[edgeFrom[b]][edgeNum[b]]
       && edgeNum[a] < edgeNum[b]);
}

int dist[maxm];
int perm[maxm];
int permR[maxm];

int main()
{
    int cas = 0;
    while (scanf("%d%d%d", &n, &m, &startBonus) == 3 && n) {
        scanf("%d%d", &target, &targetTime);
        target --;
        for (int i = 0; i < n; i++)
            adj[i].clear();
        int s = m, t = m + 1;
        if (true) {
            Edge edge;
            edge.id = s;
            edge.from = edge.dest = 0;
            edge.s1 = edge.s2 = edge.t1 = edge.t2 = 0;
            adj[edge.from].push_back(edge);
        }
        for (int i = 0; i < m; i++) {
            Edge edge;
            edge.id = i;
            scanf("%d%d%d%d%d%d", &edge.from, &edge.dest, &edge.s1, &edge.s2, &edge.t1, &edge.t2);
            edge.from --;
            edge.dest --;
            adj[edge.from].push_back(edge);
        }
        if (true) {
            Edge edge;
            edge.id = t;
            edge.from = edge.dest = target;
            edge.s1 = edge.s2 = edge.t1 = edge.t2 = targetTime;
            adj[edge.from].push_back(edge);
        }
        m += 2;
        for (int i = 0; i < n; i++) {
            stable_sort(adj[i].begin(), adj[i].end());
            adjS1[i].resize(adj[i].size());
            for (int j = 0; j < adj[i].size(); j++) {
                adjS1[i][j] = adj[i][j].s1;
                edgeFrom[adj[i][j].id] = i;
                edgeNum[adj[i][j].id] = j;
            }
        }
        for (int i = 0; i < m; i++) {
            perm[i] = i;
        }
        sort(perm, perm + m, cmp);
        for (int i = 0; i < m; i++) {
            permR[perm[i]] = i;
        }
        memset(dist, -1, sizeof(dist));
        dist[s] = startBonus;
        for (int i = 0; i < m; i++) {
            int p = perm[i];
            if (dist[p] < 0)
                continue;
            #define UPDATE(A, DIST) { \
                if (dist[A] < (DIST)) { \
                    dist[A] = (DIST); \
                } \
            }
            int px = edgeFrom[p], py = edgeNum[p];
            const Edge &edge = adj[px][py];
            if (dist[p] >= edge.getCost()) {
                int qx = edge.dest;
                int qy = lower_bound(adjS1[qx].begin(), adjS1[qx].end(), edge.t2) - adjS1[qx].begin();
                if (qy < adj[qx].size()) {
                    int q = adj[qx][qy].id;
                    assert(permR[p] <= permR[q]);
                    int waitTime = adjS1[qx][qy] - edge.t2;
                    UPDATE(q, dist[p] - edge.getCost() - waitTime);
                }
            }
            if (py + 1 < adj[px].size()) {
                int cost = adjS1[px][py + 1] - adjS1[px][py];
                if (dist[p] >= cost) {
                    int q = adj[px][py + 1].id;
                    assert(permR[p] <= permR[q]);
                    UPDATE(q, dist[p] - cost);
                }
            }
        }
        printf("Plant %d: %d\n", ++cas, max(0, dist[t]));
    }
}
