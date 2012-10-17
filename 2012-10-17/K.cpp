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

const int maxn = 1 << 10;

int a[maxn];
set<pair<int,int> > S;

void modify(int i, int delta)
{
    S.erase(make_pair(a[i], i));
    a[i] += delta;
    S.insert(make_pair(a[i], i));
}

int main()
{
    freopen("table.in", "r", stdin);
    freopen("table.out", "w", stdout);
    int n;
    scanf("%d", &n);
    if (n % 2 == 0) {
        puts("IMPOSSIBLE");
        return 0;
    }
    n /= 2;
    memset(a, 0, sizeof(a));
    a[n] = 2 * n + 1;
    S.clear();
    for (int i = 0; i < 2 * n + 1; i++) {
        S.insert(make_pair(a[i], i));
    }
    bool first = true;
    while (true) {
        int p = S.rbegin()->second;
        if (a[p] == 1) {
            break;
        }
        if (first) {
            first = false;
        } else {
            putchar(' ');
        }
        printf("%d", (p - n + (2 * n + 1)) % (2 * n + 1) + 1);
        assert(p != 0 && p != 2 * n);
        modify(p, -2);
        modify(p - 1, 1);
        modify(p + 1, 1);
    }
    puts("");
}
