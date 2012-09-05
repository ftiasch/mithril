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
const long long inf = 1LL << 60;

int base[2][maxn];
int delta[2][maxn];

vector<int> adj[maxn];

long long opt[maxn][2][maxn * 2];

int n, m;

long long tmp[maxn * 2];
long long ntmp[maxn * 2];

vector<int> deltas;

void dfs(int p, int parent)
{
    for (int i = 0; i < adj[p].size(); i++) {
        int q = adj[p][i];
        if (q == parent) {
            continue;
        }
        dfs(q, p);
    }
    for (int color = 0; color < 2; color ++) {
        for (int j = 0; j < m; j++) {
            tmp[j] = inf;
        }
        tmp[delta[color][p]] = base[color][p];
        for (int i = 0; i < adj[p].size(); i++) {
            int q = adj[p][i];
            if (q == parent) {
                continue;
            }
            for (int j = 0; j < m; j++) {
                ntmp[j] = inf;
            }
            for (int ccolor = 0; ccolor < 2; ccolor++) {
                for (int minv = 0; minv < m; minv++) {
                    long long &ref = opt[q][ccolor][minv];
                    if (ref == inf) {
                        continue;
                    }
                    for (int j = 0; j < m; j++) {
                        if (tmp[j] == inf) {
                            continue;
                        }
                        if (ccolor == color) {
                            int nminv = min(minv, j);
                            ntmp[nminv] = min(ntmp[nminv], tmp[j] + ref);
                        } else {
                            ntmp[j] = min(ntmp[j], tmp[j] + ref + deltas[minv]);
                        }
                    }
                }
            }
            for (int j = 0; j < m; j++) {
                tmp[j] = ntmp[j];
            }
        }
        for (int j = 0; j < m; j++) {
            opt[p][color][j] = tmp[j];
        }
    }
}

int main()
{
    while (scanf("%d", &n) == 1) {
        deltas.clear();
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                int aij;
                scanf("%d", &aij);
                int half = aij / 2;
                base[i][j] = half;
                delta[i][j] = aij - half;
                deltas.push_back(delta[i][j]);
            }
        }
        sort(deltas.begin(), deltas.end());
        deltas.erase(unique(deltas.begin(), deltas.end()), deltas.end());
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                delta[i][j] = lower_bound(deltas.begin(), deltas.end(), delta[i][j]) - deltas.begin();
            }
        }
        m = deltas.size();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int ai, bi;
            scanf("%d%d", &ai, &bi);
            ai --, bi --;
            adj[ai].push_back(bi);
            adj[bi].push_back(ai);
        }
        dfs(0, -1);
        long long ans = inf;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < m; j++) {
                ans = min(ans, deltas[j] + opt[0][i][j]);
            }
        }
        cout << ans << endl;
    }
}
