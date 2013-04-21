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

const int maxn = 111111;

int n, m;
vector<int> adj[maxn];
int maxdep[maxn];

bool visit[maxn];
vector<int>::iterator iters[maxn];

void dfs(int p) 
{
    visit[p] = true;
    maxdep[p] = 0;
    vector<int>::iterator &it = iters[p]; 
    for (it = adj[p].begin(); it != adj[p].end(); ++ it) {
        if (visit[*it]) {
            continue;
        }
        dfs(*it);
        maxdep[p] = max(maxdep[p], maxdep[*it] + 1);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int xi, yi;
        scanf("%d%d", &xi, &yi);
        xi --, yi --;
        adj[xi].push_back(yi);
        adj[yi].push_back(xi);
    }
    memset(visit, 0, sizeof(visit));
    dfs(0);
    vector<int> cnt(n, 0);
    for (int i = 1; i < n; i++) {
        cnt[maxdep[i]] ++;
    }
    int ret = 0;
    for (int i = 0; i < n; i++) {
        ret += min(cnt[i], m);
    }
    printf("%d\n", ret);
}
