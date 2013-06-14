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
const int maxsg = 1 << 8;

int sg[maxn][maxn], psum[maxn][maxn];
int ways[maxn][maxn][maxsg];
int last[maxn][maxn][maxsg];

int stamp[maxsg], stampTime;

int a[maxn][maxn];

int main()
{
    memset(last, -1, sizeof(last));
    memset(ways, 0, sizeof(ways));
    for (int r = 1; r < maxn; r++) {
        for (int c = 1; c < maxn; c++) {
            psum[r][c] = psum[r][c - 1] ^ psum[r - 1][c] ^ psum[r - 1][c - 1];
            stampTime ++;
            for (int i = 0; i < r; i ++) {
                for (int j = 0; j < c; j++) {
                    int nsg = psum[r][c] ^ psum[r][j] ^ psum[i][c] ^ psum[i][j];
                    stamp[nsg] = stampTime;
                    ways[r][c][nsg] ++;
                    last[r][c][nsg] = i << 10 | j;
                }
            }
            sg[r][c] = 0;
            while (sg[r][c] < maxsg && stamp[sg[r][c]] == stampTime) {
                sg[r][c] ++;
            }
            assert(sg[r][c] < maxsg);
            psum[r][c] ^= sg[r][c];
        }
    }
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        int xorSum = 0;
        for (int i = 0 ; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
                if (a[i][j]) {
                    xorSum ^= sg[n - i][m - j];
                }
            }
        }
        if (xorSum == 0) {
            puts("No");
        } else {
            int sumWays = 0;
            int x1 = -1, y1, x2, y2;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (a[i][j]) {
                        int deltaXor = sg[n - i][m - j] ^ xorSum;
                        if (ways[n - i][m - j][deltaXor]) {
                            sumWays += ways[n - i][m - j][deltaXor];
                            if (x1 < 0) {
                                x1 = i;
                                y1 = j;
                                x2 = n - (last[n - i][m - j][deltaXor] >> 10);
                                y2 = m - (last[n - i][m - j][deltaXor] & 1023);
                            }
                        }
                    }
                }
            }
            printf("%d %d %d %d %d\n", sumWays, x1 + 1, y1 + 1, x2, y2);
        }
    }
}
