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

const int maxn = 100;

long long n, k;
long long memo[maxn][2];
int digit[maxn], digitCount;

long long go(int pos, int lt)
{
    long long &ret = memo[pos][lt];
    if (~ret) {
        return ret;
    }
    if (pos == digitCount) {
        return ret = 1;
    }
    ret = 0;
    for (int i = 0; i < k; i++) {
        if ((digitCount - pos) % 2 == 0 && i > 0) {
            continue;
        }
        if (lt || i <= digit[pos]) {
            ret += go(pos + 1, lt || i < digit[pos]);
        }
    }
    return ret;
}

int main()
{
    freopen("great.in", "r", stdin);
    freopen("great.out", "w", stdout);
    cin >> n >> k;
    digitCount = 0;
    for (long long t = n; t; ) {
        digit[digitCount ++] = t % k;
        t /= k;
    }
    reverse(digit, digit + digitCount);
    memset(memo, -1, sizeof(memo));
    cout << go(0, 0) << endl;
}
