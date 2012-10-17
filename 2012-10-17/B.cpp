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

const int maxs = 25;
const int maxl = 100000;

int n, len;
int scale[maxs];
int target;

int dist[maxs][maxl + 1];

int Q[maxs * (maxl + 1)][2], head, tail;

int main()
{
    freopen("cylinders.in", "r", stdin);
    freopen("cylinders.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", scale + i);
    }
    scanf("%d", &target);
    len = scale[n - 1];
    assert(scale[0] == 0 && target <= len);
    memset(dist, -1, sizeof(dist));
    dist[0][0] = 0;
    head = tail = 0;
    Q[tail][0] = 0, Q[tail ++][1] = 0;
    while (head < tail) {
        int x = Q[head][0], y = Q[head ++][1];
        if (y == target) {
            break;
        }
        for (int i = 0; i < n; i++) {
#define UPDATE(X,Y) \
            if (dist[X][Y] < 0) { \
                dist[X][Y] = dist[x][y] + 1; \
                Q[tail][0] = X, Q[tail++][1] = Y; \
            }
            UPDATE(i, y);
            UPDATE(x, scale[i]);
            int nz = (scale[x] + y) - scale[i];
            if (nz >= 0 && nz <= len) {
                UPDATE(i, nz);
            }
        }
    }
    int ans = -1;
    for (int i = 0; i < n; i++) {
        if (dist[i][target] >= 0 && (ans < 0 || ans > dist[i][target])) {
            ans = dist[i][target];
        }
    }
    if (ans < 0) {
        puts("IMPOSSIBLE");
    } else {
        printf("%d\n", ans);
    }
}
