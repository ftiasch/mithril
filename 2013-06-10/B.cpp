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

const int maxn = 1 << 20;
const int MOD = 1000000000 + 7;

int ans[maxn];
int inverse[maxn];
int k, p, t;

int main()
{
    scanf("%d%d%d", &k, &p, &t);
    inverse[1] = 1;
    for (int i = 2; i < p; i++) {
        inverse[i] = (long long)(MOD - MOD / i) * inverse[MOD % i] % MOD;
    }
    ans[0] = 1;
    for (int i = 1; i < p; i++) {
        ans[i] = (long long)ans[i - 1] * (i + k - 1) % MOD * inverse[i] % MOD;
    }
    for (int i = 0; i < t; i++) {
        long long input, mul = 1;
        scanf("%lld", &input);
        while (input > 0) {
            mul = mul * ans[input % p] % MOD;
            input /= p;
        }
        printf("%d\n", (int)mul);
    }
}
