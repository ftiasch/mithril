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

const int maxn = 100;

int n, T;
int treasure[maxn];

vector<pair<int,int> > adj[maxn];

int src, dest;
bool containDest[maxn];

int opt[maxn][512];

void dfs(int p, int pa = -1)
{
    containDest[p] = p == dest;
    opt[p][0] = treasure[p];
    for (int i = 0; i < adj[p].size(); i++) {
        int q = adj[p][i].first;
        if (q == pa) {
            continue;
        }
        dfs(q, p);
        if (containDest[q]) {
            containDest[p] = true;
            opt[p][0] = -1;
            for (int t = 0; t + adj[p][i].second <= T; t++) {
                if (opt[q][t] >= 0) {
                    opt[p][t + adj[p][i].second] = opt[q][t] + treasure[p];
                }
            }
        }
    }
    for (int i = 0; i < adj[p].size(); i++) {
        int q = adj[p][i].first;
        if (q == pa) {
            continue;
        }
        if (containDest[q]) {
            continue;
        }
        int cost = adj[p][i].second;
        for (int t = T; t >= 0; t --) {
            for (int ct = 0; ct + 2 * cost <= t; ct ++) {
                int opt1 = opt[p][t - ct - 2 * cost];
                int opt2 = opt[q][ct];
                if (opt1 < 0 || opt2 < 0) {
                    continue;
                }
                opt[p][t] = max(opt[p][t], opt1 + opt2);
            }
        }
    }
}

int main()
{
    while (scanf("%d%d", &n, &T) == 2) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int ai, bi, ci;
            scanf("%d%d%d", &ai, &bi, &ci);
            ai --, bi --;
            adj[ai].push_back(make_pair(bi, ci));
            adj[bi].push_back(make_pair(ai, ci));
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", treasure + i);
        }
        src = 0, dest = n - 1;
        memset(opt, -1, sizeof(opt));
        dfs(src);
        int maxv = -1;
        for (int i = 0; i <= T; i++) {
            maxv = max(maxv, opt[src][i]);
        }
        if (maxv < 0) {
            puts("Human beings die in pursuit of wealth, and birds die in pursuit of food!");
        } else {
            printf("%d\n", maxv);
        }
    }
}
