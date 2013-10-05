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

int main()
{
    int n;
    int cas = 0;
    while (scanf("%d", &n) == 1 && n) {
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x[i], &y[i]);
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        int X = x[(n - 1) / 2];
        int Y = y[(n - 1) / 2];
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += abs(X - x[i]);
            ans += abs(Y - y[i]);
        }
        printf("Case %d: (%d,%d) %d\n", ++cas, X, Y, ans);
    }
}
