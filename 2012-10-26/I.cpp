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

const int maxn = 2012;

double a[maxn], suffix[maxn];

double solve(int n)
{
    if (n == 1) {
        return 1.0;
    }
    suffix[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = suffix[i + 1] * a[i];
    }
    double ret = 0.0;
    for (int x = 1; x < n; x++) {
        double mul = 1, sum = 0;
        for (int y = x; y < n; y++) {
            // drop first x and marry y
            sum += mul / (y + 1) * suffix[y + 1];
            mul *= a[y];
        }
        ret = max(ret, sum);
    }
    return ret;
}

int main()
{
    for (int i = 0; i < maxn; i++) {
        a[i] = (double)i / (i + 1);
    }
    int n;
    scanf("%d", &n);
    printf("%.15f\n", solve(n));
}
