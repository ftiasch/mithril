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

const int maxn = 512;
const int inf = 1000000000;

bool readInput(int &n, char *str, vector<int> *adj)
{
    int m;
    if (scanf("%d%d", &n, &m) != 2) {
        return false;
    }
    scanf("%s", str);
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        ai --, bi --;
        adj[ai].push_back(bi);
    }
    return true;
}

int n1, n2;
char str1[maxn], str2[maxn];
vector<int> adj1[maxn], adj2[maxn];

vector<int> adj[maxn * maxn * 2];
int indeg[maxn * maxn * 2];

int opt[maxn * maxn * 2];
int next[maxn * maxn * 2];

bool check(int p)
{
    return p % 2 == 1 || str1[p / 2 / n2] == str2[p / 2 % n2];
}

int main()
{
    int cas = 0;
    while (readInput(n1, str1, adj1) && readInput(n2, str2, adj2)) {
        int N = n1 * n2 * 2;
        for (int i = 0; i < N; i++) {
            adj[i].clear();
            indeg[i] = 0;
        }
#define ID(a, b, c) (((a) * n2 + (b)) * 2 + (c))
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                if (str1[i] == str2[j]) {
                    FOR (it, adj1[i]) {
                        adj[ID(i, j, 0)].push_back(ID(*it, j, 1));
                    }
                }
                FOR (it, adj2[j]) {
                    if (str1[i] == str2[*it]) {
                        adj[ID(i, j, 1)].push_back(ID(i, *it, 0));
                    }
                }
            }
        }
        for (int i = 0; i < N; i++) {
            FOR (it, adj[i]) {
                indeg[*it] ++;
            }
        }
        vector<int> order;
        for (int i = 0; i < N; i++) {
            if (indeg[i] == 0) {
                order.push_back(i);
            }
        }
        for (int i = 0; i < order.size(); i++) {
            int p = order[i];
            FOR (it, adj[p]) {
                if (--indeg[*it] == 0) {
                    order.push_back(*it);
                }
            }
        }
        bool found = false;
        for (int i = 0; i < N; i ++) {
            if (indeg[i] > 0) {
                opt[i] = inf;
                next[i] = -1;
                if (~i & 1 && check(i)) {
                    found = true;
                }
            }
        }
        reverse(order.begin(), order.end());
        int maxi = -1;
        FOR (it, order) {
            int p = *it;
            opt[p] = 0;
            next[p] = -1;
            FOR (jt, adj[p]) {
                int q = *jt;
                if (opt[p] < opt[q]) {
                    opt[p] = opt[q];
                    next[p] = q;
                }
            }
            if (~p & 1) {
                opt[p] ++;
                if (check(p) && (maxi < 0 || opt[p] > opt[maxi])) {
                    maxi = p;
                }
            }
        }
        if (found || maxi >= 0 && opt[maxi] >= inf) {
            printf("Case %d: %d\n", ++cas, -1);
        } else if (maxi < 0) {
            printf("Case %d: %d\n", ++cas, 0);
        } else {
            printf("Case %d: %d\n", ++cas, opt[maxi]);
            int ptr = maxi;
            vector<pair<int,int> > ans;
            while (ptr >= 0) {
                if (~ptr & 1) {
                    ans.push_back(make_pair(ptr / 2 / n2, ptr / 2 % n2));
                }
                ptr = next[ptr];
            }
            for (int i = 0; i < ans.size(); i++) {
                if (i) {
                    putchar(' ');
                }
                printf("%d", ans[i].first + 1);
            }
            puts("");
            for (int i = 0; i < ans.size(); i++) {
                if (i) {
                    putchar(' ');
                }
                printf("%d", ans[i].second + 1);
            }
            puts("");
        }
    }
}
