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
 
const int MOD = 1000000000 + 7;
 
const int maxn = 222222;
 
int cnt[maxn];
 
int main()
{
    freopen("idempotent.in", "r", stdin);
    freopen("idempotent.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int ai;
        scanf("%d", &ai);
        cnt[ai] ++;
    }
    long long ret = 1, sum = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] <= 1) {
            continue;
        }
        ret = ret * cnt[i] % MOD;
        sum += cnt[i] - 1;
    }
    for (int i = 1; i <= sum; i++) {
        ret = ret * i % MOD;
    }
    cout << ret << endl;
}
