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

int memo[1 << 10][21][21];

int n;
int side[10][3];

int go(int mask, int X, int Y)
{
    int &ret = memo[mask][X][Y];
    if (~ret) {
        return ret;
    }
    ret = 0;
    for (int i = 0; i < n; i++) {
        if (~mask >> i & 1) {
            sort(side[i], side[i] + 3);
            do {
                if (X <= side[i][0] && Y <= side[i][1]) {
                    ret = max(ret, go(mask | 1 << i, side[i][0], side[i][1]) + 1);
                }
            } while (next_permutation(side[i], side[i] + 3));
        }
    }
    return ret;
}

int main()
{
    int cas = 0;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%d", &side[i][j]);
            }
        }
        memset(memo, -1, sizeof(memo));
        printf("Case %d: %d\n", ++cas, go(0, 0, 0));
    }
}

