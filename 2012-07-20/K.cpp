// Problem K -- XOR
// Author: Bin Jin
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

const int maxn = 64;

int n, bits;
long long a[maxn];
int ones[maxn];

int memo[maxn][maxn];

bool go(int pos, int num1)
{
    int &ret = memo[pos][num1];
    if (~ret)
        return ret;
    if (pos == n)
        return ret = num1 == 0;
    for (int i = 0; i <= ones[pos]; i++) {
        int j = ones[pos] - i;
        if (i <= num1 && j <= bits - num1) {
            if (go(pos + 1, num1 - i + j)) {
                return ret = true;
            }
        }
    }
    return ret = false;
}

long long ans[maxn];

void construct(int pos, int num1, long long num)
{
    assert(go(pos, num1));
    if (pos == n)
        return;
    for (int i = 0; i <= ones[pos]; i++) {
        int j = ones[pos] - i;
        if (i <= num1 && j <= bits - num1) {
            if (go(pos + 1, num1 - i + j)) {
                ans[pos] = 0;
                int cnt[2];
                cnt[1] = i;
                cnt[0] = j;
                for (int k = 0; k < bits; k++) {
                    if (cnt[num >> k & 1]-- > 0) {
                        ans[pos] |= 1LL << k;
                    }
                }
                construct(pos + 1, num1 - i + j, num ^ ans[pos]);
                return;
            }
        }
    }
    assert(false);
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long maxv = *max_element(a, a + n);
    for (bits = 0; (1LL << bits) <= maxv; bits++);
    for (int i = 0; i < n; i++)
        ones[i] = __builtin_popcountll(a[i]);
    memset(memo, -1, sizeof(memo));
    if (!go(0, 0)) {
        puts("impossible");
    } else {
        construct(0, 0, 0LL);
        for (int i = 0; i < n; i++) {
            if (i > 0)
                cout << " ";
            cout << ans[i];
        }
        cout << endl;
    }
}
