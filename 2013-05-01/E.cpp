#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <cctype>
#include <sstream>

using namespace std;

#define FOR(it, a) for (__typeof((a).begin()) it=(a).begin(); it != (a).end(); ++it)

const int maxn = 51;

pair<int,int> sorted[maxn * maxn];
int len;

int n, m;
char input[maxn][maxn];

int main()
{
    scanf("%d%d", &n, &m);
    int blacks = 0;
    for (int i = 0; i < n; i++) {
        scanf("%s", input[i]);
        for (int j = 0; j < m; j++) {
            if (input[i][j] == '#') {
                blacks ++;
            }
        }
    }
    int ans = n * m + 10;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int maxR = min(min(i + 1, n - i), min(j + 1, m - j));
            len = 0;
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    int dis = (x - i) * (x - i) + (y - j) * (y - j);
                    if (dis < maxR * maxR) {
                        sorted[len++] = make_pair(dis, x * m + y);
                    }
                }
            }
            sort(sorted, sorted + len);
            int now = blacks;
            for (int p = 0; p < len; ) {
                int np = p + 1;
                while (np < len && sorted[p].first == sorted[np].first) {
                    np ++;
                }
                for (int q = p; q < np; q++) {
                    int x = sorted[q].second / m;
                    int y = sorted[q].second % m;
                    if (input[x][y] == '#') {
                        now --;
                    } else {
                        now ++;
                    }
                }
                ans = min(ans, now);
                p = np;
            }
        }
    }
    printf("%d\n", ans);
}
