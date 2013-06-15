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

const int maxn = 20;

int n;
int t[maxn], x[maxn];
int cover[1 << maxn];

int main()
{
    int cas = 0;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", t + i, x + i);
        }
        cover[0] = 0;
        for (int msk = 1; msk < 1 << n; msk++) {
            int cntbit = 0, sum = 0;
            for (int i = 0; i < n; i++) {
                if (msk >> i & 1) {
                    cntbit ++;
                    sum += t[i];
                }
            }
            cover[msk] = msk;
            int mean = sum / cntbit;
            for (int i = 0; i < n; i++) {
                if (~msk >> i & 1 && abs(t[i] - mean) <= x[i]) {
                    cover[msk] |= 1 << i;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int msk = 0; msk < 1 << n; msk++) {
                if (~msk >> i & 1) {
                    cover[msk | 1 << i] |= cover[msk];
                }
            }
        }
        int ans = n;
        for (int msk = 0; msk < 1 << n; msk ++) {
            if (cover[msk] + 1 == (1 << n)) {
                ans = min(ans, __builtin_popcount(msk));
            }
        }
        printf("Case %d: %d\n", ++cas, ans);
    }
}
