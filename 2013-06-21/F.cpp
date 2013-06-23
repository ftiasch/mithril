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

const int maxn = 1000;
const double pi = acos(-1.);

int n;
int x[maxn], y[maxn];

double val[maxn];

double minv = 1e100;

double get(double ang)
{
    double X = sin(ang), Y = cos(ang);
    for (int i = 0; i < n; i++) {
        val[i] = x[i] * X + y[i] * Y;
    }
    nth_element(val, val + n / 2, val + n);
    double ret = 0;
    int l = 0, r = n - 1;
    while (l < r) {
        ret += val[r] - val[l];
        l ++, r --;
    }
    minv = min(minv, ret);
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", x + i, y + i);
    }
    double base = 0.4423;
    vector<double> splits(30);
    for (int i = 0; i < splits.size(); i++) {
        splits[i] = base + pi / splits.size() * i;
    }
    for (int jt = 0; jt < 5; jt++) {
        vector<double> nsplits;
        for (int i = 0; i < splits.size(); i++) {
            double lo = splits[i], hi = splits[(i + 1) % splits.size()];
            if (hi < lo) {
                hi += pi;
            }
            for (int kt = 0; kt < 50; ++kt) {
                double mid1 = lo * 0.55 + hi * 0.45;
                double mid2 = lo * 0.45 + hi * 0.55;
                if (get(mid1) < get(mid2)) {
                    hi = mid2;
                } else {
                    lo = mid1;
                }
            }
            nsplits.push_back((lo + hi) / 2);
        }
        splits = nsplits;
    }
    printf("%.10f\n", minv);
}
