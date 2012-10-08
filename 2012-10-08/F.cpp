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

#define double long double

const int maxb = 1 << 18;
const double pi = acos(-1.);

struct Complex {
    double x, y;

    inline Complex(double real = 0, double imag = 0) : x(real), y(imag) {}

    inline double &real() {
        return x;
    }

    inline double &imag() {
        return y;
    }
};

inline Complex operator+(const Complex &a, const Complex &b)
{
    return Complex(a.x + b.x, a.y + b.y);
}

inline Complex operator-(const Complex &a, const Complex &b)
{
    return Complex(a.x - b.x, a.y - b.y);
}

inline Complex operator*(const Complex &a, const Complex &b)
{
    return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

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
        sincosl(p0, &unit_p0.y, &unit_p0.x);
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

vector<int> mul(const vector<int> &a, const vector<int> &b, int mod)
{
    static Complex A[maxb], B[maxb], C[maxb];
    vector<int> res(a.size() + b.size() - 1);
    int len = 1;
    while (len <= res.size()) {
        len *= 2;
    }
    for (int i = 0; i < len; i++) {
        A[i] = i < a.size() ? a[i] : 0;
        B[i] = i < b.size() ? b[i] : 0;
    }
    FFT(A, len, 1);
    FFT(B, len, 1);
    for (int i = 0; i < len; i++) {
        C[i] = A[i] * B[i];
    }
    FFT(C, len, -1);
    for (int i = 0; i < res.size(); i++) {
        res[i] = (long long)(C[i].real() / len + 0.5) % mod;
    }
    return res;
}

vector<int> solve(int mod, int l, int r)
{
    if (l == r) {
        vector<int> res;
        res.push_back(l);
        res.push_back(1);
        return res;
    }
    int mid = (l + r) / 2;
    return mul(solve(mod, l, mid), solve(mod, mid + 1, r), mod);
}

int main()
{
    freopen("polynomial.in", "r", stdin);
    freopen("polynomial.out", "w", stdout);
    int m;
    cin >> m;
    if (m == 1) {
        puts("1");
        puts("1 0");
        return 0;
    }
    vector<int> res = solve(m, 1, m - 1);
    printf("%d\n", m);
    for (int i = 0; i < res.size(); i++) {
        printf("%d ", res[res.size() - 1 - i]);
    }
    puts("0");
}
