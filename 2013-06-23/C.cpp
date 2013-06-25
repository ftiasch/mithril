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

const int maxn = 20;
const int inf = 1000000000;

int cntbit[1 << maxn];

int n, m;
int dist[maxn][maxn];
int opt[2][maxn][1 << 18];

void checkmin(int &a, int v)
{
    if (a < 0 || a > v) {
        a = v;
    }
}

int main()
{
    cntbit[0] = 0;
    for (int i = 1; i < 1 << maxn; i++) {
        cntbit[i] = cntbit[i >> 1] + (i & 1);
    }
    int cas = 0;
    while (scanf("%d%d", &n, &m) == 2) {
        memset(dist, -1, sizeof(dist));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = i == j ? 0 : inf;
            }
        }
        for (int i = 0; i < m; i++) {
            int ai, bi, ci;
            scanf("%d%d%d", &ai, &bi, &ci);
            if (dist[ai][bi] > ci) {
                dist[ai][bi] = ci;
                dist[bi][ai] = ci;
            }
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        if (n == 3) {
            printf("Case %d: %d\n", ++cas, (dist[0][1] + dist[1][2]) * 2);
            continue;
        }
        memset(opt, -1, sizeof(opt));
        for (int i = 1; i < n - 1; i++) {
            opt[0][i - 1][1 << i - 1] = dist[0][i];
            opt[1][i - 1][1 << i - 1] = dist[n - 1][i];
        }
        int left = (n - 2) / 2, right = n - 2 - left;
        for (int mask = 1; mask < 1 << n - 2; mask++) {
            if (cntbit[mask] < right) {
                for (int pos = 0; pos < n - 2; pos ++) {
                    if (~mask >> pos & 1) {
                        continue;
                    }
                    for (int side = 0; side < 2; side ++) {
                        if (opt[side][pos][mask] < 0) {
                            continue;
                        }
                        for (int z = 0; z < n - 2; z++) {
                            if (~mask >> z & 1) {
                                checkmin(opt[side][z][mask | 1 << z], opt[side][pos][mask] + dist[pos + 1][z + 1]);
                            }
                        }
                    }
                }
            }
        }
        int ans = -1;
        for (int lmsk = 0; lmsk < 1 << n - 2; lmsk++) {
            if (cntbit[lmsk] == left) {
                int rmsk = (1 << n - 2) - 1 ^ lmsk;
                int turn1 = -1, turn2 = -1;
                for (int i = 0; i < n - 2; i++) {
                    if (lmsk >> i & 1) {
                        for (int j = 0; j < n - 2; j++) {
                            if (rmsk >> j & 1) {
                                int val1 = opt[0][i][lmsk];
                                int val2 = opt[1][j][rmsk];
                                if (val1 >= 0 && val2 >= 0) {
                                    checkmin(turn1, val1 + dist[i + 1][j + 1] + val2);
                                }
                                val1 = opt[1][i][lmsk];
                                val2 = opt[0][j][rmsk];
                                if (val1 >= 0 && val2 >= 0) {
                                    checkmin(turn2, val1 + dist[i + 1][j + 1] + val2);
                                }
                            }
                        }
                    }
                }
                if (turn1 >= 0 && turn2 >= 0) {
                    checkmin(ans, turn1 + turn2);
                }
            }
        }
        printf("Case %d: %d\n", ++cas, ans);
    }
}
