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
const int mid = maxn / 2;

int n;
int a[5000];
bool big[maxn], *vis = big + mid;

int main()
{
    scanf("%d", &n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        for (int j = 0; j < i; j++) {
            if (vis[a[i] - a[j]]) {
                ans ++;
                break;
            }
        }
        for (int j = 0; j <= i; j++) {
            vis[a[i] + a[j]] = true;
        }
    }
    printf("%d\n", ans);
}
