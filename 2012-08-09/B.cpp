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

const int maxn = 111111;

int n;
int a[maxn << 1];
int ans[maxn];

int tree[maxn << 1];

void add(int p, int delta)
{
    for (p ++; p < (maxn << 1); p += p & -p) {
        tree[p] += delta;
    }
}

int get(int p)
{
    int ret = 0;
    for (p ++; p > 0; p -= p & -p) {
        ret += tree[p];
    }
    return ret;
}

void solve()
{
    vector<pair<pair<int,int>, int> > pairs(n);
    for (int i = 0; i < n; i++) {
        pairs[i].first.first = -1;
        pairs[i].first.second = -1;
        pairs[i].second = i;
    }
    for (int i = 0; i < 2 * n; i++) {
        int ai = a[i];
        if (pairs[ai].first.first == -1) {
            pairs[ai].first.first = i;
        } else {
            pairs[ai].first.second = i;
        }
    }
    sort(pairs.begin(), pairs.end());
    memset(tree, 0, sizeof(tree));
    for (int i = 0; i < pairs.size(); i++) {
        ans[pairs[i].second] += get(pairs[i].first.second);
        ans[pairs[i].second] -= get(pairs[i].first.first);
        add(pairs[i].first.second, 1);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++) {
        scanf("%d", a + i);
        a[i] --;
    }
    memset(ans, 0, sizeof(ans));
    solve();
    reverse(a, a + 2 * n);
    solve();
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
}
