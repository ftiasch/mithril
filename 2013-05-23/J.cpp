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

int n, B;
int parent[maxn];
vector<int> adj[maxn];

pair<int,int> down[maxn], up[maxn], ans[maxn];

pair<int,int> calc(const map<int,int> &M)
{
    if (M.empty()) {
        return make_pair(0, 1);
    }
    if (M.rbegin()->second + 1 <= B) {
        return make_pair(M.rbegin()->first, M.rbegin()->second + 1);
    } else {
        return make_pair(M.rbegin()->first + 1, 1);
    }
}

void add(map<int,int> &M, const pair<int,int> &v)
{
    M[v.first] += v.second;
}

void del(map<int,int> &M, const pair<int,int> &v)
{
    if ((M[v.first] -= v.second) == 0) {
        M.erase(v.first);
    }
}

int main()
{
    int cas = 0;
    while (scanf("%d%d", &n, &B) == 2 && n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 1; i < n; i++) {
            scanf("%d", parent + i);
            parent[i] --;
            adj[parent[i]].push_back(i);
        }
        for (int p = n - 1; p >= 0; p--) {
            map<int,int> M;
            FOR (it, adj[p]) {
                add(M, down[*it]);
            }
            down[p] = calc(M);
        }
        for (int p = 0; p < n; p++) {
            map<int,int> M;
            if (p > 0) {
                add(M, up[p]);
            }
            FOR (it, adj[p]) {
                add(M, down[*it]);
            }
            ans[p] = calc(M);
            FOR (it, adj[p]) {
                del(M, down[*it]);
                up[*it] = calc(M);
                add(M, down[*it]);
            }
                
        }
        printf("Case %d:\n", ++cas);
        for (int i = 0; i < n; i++) {
            printf("%d\n", ans[i].first + 1);
        }
    }
}
