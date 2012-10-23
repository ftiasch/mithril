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

map<long long, double> memo[55][2];

int n, c;
double prob[55];

double go(int pos, long long money, bool used)
{
    if (memo[pos][(int)used].count(money)) {
        return memo[pos][(int)used][money];
    }
    double &ret = memo[pos][(int)used][money];
    ret = money;
    if (pos < n) {
        ret = max(ret, go(pos + 1, money * 2, used) * prob[pos]);
        if (money >= c && !used) {
            ret = max(ret, go(pos + 1, (money - c) * 2, true) * prob[pos] + 
                    go(pos + 1, money - c, true) * (1 - prob[pos]));
        }
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &c);
    for (int i = 0; i < n; i++) {
        scanf("%lf", prob + i);
        prob[i] /= 100;
    }
    printf("%.10f\n", go(0, 100, false));
}
