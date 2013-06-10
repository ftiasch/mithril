#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 50000;

typedef unsigned long long ULL;

int n, m, degree[maxn];
vector<int> adj[maxn];
int rank[maxn];

inline bool byRank(const int &i, const int &j)
{
    return rank[i] < rank[j];
}

ULL vis[maxn][maxn / 64 + 1];

inline void insert(ULL vis[], int x)
{
    vis[x >> 6] |= 1ULL << (x & 63);
}

inline bool query(ULL vis[], int x)
{
    return vis[x >> 6] >> (x & 63) & 1;
}

inline void merge(ULL vis1[], ULL vis2[])
{
    for (int i = (n - 1) >> 6; i >= 0; -- i) {
        vis1[i] |= vis2[i];
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        -- a; -- b;
        adj[a].push_back(b);
        ++ degree[b];
    }
    vector<int> q;
    for (int i = 0; i < n; ++ i) {
        if (!degree[i]) {
            q.push_back(i);
        }
    }
    for (int i = 0; i < q.size(); ++ i) {
        int u = q[i];
        for (int j = 0; j < adj[u].size(); ++ j) {
            int v = adj[u][j];
            if ((-- degree[v]) == 0) {
                q.push_back(v);
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        rank[q[i]] = i;
    }
    for (int i = 0; i < n; ++ i) {
        sort(adj[i].begin(), adj[i].end(), byRank);
    }
    
    for (int i = 0; i < n; ++ i) {
        insert(vis[i], i);
    }
    
    for (int i = q.size() - 1; i >= 0; -- i) {
        int u = q[i];
        for (int j = 0; j < adj[u].size(); ++ j) {
            int v = adj[u][j];
            if (!query(vis[u], v)) {
                printf("%d %d\n", u + 1, v + 1);
                merge(vis[u], vis[v]);
            }
        }
    }
    return 0;
}

