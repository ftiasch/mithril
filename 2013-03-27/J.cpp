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

const int maxn = 101;
const int MOD = 1000000000;

int ways[maxn][2][maxn];

int n;
vector<int> adj[maxn];

void dfs(int p, int parent)
{
    FOR (q, adj[p]) {
        if (*q == parent) {
            continue;
        }
        dfs(*q, p);
    }
    ways[p][0][0] = 1;
    ways[p][1][1] = 1;
    FOR (q, adj[p]) {
        if (*q == parent) {
            continue;
        }
        static int oways[2][maxn];
        memcpy(oways, ways[p], sizeof(oways));
        memset(ways[p], 0, sizeof(ways[p]));
        for (int i = 0; i < 2; i++) {
            for (int j = i; j < maxn; j++) {
                if (oways[i][j] == 0) {
                    continue;
                }
                for (int u = 0; u < 2; u++) {
                    for (int v = u; j + v < maxn; v++) {
                        if (ways[*q][u][v] == 0) {
                            continue;
                        }
                        int cnt = (long long)oways[i][j] * ways[*q][u][v] % MOD;
                        (ways[p][i][j + v] += cnt) %= MOD;
                        if (i == 1 && u == 1) {
                            (ways[p][i][j + v - 1] += cnt) %= MOD;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        ai --;
        bi --;
        adj[ai].push_back(bi);
        adj[bi].push_back(ai);
    }
    dfs(0, -1);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", (ways[0][0][i] + ways[0][1][i]) % MOD);
    }
}
