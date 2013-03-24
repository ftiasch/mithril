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

const int lcm = 720;

int n, a[5];

typedef vector<long long> poly;

poly operator*(const poly &a, const poly &b)
{
    poly ret(a.size() + b.size() - 1, 0);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            ret[i + j] += a[i] * b[j];
        }
    }
    return ret;
}

poly integrate(const poly &a)
{
    poly ret(a.size() + 1);
    ret[0] = 0;
    for (int i = 0; i < a.size(); i++) {
        ret[i + 1] = a[i] / (i + 1);
    }
    return ret;
}

long long evaluate(const poly &a, long long v)
{
    long long ret = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        ret = ret * v + a[i];
    }
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    sort(a, a + n);
    poly num(1, lcm);
    long long den = lcm;
    for (int i = 0; i < n; i++) {
        den *= a[i];
        poly factor(2);
        factor[1] = -1;
        factor[0] = a[i];
        num = num * factor;
    }
    num = integrate(num);
    long long numV = evaluate(num, a[0]) - evaluate(num, 0);
    long long g = __gcd(numV, den);
    cout << numV / g << "/" << den / g << endl;
}
