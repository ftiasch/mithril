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

const int maxn = 750;

int parent[maxn];

int findRoot(int p)
{
    return parent[p] >= 0 ? parent[p] = findRoot(parent[p]) : p;
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
int x[maxn], y[maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", x + i, y + i);
    }
    memset(parent, -1, sizeof(parent));
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        ai --, bi --;
        mergeComp(ai, bi);
    }
    vector<pair<int,pair<int,int> > > edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int dist = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
            edges.push_back(make_pair(dist, make_pair(j, i)));
        }
    }
    sort(edges.begin(), edges.end());
    FOR (it, edges) {
        if (mergeComp(it->second.first, it->second.second)) {
            printf("%d %d\n", it->second.first + 1, it->second.second + 1);
        }
    }
}
