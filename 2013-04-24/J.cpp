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

const int maxn = 1555;

int na, nb;
int t[2][maxn];
int wa, wb, x;

long long minTime[2][maxn][maxn];
int prev[2][maxn][maxn];

const int A = 0;
const int B = 1;

long long ans[2][maxn];

bool update(long long &a, long long v)
{
    if (a < 0 || a > v) {
        a = v;
        return true;
    }
    return false;
}

int main()
{
    while (scanf("%d", &na) == 1 && na > 0) {
        for (int i = 0; i < na; i++) {
            scanf("%d", &t[A][i]);
        }
        scanf("%d", &nb);
        for (int i = 0; i < nb; i++) {
            scanf("%d", &t[B][i]);
        }
        scanf("%d%d%d", &wa, &wb, &x);
        for (int i = 0; i <= na; i++) {
            memset(minTime[A][i], -1, sizeof(long long) * (nb + 1));
            memset(minTime[B][i], -1, sizeof(long long) * (nb + 1));
        }
        minTime[A][1][0] = t[A][0];
        minTime[B][0][1] = t[B][0];
        for (int a = 0; a <= na; a++) {
            for (int b = 0; b <= nb; b++) {
                for (int side = 0; side < 2; side ++) {
                    long long &T = minTime[side][a][b];
                    int aPos = a + wa, bPos = b + wb;
                    if (side == A) {
                        aPos --;
                    } else {
                        bPos --;
                    }
                    if (T >= 0) {
                        T = max(T, (long long)t[side][side == A ? a - 1 : b - 1]);
                    }
                    if (aPos < na && t[A][aPos] <= T) {
                        T = -1;
                    }
                    if (bPos < nb && t[B][bPos] <= T) {
                        T = -1;
                    }
                    if (T < 0) {
                        continue;
                    }
                    if (a < na && update(minTime[A][a + 1][b], T + (side == A ? 1 : x))) {
                        prev[A][a + 1][b] = side;
                    }
                    if (b < nb && update(minTime[B][a][b + 1], T + (side == B ? 1 : x))) {
                        prev[B][a][b + 1] = side;
                    }
                }
            }
        }
        int z = -1;
        if (minTime[A][na][nb] >= 0) {
            z = A;
        } else if (minTime[B][na][nb] >= 0) {
            z = B;
        }
        if (z < 0) {
            puts("No solution");
            puts("");
        } else {
            int a = na, b = nb;
            while (a > 0 || b > 0) {
                int nz = prev[z][a][b];
                long long T = minTime[z][a][b];
                if (z == A) {
                    ans[A][--a] = T;
                } else {
                    ans[B][--b] = T;
                }
                z = nz;
            }
            for (int i = 0; i < na; i++) {
                if (i > 0) {
                    putchar(' ');
                }
                printf("%lld", ans[A][i]);
            }
            puts("");
            for (int i = 0; i < nb; i++) {
                if (i > 0) {
                    putchar(' ');
                }
                printf("%lld", ans[B][i]);
            }
            puts("");
        }
    }
}
