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

int solve(int x, int y)
{
    int ret = 0;
    while (true) {
        if (x == 0 && y == 0) {
            return ret;
        }
        if (x >= 0 && y > 0) {
            return ret + x + y;
        }
        y --;
        ret ++;
        swap(x, y);
        x = -x;
    }
}

int main()
{
    int x, y;
    freopen("right-turn-only.in", "r", stdin);
    freopen("right-turn-only.out", "w", stdout);
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d", &x, &y);
        printf("%d\n", solve(x, y));
    }
}
