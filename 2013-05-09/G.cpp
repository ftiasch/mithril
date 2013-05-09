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

const int maxn = 50000;
const int maxh = 137777;

int n, k;

long long hash[maxn][1 << 6];
char str[maxn][7];

int ans[maxn][7];

long long keys[maxh];
vector<int> values[maxh];

int find(long long key)
{
    int pos = (unsigned long long)key % maxh;
    while (~keys[pos] && keys[pos] != key) {
        if (++pos == maxh) {
            pos = 0;
        }
    }
    return pos;
}

int main()
{
    freopen("similar.in", "r", stdin);
    freopen("similar.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%s", str[i]);
    }
    memset(hash, 0, sizeof(hash));
    memset(ans, -1, sizeof(ans));
    for (int mask = 1; mask < 1 << k; mask++) {
        int lowbit = 0;
        while (~mask >> lowbit & 1) {
            lowbit ++;
        }
        for (int i = 0; i < n; i++) {
            hash[i][mask] = hash[i][mask ^ 1 << lowbit] * 128 + str[i][lowbit];
        }
    }
    for (int mask = 0; mask < 1 << k; mask++) {
        memset(keys, -1, sizeof(keys));
        vector<int> hashPos;
        int len = __builtin_popcount(mask);
        for (int i = 0; i < n; i++) {
            int pos = find(hash[i][mask]);
            if (keys[pos] == -1) {
                keys[pos] = hash[i][mask];
                values[pos].clear();
                hashPos.push_back(pos);
            }
            values[pos].push_back(i);
        }
        FOR (pos, hashPos) {
            if (values[*pos].size() == 1) {
                continue;
            }
            for (int i = 0; i < values[*pos].size(); i++) {
                ans[values[*pos][i]][k - len] = values[*pos][i == 0 ? 1 : 0];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (ans[i][j] >= 0) {
                printf("%d %d\n", j, ans[i][j] + 1);
                break;
            }
        }
    }
}
