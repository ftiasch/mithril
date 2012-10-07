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

bool check(double x, double y, double r)
{
    return x * x + y * y <= r * r;
}

int main()
{
    freopen("speed.in", "r", stdin);
    freopen("speed.out", "w", stdout);
    double w1, w2;
    while (cin >> w1 >> w2) {
        double lo = max(w1, w2), hi = 1e10;
        for (int it = 0; it < 200; ++it) {
            double mid = (lo + hi) / 2.0;
            if (check(mid - w1, mid - w2, mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        printf("%.15f\n", (lo + hi) / 2.0);
    }
}
