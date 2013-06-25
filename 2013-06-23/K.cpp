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

const int maxn = 50;

int n;
vector<int> parts[maxn];
vector<int> all;

vector<int> col[maxn * maxn];
bool ma[maxn][maxn * maxn];

int memo[maxn * maxn][maxn];

int go(int num, int inRow)
{
    int &ret = memo[num][inRow];
    if (~ret) {
        return ret;
    }
    if (num + 1 == all.size()) {
        return ret = 0;
    }
    ret = 0;
    FOR (nInRow, col[num + 1]) {
        if (col[num].size() == 1) {
            ret = max(ret, go(num + 1, *nInRow) + (inRow == *nInRow ? 1 : 0));
        } else {
            ret = max(ret, go(num + 1, *nInRow) + (inRow != *nInRow && ma[*nInRow][num] ? 1 : 0));
        }
    }
    return ret;
}

int main()
{
    int cas = 0;
    while (scanf("%d", &n) == 1) {
        all.clear();
        int splitCnt = 0;
        for (int i = 0; i < n; i++) {
            int sz;
            scanf("%d", &sz);
            parts[i].resize(sz);
            for (int j = 0; j < sz; j++) {
                scanf("%d", &parts[i][j]);
                all.push_back(parts[i][j]);
            }
            sort(parts[i].begin(), parts[i].end());
            parts[i].erase(unique(parts[i].begin(), parts[i].end()), parts[i].end());
            splitCnt += parts[i].size() - 1;
        }
        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());
        for (int i = 0; i < n; i++) {
            FOR (it, parts[i]) {
                *it = lower_bound(all.begin(), all.end(), *it) - all.begin();
            }
        }
        memset(ma, 0, sizeof(ma));
        for (int i = 0; i < all.size(); i++) {
            col[i].clear();
        }
        for (int i = 0; i < n; i++) {
            FOR (it, parts[i]) {
                col[*it].push_back(i);
                ma[i][*it] = true;
            }
        }
        int maxv = 0;
        memset(memo, -1, sizeof(memo));
        FOR (it, col[0]) {
            maxv = max(maxv, go(0, *it));
        }
        int ans = (splitCnt - maxv) * 2 + (n - 1);
        printf("Case %d: %d\n", ++cas, ans);
    }
}
