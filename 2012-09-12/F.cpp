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

const int maxn = 1 << 20;

char str[maxn];
int a[maxn];
int sum[maxn];
int pos[maxn * 2];

int n, m;

bool check(int p, int delta)
{
    int q = sum[p] + delta;
    if (0 <= q && q < maxn * 2) {
        q = pos[q];
        if (~q) {
            if (p > q) {
                swap(p, q);
            }
            printf("%d %d\n", p + 1, q);
            return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", str);
    sum[0] = 0;
    int first1 = -1, last1 = -1;
    for (int i = 0; i < n; i++) {
        a[i] = str[i] == 'T' ? 2 : 1;
        sum[i + 1] = sum[i] + a[i];
        if (a[i] == 1) {
            if (first1 < 0) {
                first1 = i;
            }
            last1 = i;
        }
    }
    memset(pos, -1, sizeof(pos));
    for (int i = 0; i <= n; i++) {
        pos[sum[i]] = i;
    }
    while (m --) {
        int len;
        scanf("%d", &len);
        if (first1 == -1) {
            if (!check(0, len)) {
                puts("NIE");
            }
        } else {
            if (!check(first1, len) && !check(first1 + 1, len)) {
                if (!check(last1, -len) && !check(last1 + 1, -len)) {
                    if (!check(0, len)) {
                        puts("NIE");
                    }
                }
            }
        }
    }
}
