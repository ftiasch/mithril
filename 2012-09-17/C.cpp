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

const int maxn = 16;

int n, m;
char words[128][maxn + 1];
int len[128];

int opt[2][1 << maxn];

int cntbit[1 << maxn];

inline void update(int &a, int v)
{
    if (a < v) {
        a = v;
    }
}

int main()
{
    cntbit[0] = 0;
    for (int i = 1; i < 1 << maxn; i++) {
        cntbit[i] = cntbit[i >> 1] + (i & 1);
    }
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; i++) {
            scanf("%s", words[i]);
            len[i] = strlen(words[i]);
        }
        memset(opt, -1, sizeof(opt));
        int now = 0;
        opt[now][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int *prev = opt[now];
                now ^= 1;
                memset(opt[now], -1, sizeof(int) << m);
                for (int msk = 0; msk < 1 << m; msk++) {
                    if (~prev[msk]) {
                        int pos = cntbit[msk & (1 << j) - 1];
                        if (pos + (m - j - 1) >= len[i]) {
                            if (j + 1 < m || pos == len[i]) {
                                update(opt[now][msk & ~(1 << j)], prev[msk]);
                            }
                        }
                        if (pos < len[i]) {
                            int cost = prev[msk];
                            if (j > 0 && msk >> (j - 1) & 1) {
                                if (words[i][pos - 1] == words[i][pos]) {
                                    cost ++;
                                }
                            }
                            if (i > 0 && msk >> j & 1) {
                                if (words[i - 1][len[i - 1] - cntbit[msk & (1 << m) - (1 << j)]] == words[i][pos]) {
                                    cost ++;
                                }
                            }
                            if (j + 1 < m || pos + 1 == len[i]) {
                                update(opt[now][msk | (1 << j)], cost);
                            }
                        }
                    }
                }
            }
        }
        int best = 0;
        for (int i = 0; i < 1 << m; i++) {
            update(best, opt[now][i]);
        }
        printf("%d\n", best * 2);
    }
}
