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

const int maxn = (1000005 + 1000005) * 3 + 10;
const int maxN = 1000005;
const long long inf = 1000000000000000000LL;

int N, src, sink;
vector< pair<int, int> > row[maxN], col[maxN];
vector<int> selRow[maxN], selCol[maxN];
int rowId[maxN], colId[maxN];
int rowSel[maxN], colSel[maxN];
int rowPtr[maxN], colPtr[maxN];
vector< vector<int> > entryId;
vector< vector<int> > rec;
int recx[maxn], recy[maxn], threshold;

struct Edge
{
    int dest, cap, flow, cost;
    int nextEdge;

    Edge(int dest, int cap, int cost) : dest(dest), cap(cap), flow(0), cost(cost){}
};

vector<Edge> edge;
int firstEdge[maxn + 2];

void addEdge1(int ai, int bi, int cap, int cost)
{
    edge.push_back(Edge(bi, cap, cost));
    edge.back().nextEdge = firstEdge[ai];
    firstEdge[ai] = edge.size() - 1;
}

int addEdge(int ai, int bi, int cap, int cost)
{
    int ret = (int)edge.size();
    addEdge1(ai, bi, cap, cost);
    addEdge1(bi, ai, 0, -cost);
    return ret;
}

void addRow(int r)
{
    if (rowSel[r] != -1 || rowPtr[r] == row[r].size()) {
        return;
    }
    int x = r;
    int y = row[r][rowPtr[r]++].second;
    while (entryId[x][y] != -1 && rowPtr[r] < row[r].size()) {
        y = row[r][rowPtr[r]++].second;
    }
    if (entryId[x][y] == -1) {
        recx[N] = x;
        recy[N] = y;
        addEdge(N, sink, 1, rec[x][y]);
        if (rowId[x] != -1) {
            addEdge(rowId[x], N, 1, 0);
        }
        if (colId[y] != -1) {
            addEdge(colId[y], N, 1, 0);
        }
        entryId[x][y] = N ++;
    }
}

void addCol(int c)
{
    if (colSel[c] != -1 || colPtr[c] == col[c].size()) {
        return;
    }
    int x = col[c][colPtr[c]++].first;
    int y = c;
    while (entryId[x][y] != -1 && colPtr[c] < col[c].size()) {
        x = col[c][colPtr[c]++].first;
    }
    if (entryId[x][y] == -1) {
        recx[N] = x;
        recy[N] = y;
        addEdge(N, sink, 1, rec[x][y]);
        if (rowId[x] != -1) {
            addEdge(rowId[x], N, 1, 0);
        }
        if (colId[y] != -1) {
            addEdge(colId[y], N, 1, 0);
        }
        entryId[x][y] = N ++;
    }
}

long long costSum;

bool spfa()
{
    vector<long long> dist(N, inf);
    vector<int> prev(N, -1);
    priority_queue< pair<long long, int> > Q;
    vector<bool> inQ(N, false);
    dist[src] = 0;
    Q.push(make_pair(0, src));
    while (!Q.empty()) {
        pair<int, int> cur = Q.top();
        int p = cur.second;
        Q.pop();
        if (dist[p] != -cur.first) {
            continue;
        }
        for (int e = firstEdge[p]; e >= 0; e = edge[e].nextEdge) {
            int q = edge[e].dest;
            if (edge[e].flow == edge[e].cap) {
                continue;
            }
            if (dist[q] > dist[p] + edge[e].cost) {
                dist[q] = dist[p] + edge[e].cost;
                prev[q] = e;
                Q.push(make_pair(-dist[q], q));
            }
        }
    }
    if (dist[sink] == inf) {
        return false;
    }
    costSum += dist[sink];
    int ptr = sink;
    while (ptr != src) {
        int e = prev[ptr];
        edge[e].flow ++;
        edge[e^1].flow --;
        int last = ptr;
        ptr = edge[e^1].dest;
        if (last == sink && ptr >= threshold) {
            addRow(recx[ptr]);
            addCol(recy[ptr]);
        }
    }
    
    return true;
}

inline bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return rec[a.first][a.second] < rec[b.first][b.second];
}

int main()
{
    memset(firstEdge, -1, sizeof(firstEdge));
    memset(rowId, -1, sizeof(rowId));
    memset(colId, -1, sizeof(colId));
    int n, m;
    scanf("%d%d", &n, &m);
    rec.resize(n);
    entryId.resize(n);
    for (int i = 0; i < n; ++ i) {
        rec[i].resize(m);
        entryId[i].resize(m);
        for (int j = 0; j < m; ++ j) {
            entryId[i][j] = -1;
            scanf("%d", &rec[i][j]);
            row[i].push_back(make_pair(i,j));
            col[j].push_back(make_pair(i,j));
        }
    }
    for (int i = 0; i < n; ++ i) {
        sort(row[i].begin(), row[i].end(), cmp);
        rowSel[i] = row[i][0].second;
    }
    for (int i = 0; i < m; ++ i) {
        sort(col[i].begin(), col[i].end(), cmp);
        colSel[i] = col[i][0].first;
    }
    
    for (int i = 0; i < n; ++ i) {
        int j = rowSel[i];
        if (colSel[j] == i) {
            rowSel[i] = colSel[j] = -1;
            rowPtr[i] = colPtr[j] = 0;
        }
    }
    
    for (int i = 0; i < m; ++ i) {
        if (colSel[i] != -1) {
            selRow[colSel[i]].push_back(i);
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (rowSel[i] != -1) {
            selCol[rowSel[i]].push_back(i);
        }
    }
    
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < n; ++ i) {
            if (rowSel[i] == -1) {
                for (int j = 0; j < selRow[i].size(); ++ j) {
                    int u = selRow[i][j];
                    if (colSel[u] != -1) {
                        colSel[u] = -1;
                        change=true;
                    }
                }
            }
        }
        for (int i = 0; i < m; ++ i) {
            if (colSel[i] == -1) {
                for (int j = 0; j < selCol[i].size(); ++ j) {
                    int u = selCol[i][j];
                    if (rowSel[u] != -1) {
                        rowSel[u] = -1;
                        change=true;
                    }
                }
            }
        }
    }
        
    costSum = 0;
    
    src = 0;
    sink = 1;
    N = 2;
    
    for (int i = 0; i < n; ++ i) {
        if (rowSel[i] == -1) {
            rowId[i] = N ++;
            addEdge(src, rowId[i], 1, 0);
            continue;
        }
        if (entryId[i][rowSel[i]] == -1) {
            entryId[i][rowSel[i]] = -2;
            costSum += rec[i][rowSel[i]];
        }
    }
    for (int i = 0; i < m; ++ i) {
        if (colSel[i] == -1) {
            colId[i] = N ++;
            addEdge(src, colId[i], 1, 0);
            continue;
        }
        if (entryId[colSel[i]][i] == -1) {
            entryId[colSel[i]][i] = -2;
            costSum += rec[colSel[i]][i];
        }
    }
    
//    printf("costSum = %lld\n",costSum);
    
    threshold = N;
    
    for (int i = 0; i < n; ++ i) {
        if (rowSel[i] == -1) {
            addRow(i);
        }
    }
    for (int i = 0; i < m; ++ i) {
        if (colSel[i] == -1) {
            addCol(i);
        }
    }
    
    while (spfa()) {
        //printf("%lld\n", costSum);
    }
    
    cout << costSum << endl;
    
    return 0;
}

