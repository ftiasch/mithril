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

const double pi = acos(-1.0);

typedef complex<double> Complex;

void FFT(Complex P[], int n, int oper)
{
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }
    Complex unit_p0;
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        double p0 = pi / m * oper;
        sincos(p0, &unit_p0.imag(), &unit_p0.real());
        for (int i = 0; i < n; i += m2) {
            Complex unit = 1;
            for (int j = 0; j < m; j++) {
                Complex &P1 = P[i + j + m], &P2 = P[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
}

const int maxn = 1 << 18;

int n;
char str[maxn];

Complex a[maxn];

int main()
{
    scanf("%s", str);
    n = strlen(str);
    for (int i = 0; i < maxn; i++) {
        a[i] = i < n && str[i] == '1' ? 1 : 0;
    }
    FFT(a, maxn, 1);
    for (int i = 0; i < maxn; i++) {
        a[i] = a[i] * a[i];
    }
    FFT(a, maxn, -1);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == '1') {
            sum += (int)(a[i * 2].real() / maxn + 0.5) - 1;
        }
    }
    cout << sum / 2 << endl;
}
