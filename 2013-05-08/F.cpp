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

const int maxn = 50000;

int n;
vector<int> adj[maxn];
int parent[maxn];

double probSleep[maxn], probIn[maxn], probOut[maxn];
double probDown[maxn], probUp[maxn];

void dfsDown(int p)
{
    probDown[p] = probOut[p];
    FOR (it, adj[p]) {
        if (*it == parent[p]) {
            continue;
        }
        parent[*it] = p;
        dfsDown(*it);
        probDown[p] *= probDown[*it] + probSleep[*it];
    }
}

double ans = 0;

void dfsUp(int p)
{
    static int chCount;
    static int ch[maxn];
    static double prefix[maxn], suffix[maxn];
    chCount = 0;
    FOR (it, adj[p]) {
        if (*it == parent[p]) {
            continue;
        }
        ch[chCount ++] = *it;
    }
    prefix[0] = 1.0;
    for (int i = 0; i < chCount; i++) {
        prefix[i + 1] = prefix[i] * (probDown[ch[i]] + probSleep[ch[i]]);
    }
    suffix[chCount] = 1.0;
    for (int i = chCount - 1; i >= 0; i--) {
        suffix[i] = suffix[i + 1] * (probDown[ch[i]] + probSleep[ch[i]]);
    }
    ans += probOut[p] * probUp[p] * prefix[chCount];
    for (int i = 0; i < chCount; i++) {
        probUp[ch[i]] = probOut[p] * probUp[p] * prefix[i] * suffix[i + 1] + probSleep[p];
    }
    FOR (it, adj[p]) {
        if (*it == parent[p]) {
            continue;
        }
        dfsUp(*it);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int ai, bi, ci;
        scanf("%d%d%d", &ai, &bi, &ci);
        probSleep[i] = ai * 0.01;
        probIn[i] = bi * 0.01;
        probOut[i] = ci * 0.01;
    }
    for (int i = 1; i < n; i++) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        ai --, bi --;
        adj[ai].push_back(bi);
        adj[bi].push_back(ai);
    }
    memset(parent, -1, sizeof(parent));
    parent[0] = -2;
    dfsDown(0);
    ans = 0;
    probUp[0] = 1.0;
    dfsUp(0);
    printf("%.10f\n", ans);
}
