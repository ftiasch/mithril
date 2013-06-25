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
int d[maxn][maxn];
int balance[maxn][1 << maxn];

bool visisted[1 << maxn];

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &d[i][j]);
                d[i][j] *= -1;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                balance[i][1 << j] = d[i][j];
            }
            balance[i][0] = 0;
            for (int mask = 1; mask < 1 << n; mask++) {
                int lowbit = mask & -mask;
                balance[i][mask] = balance[i][lowbit] + balance[i][mask ^ lowbit];
            }
        }
        memset(visisted, false, sizeof(*visisted) << n);
        visisted[(1 << n) - 1] = true;
        queue<int> Q;
        Q.push((1 << n) - 1);
        while (!Q.empty()) {
            int mask = Q.front();
            Q.pop();
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1 && balance[i][mask] < 0) {
                    int nmask = mask ^ 1 << i;
                    if (!visisted[nmask]) {
                        visisted[nmask] = true;
                        Q.push(nmask);
                    }
                }
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (visisted[1 << i]) {
                ans.push_back(i);
            }
        }
        //printf("%d", ans.size());
        bool first = true;
        FOR (it, ans) {
            if (first) {
                first = false;
            } else {
                printf(" ");
            }
            printf("%d", *it + 1);
        }
        if (ans.size()) {
            puts("");
        } else {
            puts("0");
        }
    }
}
