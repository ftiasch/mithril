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

int n, m;
int a[1 << 10];
int perm[1 << 10];

bool cmp(int i, int j)
{
    return a[i] > a[j];
}

int main()
{
    freopen("lan.in", "r", stdin);
    freopen("lan.out", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < m; i++) {
            scanf("%d", a + i);
            perm[i] = i;
        }
        sort(perm, perm + m, cmp);
        int ans = -1, sum = 0;
        for (int i = 0; i < m; i++) {
            sum += a[perm[i]];
            if (sum - i * 2 >= n) {
                ans = i + 1;
                break;
            }
        }
        if (ans < 0) {
            puts("Epic fail");
        } else {
            printf("%d\n", ans);
            for (int i = 0; i < ans; i++) {
                if (i > 0) {
                    putchar(' ');
                }
                printf("%d", perm[i] + 1);
            }
            puts("");
        }
    }
}
