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

const double eps = 1e-11;

bool check(int prefix, int num)
{
    while (num > prefix) {
        num /= 10;
    }
    return prefix == num;
}

int main()
{
    freopen("fraction.in", "r", stdin);
    freopen("fraction.out", "w", stdout);
    int n, b, q;
    while (cin >> n >> b >> q) {
        double ans = 0.;
        if (q == 1) {
            if (check(n, b)) {
                ans = 1;
            }
        } else if (q == 10 || q == 100 || q == 1000) {
            if (check(n, b * 100000)) {
                ans = 1;
            }
        } else {
            double N = n, N2 = n + 1;
            while (N + eps >= 1) {
                N /= 10;
                N2 /= 10;
            }
            ans = log10(N2) - log10(N);
        }
        printf("%.15f\n", ans);
    }
}
