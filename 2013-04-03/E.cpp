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

const int inf = 1000000000;

int n, s;
int v[11], V;
int m[11], num[11][51];

int A;
int a2b[11][101];
int memo[11][101][51];

int go(int i, int sumAi, int sumBi)
{
    int &ret = memo[i][sumAi][sumBi];
    if (~ret) {
        return ret;
    }
    if (i == n) {
        return ret = sumAi == A && sumBi == s ? 0 : inf;
    }
    ret = inf;
    for (int ai = 0, bi; bi = a2b[i][ai], sumAi + ai <= A && sumBi + bi <= s; ai++) {
        ret = min(ret, go(i + 1, sumAi + ai, sumBi + bi) + abs(ai * V - v[i] * A));
    }
    return ret;
}

double minAns = 1e100;
int ans[11];

void construct(int i, int sumAi, int sumBi)
{
    if (i == n) {
        assert(sumAi == A && sumBi == s);
        return;
    }
    int ret = go(i, sumAi, sumBi);
    for (int ai = 0, bi; bi = a2b[i][ai], sumAi + ai <= A && sumBi + bi <= s; ai++) {
        if (ret == go(i + 1, sumAi + ai, sumBi + bi) + abs(ai * V - v[i] * A)) {
            ans[i] = ai;
            construct(i + 1, sumAi + ai, sumBi + bi);
            return;
        }
    }
    assert(false);
}

int main()
{
    scanf("%d%d", &n, &s);
    V = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", v + i, m + i);
        V += v[i];
        for (int j = 0; j < m[i]; j++) {
            scanf("%d", &num[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 100; j++) {
            a2b[i][j] = j;
            for (int k = 0; k < m[i]; k++) {
                if (num[i][k] <= j) {
                    a2b[i][j] --;
                }
            }
        }
    }
    memset(ans, -1, sizeof(ans));
    for (A = s; A <= s + 50; A++) {
        memset(memo, -1, sizeof(memo));
        if (go(0, 0, 0) == inf) {
            continue;
        }
        double val = go(0, 0, 0) / (double)(V * A);
        if (val < minAns) {
            minAns = val;
            construct(0, 0, 0);
        }
    }
    fprintf(stderr, "%.10f\n", minAns);
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
}
