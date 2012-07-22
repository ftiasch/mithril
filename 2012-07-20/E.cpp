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

const int maxn = 155;

int fa[maxn];

int getF(int p)
{
    return fa[p] >= 0 ? fa[p] = getF(fa[p]) : p;
}

bool mergeF(int a, int b)
{
    a = getF(a);
    b = getF(b);
    if (a == b)
        return false;
    fa[a] = b;
    return true;
}

int n, m;
int a[maxn * maxn], b[maxn * maxn];

int cntV[maxn], cntE[maxn];

int memo[maxn][maxn][4];

bool go(int odd, int even, int spare)
{
    int &ret = memo[odd][even][spare];
    if (~ret)
        return ret;
    if (odd + even == 1) {
        return ret = false;
    }
    if (spare > 0 && !go(odd, even, spare - 1)) {
        return ret = true;
    }
    if (odd >= 2 && !go(odd - 2, even + 1, (spare + 0) % 2 + 2)) {
        return ret = true;
    }
    if (even >= 2 && !go(odd, even - 1, (spare + 1) % 2 + 2)) {
        return ret = true;
    }
    if (odd >= 1 && even >= 1 && !go(odd - 1 + 1, even - 1, (spare + 1) % 2 + 2)) {
        return ret = true;
    }
    return ret = false;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(fa, -1, sizeof(fa));
    for (int i = 0; i < m; i++) {
        scanf("%d%d", a + i, b + i);
        a[i] --, b[i] --;
        mergeF(a[i], b[i]);
    }
    memset(cntV, 0, sizeof(cntV));
    memset(cntE, 0, sizeof(cntE));
    for (int i = 0; i < n; i++)
        cntV[getF(i)] ++;
    for (int i = 0; i < m; i++)
        cntE[getF(a[i])] ++;
    int cntOdd = 0, cntEven = 0, cntSpare = 0;
    for (int i = 0; i < n; i++) {
        if (cntV[i] > 0) {
            int edges = cntV[i] * (cntV[i] - 1) / 2;
            edges -= cntE[i];
            cntSpare += edges;
            if (cntV[i] & 1) {
                cntOdd ++;
            } else {
                cntEven ++;
            }
        }
    }
    cntSpare &= 1;
    memset(memo, -1, sizeof(memo));
    if (go(cntOdd, cntEven, cntSpare + 2)) {
        puts("Andrew");
    } else {
        puts("Betty");
    }
}
