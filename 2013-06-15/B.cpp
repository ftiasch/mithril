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
const int MOD = 1000000007;

int n;
char str[maxn * 2];
unsigned long long hash[maxn * 2];
unsigned long long p4423[maxn];
int hashmod[maxn * 2];
int p4423mod[maxn];

bool ans[maxn];

pair<unsigned long long,int> calc(int l, int r)
{
    return make_pair(hash[r] - hash[l] * p4423[r - l],
            (hashmod[r] - (long long)hashmod[l] * p4423mod[r - l] % MOD + MOD) % MOD);
}

int main()
{
    int cas = 0;
    p4423[0] = 1;
    p4423mod[0] = 1;
    for (int i = 1; i < maxn; i++) {
        p4423[i] = p4423[i - 1] * 4423;
        p4423mod[i] = (long long)p4423mod[i - 1] * 4423 % MOD;
    }
    while (scanf("%s", str) == 1) {
        n = strlen(str);
        for (int i = 0; i < n; i++) {
            str[i + n] = str[i];
            ans[i + 1] = false;
        }
        ans[1] = true;
        hash[0] = 0;
        hashmod[0] = 1;
        for (int i = 0; i < n * 2; i++) {
            hash[i + 1] = hash[i] * 4423 + str[i];
            hashmod[i + 1] = ((long long)hashmod[i] * 4423 + str[i]) % MOD;
        }
        vector<int> splitPoints;
        for (int i = 0; i < n; i++) {
            if (str[i] == str[i + n - 1]) {
                splitPoints.push_back(i);
            }
        }
        if (splitPoints.empty()) {
            for (int diff = 1; diff < n; diff++) {
                if (calc(0, n) != calc(diff, n + diff)) {
                    ans[diff + 1] = true;
                }
            }
        } else {
            for (int i = 0; i < splitPoints.size(); i++) {
                int lo = splitPoints[i];
                int hi = splitPoints[(i + 1) % splitPoints.size()];
                if (hi <= lo) {
                    hi += n;
                }
                for (int diff = 1; diff < hi - lo; diff++) {
                    if (calc(lo, hi - diff) != calc(lo + diff, hi)) {
                        ans[diff + 1] = true;
                    }
                }
            }
        }
        printf("Case %d: ", ++cas);
        for (int i = 0; i < n; i++) {
            putchar(ans[n - i] ? '1' : '0');
        }
        puts("");
    }
}
