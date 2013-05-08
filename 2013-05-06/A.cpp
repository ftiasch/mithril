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

int n, m;

int bits[2][32];

long long memo[33][2][2];

long long go(int pos, int carry0, int carry1)
{
    long long &ret = memo[pos][carry0][carry1];
    if (~ret) {
        return ret;
    }
    if (pos == 32) {
        return ret = carry0 == 0 && carry1 == 0 ? 1 : 0;
    }
    ret = 0;
    for (int msk = 0; msk < 16; msk++) {
        int tmp = (msk ^ msk >> 2) & 3;
        if (tmp == 1 || tmp == 2) {
            continue;
        }
        int num0 = (msk >> 0 & 1) + (msk >> 1 & 1) + carry0;
        int num1 = (msk >> 2 & 1) + (msk >> 3 & 1) + carry1;
        if ((num0 & 1) != bits[0][pos]) {
            continue;
        }
        if ((num1 & 1) != bits[1][pos]) {
            continue;
        }
        ret += go(pos + 1, num0 >> 1, num1 >> 1);
    }
    return ret;
}

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d", &n, &m);
        n --, m--;
        for (int i = 0; i < 32; i++) {
            bits[0][i] = n & 1, n >>= 1;
            bits[1][i] = m & 1, m >>= 1;
        }
        memset(memo, -1, sizeof(memo));
        printf("%lld\n", go(0, 0, 0));
    }
}
