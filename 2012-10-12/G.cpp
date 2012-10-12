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

int n, m, k;

const int maxn = 50;
const int MOD = 10003;

int memo[maxn + 1][maxn + 1][maxn + 1][2 * maxn + 1];

inline void addmod(int &a, int v)
{
    if ((a += v) >= MOD) {
        a -= MOD;
    }
}

#define C2(n) (((n) * (n - 1)) >> 1)

int go(int pos, int num0, int num1, int num)
{
    int &ret = memo[pos][num0][num1][num];
    if (~ret) {
        return ret;
    }
    if (pos == n) {
        return ret = num == k ? 1 : 0;
    }
    ret = 0;
    // 0 + 0
    addmod(ret, go(pos + 1, num0, num1, num));
    // 0 + 1
    if (num1 >= 1) {
        addmod(ret, go(pos + 1, num0, num1 - 1, num + 1) * num1 % MOD);
    }
    // 0 + 2
    if (num1 >= 2) {
        addmod(ret, go(pos + 1, num0, num1 - 2, num + 2) * C2(num1) % MOD);
    }
    // 1 + 0
    if (num0 >= 1) {
        addmod(ret, go(pos + 1, num0 - 1, num1 + 1, num + 1) * num0 % MOD);
    }
    // 1 + 1
    if (num0 >= 1 && num1 >= 1) {
        addmod(ret, go(pos + 1, num0 - 1, num1, num + 2) * num0 % MOD * num1 % MOD);
    }
    // 2 + 0
    if (num0 >= 2) {
        addmod(ret, go(pos + 1, num0 - 2, num1 + 2, num + 2) * C2(num0) % MOD);
    }
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    memset(memo, -1, sizeof(memo));
    printf("%d\n", go(0, m, 0, 0));
}
