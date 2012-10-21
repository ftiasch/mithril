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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

int signum(double a)
{
    return a < -eps ? -1 : a > eps ? 1 : 0;
}

struct Num
{
    int sign;
    double logSum;

    Num() : sign(1), logSum(0) {}

    Num(int sign, double logSum) : sign(sign), logSum(logSum) {}

    Num(double a) {
        sign = signum(a);
        if (sign) {
            logSum = log(a * sign);
        }
    }

    Num operator*(const Num &o) const {
        return Num(sign * o.sign, logSum + o.logSum);
    }

    bool operator==(const Num &o) const {
        return sign == o.sign && fabs(logSum - o.logSum) < eps;
    }

    bool operator<(const Num &o) const {
        return sign < o.sign || sign == o.sign && sign * logSum + eps < o.sign * o.logSum;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    vector<pair<Num, int> > a;
    for (int i = 0; i < n; i++) {
        double ai;
        scanf("%lf", &ai);
        a.push_back(make_pair(Num(ai), i));
    }
    sort(a.begin(), a.end());
    int lo = 0, hi = 0;
    while (hi < a.size() && Num(1.0) < a[a.size() - 1 - hi].first) {
        hi ++;
    }
    Num maxv = 1.0, mul = 1.0;
    if (hi == 0) {
        maxv = a.back().first;
    }
    for (int i = 1; i + hi <= a.size(); i++) {
        mul = mul * a[i - 1].first;
        if (maxv < mul) {
            maxv = mul;
            lo = i;
        }
    }
    if (lo == 0 && hi == 0) {
        hi ++;
    }
    vector<int> ans;
    for (int i = 0; i < lo; i++) {
        ans.push_back(a[i].second);
    }
    for (int i = 0; i < hi; i++) {
        ans.push_back(a[a.size() - 1 - i].second);
    }
    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", ans[i] + 1);
    }
    puts("");
}
