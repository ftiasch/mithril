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

const int maxn = 1024;
const int limit = maxn * maxn / 2;

struct Table
{
    long long table[maxn][maxn];

    void clear() {
        memset(table, 0, sizeof(table));
    }

    void add(int x, int y, long long delta) {
        for (int X = x; X < maxn; X += X & -X) {
            for (int Y = y; Y < maxn; Y += Y & -Y) {
                table[X][Y] += delta;
            }
        }
    }

    long long get(int x, int y) {
        long long ret = 0;
        for (int X = x; X > 0; X -= X & -X) {
            for (int Y = y; Y > 0; Y -= Y & -Y) {
                ret += table[X][Y];
            }
        }
        return ret;
    }
};

Table xy, x, y, unit;

long long pieces[maxn][maxn];
int sqrti[maxn * maxn];

void prepare()
{
    memset(sqrti, -1, sizeof(sqrti));
    for (int i = 0; i < maxn; i++) {
        sqrti[i * i] = i;
    }
    memset(pieces, 0, sizeof(pieces));
    for (int dx = 1; dx < maxn; dx++) {
        for (int dy = 0; dy < maxn; dy++) {
            int len2 = dx * dx + dy * dy;
            if (len2 > limit) {
                break;
            }
            if (sqrti[len2] >= 0) {
                int len = sqrti[len2];
                for (int r1 = 1; r1 < len; r1++) {
                    int r2 = len - r1;
                    int xlen = max(0 + r1, dx + r2) - min(0 - r1, dx - r2);
                    int ylen = max(0 + r1, dy + r2) - min(0 - r1, dy - r2);
                    if (xlen < maxn && ylen < maxn) {
                        pieces[xlen][ylen] ++;
                        pieces[ylen][xlen] ++;
                    }
                }
            }
        }
    }
    xy.clear(), x.clear(), y.clear(), unit.clear();
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j < maxn; j++) {
            if (pieces[i][j] > 0) {
                xy.add(i, j, pieces[i][j] * i * j);
                x.add(i, j, pieces[i][j] * i);
                y.add(i, j, pieces[i][j] * j);
                unit.add(i, j, pieces[i][j]);
            }
        }
    }
}

int main()
{
    prepare();
    int tests, cas = 0;
    scanf("%d", &tests);
    while (tests --) {
        int n, m;
        scanf("%d%d", &n, &m);
        long long ret = 0;
        ret += unit.get(n, m) * (n + 1) * (m + 1);
        ret -= x.get(n, m) * (m + 1);
        ret -= y.get(n, m) * (n + 1);
        ret += xy.get(n, m);
        cout << "Case " << ++cas << ": " << ret << endl;
    }
}

