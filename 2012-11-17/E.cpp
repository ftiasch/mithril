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

const double PI = acos(-1.0);

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

double L, D;

double solve(double ang)
{
    double r = D / 2;
    double l = r / cos(ang);
    double h = l * sin(ang);
    double ratio = (l + L) / l;
    return PI * r * r * h / 3 * (ratio * ratio * ratio - 1);
}

int main()
{
    freopen("frustum.in", "r", stdin);
    freopen("frustum.out", "w", stdout);
    while (cin >> L >> D) {
        double ans = 0;
        for (int i = 0; i < 10; i++) {
            double lo = PI / 2 * i / 10;
            double hi = PI / 2 * (i + 1) / 10;
            for (int it = 0; it < 200; ++it) {
                double mid1 = (lo + lo + hi) / 3;
                double mid2 = (lo + hi + hi) / 3;
                if (solve(mid1) > solve(mid2)) {
                    hi = mid2;
                } else {
                    lo = mid1;
                }
            }
            ans = max(ans, solve(lo));
        }
        printf("%.10f\n", ans);
    }
}
