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

const int inf = 1000000000;

const int maxn = 100;
const int maxm = 15;

int n, m, startingBonus, h;

int chosen[maxm];
int paid[maxm], gain[maxm];

int minCost[maxn][maxn];

int maxBonus[maxm][1 << maxm];

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d%d", &n, &m, &startingBonus);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                minCost[i][j] = i == j ? 0 : inf;
            }
        }
        for (int i = 0; i < m; i++) {
            int ai, bi, ci;
            scanf("%d%d%d", &ai, &bi, &ci);
            ai --, bi --;
            minCost[ai][bi] = min(minCost[ai][bi], ci);
            minCost[bi][ai] = minCost[ai][bi];
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    minCost[i][j] = min(minCost[i][j], minCost[i][k] + minCost[k][j]);
                }
            }
        }
        scanf("%d", &h);
        for (int i = 0; i < h; i++) {
            scanf("%d%d%d", chosen + i, gain + i, paid + i);
            chosen[i] --;
        }
        for (int i = 0; i < h; i++) {
            memset(maxBonus[i], -1, sizeof(maxBonus[i]) << h);
            int &ref = maxBonus[i][1 << i];
            ref = startingBonus - minCost[0][chosen[i]];
            ref -= paid[i];
            if (ref >= 0) {
                ref += gain[i];
            }
        }
        for (int mask = 1; mask < 1 << h; mask++) {
            for (int i = 0; i < h; i++) {
                if (maxBonus[i][mask] >= 0) {
                    for (int j = 0; j < h; j++) {
                        if (~mask >> j & 1) {
                            int ncost = maxBonus[i][mask] - minCost[chosen[i]][chosen[j]];
                            ncost -= paid[j];
                            if (ncost >= 0) {
                                ncost += gain[j];
                                maxBonus[j][mask | 1 << j] = max(maxBonus[j][mask | 1 << j], ncost);
                            }
                        }
                    }
                }
            }
        }
        bool found = false;
        for (int i = 0; i < h; i++) {
            if (maxBonus[i][(1 << h) - 1] - minCost[chosen[i]][0] >= 0) {
                found = true;
            }
        }
        puts(found ? "YES" : "NO");
    }
}
