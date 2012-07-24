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

const int maxn = 64;


int n, m;
int next[maxn][maxn];
long long k;
int a[maxn];
vector<int> s;

long long memo[maxn][maxn];

long long go(int p, int lst)
{
    long long &ret = memo[p][lst + 1];
    if (~ret) {
        return ret;
    }
    ret = 1;
    for (int j = lst + 1; j < m; j++) {
        int q = next[p][j];
        if (q >= 0) {
            ret += go(q, j);
        }
    }
    return ret;
}

void construct(int p, int lst, long long k, vector<int> &ans)
{
    assert(k < go(p, lst));
    if (k == 0) {
        return;
    }
    k --;
    for (int j = lst + 1; j < m; j++) {
        int q = next[p][j];
        if (q >= 0) {
            if (k < go(q, j)) {
                ans.push_back(s[j]);
                construct(q, j, k, ans);
                return;
            }
            k -= go(q, j);
        }
    }
    assert(false);
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    s.assign(a, a + n);
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(s.begin(), s.end(), a[i]) - s.begin();
    }
    m = s.size();
    memset(next, -1, sizeof(next));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            next[i][j] = next[i+1][j];
        }
        next[i][a[i]] = i;
    }
    memset(memo, -1, sizeof(memo));
    vector<int> ans;
    construct(0, -1, k, ans);
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << ans[i];
    }
    cout << endl;
}
