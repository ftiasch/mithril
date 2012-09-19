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

double solve(int c, int m)
{
    if (m > c) {
        return 0.;
    }
    double ret = 1.0;
    for (int i = 0; i < m; i++) {
        ret = ret * (2 * c - m - i) / (2 * c - 1 - 2 * i);
        if (ret < 1e-11) {
            return 0.0;
        }
    }
    return ret;
}

int main()
{
    freopen("dance.in", "r", stdin);
    freopen("dance.out", "w", stdout);
    int c, m, f;
    scanf("%d%d%d", &c, &m, &f);
    printf("%.10lf\n", 1.0 - solve(c, m));
}
