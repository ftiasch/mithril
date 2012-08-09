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

const int maxn = 101;

int n, m;
int a[maxn][maxn];

int opt[maxn][maxn][maxn];
int prev[maxn][maxn][maxn];

inline void update(int i, int j, int k, int v, int pv)
{
    if (opt[i][j][k] < 0 || opt[i][j][k] > v) {
        opt[i][j][k] = v;
        prev[i][j][k] = pv;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    memset(opt, -1, sizeof(opt));
    opt[0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = j; k <= n; k++) {
                if (opt[i][j][k] < 0) {
                    continue;
                }
                update(i + 1, j, k, opt[i][j][k], 0);
                for (int z = 0; k + z + (m - j) <= n; z++) {
                    update(i + 1, j + 1, k + z + 1, opt[i][j][k] + a[i][z], z + 1);
                }
            }
        }
    }
    assert(opt[n][m][n] >= 0);
    printf("%d\n", opt[n][m][n]);
    int a = m, b = n;
    vector<pair<int,int> > ans;
    for (int i = n - 1; i >= 0; i--) {
        int z = prev[i + 1][a][b];
        if (z > 0) {
            a --;
            b -= z;
            ans.push_back(make_pair(i, z - 1));
        }
    }
    sort(ans.begin(), ans.end());
    assert(ans.size() == m);
    vector<int> ans2(n, -1);
    for (int i = 0; i < ans.size(); i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", ans[i].first + 1);
        ans2[ans[i].first] = i;
    }
    puts("");
    int ptr = 0;
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].second; j++) {
            while (ptr < n && ans2[ptr] >= 0) {
                ptr ++;
            }
            ans2[ptr++] = i;
        }
    }
    for (int i = 0; i < ans2.size(); i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", ans2[i] + 1);
    }
    puts("");
}
