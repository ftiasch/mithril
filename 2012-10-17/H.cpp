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

const int MOD = 333;
const int MOD2 = 666;
const int MAXN = 110;
const int P10[3] = {1, 10, 100};

char str[MAXN];
int digits[MAXN];
int len;

#define PREV3(a) (((a) + 1) % 3)
#define NEXT3(a) (((a) + 2) % 3)

short memo[MAXN][MAXN][MOD][3][3][3];

void addmod(short &a, short b)
{
    if ((a += b) >= MOD2) {
        a -= MOD2;
    }
}

short go(int p1, int p2, int mod, int p13, int p23, int flag)
{
    if (p1 < 0 || p2 >= len) {
        return 0;
    }
    short &ret = memo[p1][p2][mod][p13][p23][flag];
    if (~ret) {
        return ret;
    }
    ret = 0;
    if (flag == 0) {
        // just find a matching pair
        if (p23 == 0 && mod == 0 && ~digits[p2] & 1) {
            ret = 1;
        }
        addmod(ret, go(p1 - 1, p2 + 1, mod, PREV3(p13), NEXT3(p23), 1));
    } else if (flag == 1) {
        // move to left
        ret = go(p1, p2, mod, p13, p23, 2);
        addmod(ret, go(p1 - 1, p2, mod, p13, p23, 1));
    } else {
        // move to right
        ret = go(p1, p2 + 1, mod, p13, p23, 2);
        if (digits[p1] == digits[p2]) {
            addmod(ret, go(p1, p2, (mod + digits[p1] * (P10[p13] + P10[p23]) % MOD) % MOD, p13, p23, 0));
        }
    }
    return ret;
}

int main()
{
    freopen("ritual.in", "r", stdin);
    freopen("ritual.out", "w", stdout);
    scanf("%s", str);
    len = strlen(str);
    for (int i = 0; i < len; i++) {
        digits[i] = str[i] - '0';
    }
    memset(memo, -1, sizeof(memo));
    short ret = 0;
    for (int p3 = 0; p3 < 3; p3++) {
        for (int i = 0; i < len; i++) {
            addmod(ret, go(i, i, digits[i] * P10[p3] % MOD, p3, p3, 0));
            for (int j = i + 1; j < len; j++) {
                if (digits[i] != digits[j]) {
                    continue;
                }
                addmod(ret, go(i, j, digits[i] * (P10[p3] + P10[NEXT3(p3)]) % MOD, p3, NEXT3(p3), 0));
            }
        }
    }
    printf("%d\n", ret == 0 ? MOD2 : (int)ret);
}
