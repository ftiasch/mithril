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

long long memo[64][2][2];
int L[64], R[64], X[64];

long long go(int pos, int gt, int lt)
{
    if (pos < 0) {
        return 1;
    }
    long long &ret = memo[pos][gt][lt];
    if (~ret) {
        return ret;
    }
    ret = 0;
    for (int i = 0; i < 2; i++) {
        int before = i ^ X[pos];
        if ((gt || before >= L[pos]) && (lt || before <= R[pos])) {
            ret += go(pos - 1, gt || before > L[pos], lt || before < R[pos]);
        }
    }
    return ret;
}

void construct(int pos, int gt, int lt, long long k, long long &ans)
{
    if (pos < 0) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        int before = i ^ X[pos];
        if ((gt || before >= L[pos]) && (lt || before <= R[pos])) {
            long long res = go(pos - 1, gt || before > L[pos], lt || before < R[pos]);
            if (k < res) {
                ans = ans * 2 + before;
                construct(pos - 1, gt || before > L[pos], lt || before < R[pos], k, ans);
                return;
            }
            k -= res;
        }
    }
    assert(false);
}
int main()
{
    long long l, r, x, k;
    cin >> l >> r >> x >> k;
    for (int i = 0; i < 64; i++) {
        L[i] = l & 1, l >>= 1;
        R[i] = r & 1, r >>= 1;
        X[i] = x & 1, x >>= 1;
    }
    memset(memo, -1, sizeof(memo));
    long long ans = 0;
    construct(63, 0, 0, k - 1, ans);
    cout << ans << endl;
}
