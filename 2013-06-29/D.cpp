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

const double eps = 1e-6;

typedef vector<double> poly;

poly operator+(const poly &a, const poly &b)
{
    poly ret = a;
    if (ret.size() < b.size()) {
        ret.resize(b.size(), 0.0);
    }
    for (int i = 0; i < b.size(); i++) {
        ret[i] += b[i];
    }
    return ret;
}

poly operator*(const poly &a, const poly &b)
{
    poly ret(max(0, (int)a.size() + (int)b.size() - 1), 0.0);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            ret[i + j] += a[i] * b[j];
        }
    }
    return ret;
}

poly interpolation(const vector<double> &x, const vector<double> &y)
{
    int n = x.size();
    poly ret(1, 0.0);
    for (int i = 0; i < n; i++) {
        poly mul(1, 1.0);
        double div = 1.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                poly now;
                now.push_back(-x[j]);
                now.push_back(1.0);
                mul = mul * now;
                div = div * (x[i] - x[j]);
            }
        }
        FOR (it, mul) {
            *it *= y[i] / div;
        }
        ret = ret + mul;
    }
    return ret;
}

double eval(const poly &p, double x)
{
    double ret = 0;
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        ret = ret * x + p[i];
    }
    return ret;
}

int main()
{
    int d;
    while (scanf("%d", &d) == 1 && d) {
        vector<double> val(d + 3);
        for (int i = 0; i < val.size(); i++) {
            scanf("%lf", &val[i]);
        }
        double minv = 1e100;
        int mini = -1;
        for (int remove = 0; remove < val.size(); remove ++) {
            vector<double> x, y;
            for (int i = 0; i < val.size(); i++) {
                if (i == remove) {
                    continue;
                }
                x.push_back(i);
                y.push_back(val[i]);
            }
            poly p = interpolation(x, y);
            double error1 = fabs(eval(p, x[remove]) - y[remove]);
            double error2 = fabs(p.back());
//printf("%.10f %.10f\n", error1, error2);
            //if (error1 >= 1 - eps) {
                if (error2 < minv) {
                    minv = error2;
                    mini = remove;
                }
            //}
        }
        printf("%d\n", mini);
    }
}
