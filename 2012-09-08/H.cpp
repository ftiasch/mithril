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

const int maxn = 10000;

vector<int> chd[maxn];

int s[maxn], t[maxn];
int nodes;

void dfs(int p)
{
    s[p] = nodes ++;
    for (int i = 0; i < chd[p].size(); i++) {
        dfs(chd[p][i]);
    }
    t[p] = nodes;
}

long long dist[maxn + 1];
bool inQ[maxn + 1];
int times[maxn + 1];

struct Edge {
    int dest, cost, next;
};

Edge edge[maxn * 10 + 100];
int edges;

int firstEdge[maxn + 1];

inline void addEdge(int ai, int bi, int ci)
{
    edge[edges].dest = bi;
    edge[edges].cost = ci;
    edge[edges].next = firstEdge[ai];
    firstEdge[ai] = edges ++;
}

int n, m;

int Q[1 << 16];
unsigned short head, tail;

int main()
{
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            chd[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int fi;
            scanf("%d", &fi);
            fi --;
            chd[fi].push_back(i);
        }
        nodes = 0;
        dfs(0);
        head = tail = 0;
        for (int i = 0; i <= n; i++) {
            Q[tail++] = i;
            inQ[i] = true;
            dist[i] = i;
            times[i] = 0;
        }
        memset(firstEdge, -1, sizeof(firstEdge));
        edges = 0;
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            int ai, ci;
            static char bi[10];
            scanf("%d%s%d", &ai, bi, &ci);
            ai --;
            if (*bi == '>') {
                addEdge(t[ai], s[ai], - ci - 1);
            } else if (*bi == '=') {
                addEdge(t[ai], s[ai], - ci);
                addEdge(s[ai], t[ai], + ci);
            } else {
                addEdge(s[ai], t[ai], + ci - 1);
            }
        }
        for (int i = 0; i < n; i++) {
            addEdge(i + 1, i, -1);
        }
        long long minSum = 0;
        for (int i = 0; i <= n; i++) {
            int minv = 0;
            for (int e = firstEdge[i]; ~e; e = edge[e].next) {
                minv = min(minv, edge[e].cost);
            }
            minSum += minv;
        }
        bool valid = true;
        while (head != tail && valid) {
            if (dist[Q[head]] > dist[Q[tail - 1]]) {
                swap(Q[head], Q[tail - 1]);
            }
            int p = Q[head ++];
            inQ[p] = false;
            for (int e = firstEdge[p]; ~e; e = edge[e].next) {
                int q = edge[e].dest;
                long long nd = dist[p] + edge[e].cost;
                if (dist[q] > nd) {
                    dist[q] = nd;
                    if (dist[q] < minSum) {
                        valid = false;
                        break;
                    }
                    if (!inQ[q]) {
                        if (++times[q] >= n || times[q] > 500) {
                            valid = false;
                            break;
                        }
                        inQ[q] = true;
                        Q[tail++] = q;
                    }
                }
            }
        }
        puts(valid ? "True" : "Lie");
    }
}
