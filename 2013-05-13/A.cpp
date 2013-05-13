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

const int maxn = 100011;

int n;
pair<int,pair<int,int> > a[maxn];
int x[maxn];
int l[maxn], r[maxn];

int tree[maxn];

void add(int pos, int value)
{
    for (pos ++; pos > 0; pos -= pos & -pos) {
        tree[pos] = min(tree[pos], value);
    }
}

int get(int pos)
{
    int ret = pos;
    for (pos ++; pos <= n; pos += pos & -pos) {
        ret = min(ret, tree[pos]);
    }
    return ret;
}

int stL[17][maxn], stR[17][maxn];
int ln2[maxn];

bool update(int &lo, int &hi)
{
    int len = ln2[hi - lo + 1];
    int nLo = min(stL[len][lo], stL[len][hi - (1 << len) + 1]);
    int nHi = max(stR[len][lo], stR[len][hi - (1 << len) + 1]);
    if (nLo != lo || nHi != hi) {
        lo = nLo;
        hi = nHi;
        return true;
    }
    return false;
}

void solve(int *l)
{
    for (int i = 0; i < n; i++) {
        tree[i + 1] = i;
    }
    for (int i = 0; i < n; i++) {
        l[i] = get(l[i]);
        add(i, l[i]);
    }
}

int ans[maxn];

int main()
{
    ln2[1] = 0;
    for (int i = 2; i < maxn; i++) {
        ln2[i] = ln2[i - 1];
        if ((i & i - 1) == 0) {
            ln2[i] ++;
        }
    }
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &a[i].first, &a[i].second.first);
            a[i].second.second = i;
        }
        sort(a, a + n);
        for (int i = 0; i < n; i++) {
            x[i] = a[i].first;
        }
        for (int i = 0; i < n; i++) {
            l[i] = lower_bound(x, x + n, a[i].first - a[i].second.first) - x;
            r[i] = upper_bound(x, x + n, a[i].first + a[i].second.first) - x - 1;
        }
        solve(l);
        reverse(r, r + n);
        for (int i = 0; i < n; i++) {
            r[i] = n - 1 - r[i];
        }
        solve(r);
        reverse(r, r + n);
        for (int i = 0; i < n; i++) {
            r[i] = n - 1 - r[i];
        }
        for (int i = 0; i < n; i++) {
            stL[0][i] = l[i];
            stR[0][i] = r[i];
        }
        for (int i = 1; (1 << i) <= n; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                stL[i][j] = min(stL[i - 1][j], stL[i - 1][j + (1 << i - 1)]);
                stR[i][j] = max(stR[i - 1][j], stR[i - 1][j + (1 << i - 1)]);
            }
        }
        for (int i = 0; i < n; i++) {
            while (update(l[i], r[i]));
            ans[a[i].second.second] = r[i] - l[i] + 1;
        }
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", ans[i]);
        }
        puts("");
    }
}
