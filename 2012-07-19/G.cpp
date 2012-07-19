// Problem G -- Princess
// Author: Bin Jin
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

double solve(double t)
{
    double last = -1e100;
    for (int n = 1; ; n++) {
        double now = log(t / n) * n;
        if (now < last) {
            return exp(last);
        }
        last = now;
    }
}

int main()
{
    double n;
    while (cin >> n) {
        double lo = 1.0;
        double hi = 1.0;
        while (solve(hi) < n) {
            hi *= 2.0;
        }
        for (int it = 0; it < 200; ++it) {
            double mid = (lo + hi) / 2;
            if (solve(mid) >= n) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        printf("%.10lf\n", lo);
    }
}
