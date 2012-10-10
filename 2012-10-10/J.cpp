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
const double pi = acos(-1.0);

struct Complex {
    double x, y;

    Complex(double x = 0, double y = 0) : x(x), y(y) {}
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
        sincos(p0, &unit_p0.y, &unit_p0.x);
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

const int MOD = 1000;
const int MAXB = 1 << 18;

struct BigInt
{
    vector<int> digits;

    BigInt(int a = 0) : digits(1, a) {
        normalize();
    }

    BigInt(const char *str) {
        int len = strlen(str);
        int now = 1;
        digits.clear();
        for (int i = len - 1; i >= 0; i--) {
            if (now == 1) {
                digits.push_back(0);
            }
            digits.back() += now * (str[i] - '0');
            if ((now *= 10) == MOD) {
                now = 1;
            }
        }
    }
    
    BigInt &normalize() {
        int carry = 0;
        for (int i = 0; i < digits.size() || carry; i++) {
            if (i == digits.size()) {
                digits.push_back(0);
            }
            digits[i] += carry;
            carry = digits[i] / MOD;
            digits[i] %= MOD;
            while (digits[i] < 0) {
                digits[i] += MOD;
                carry --;
            }
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    BigInt &operator+=(const BigInt &o) {
        if (digits.size() < o.digits.size()) {
            digits.resize(o.digits.size(), 0);
        }
        for (int i = 0; i < o.digits.size(); i++) {
            digits[i] += o.digits[i];
        }
        return normalize();
    }

    BigInt &operator-=(const BigInt &o) {
        if (digits.size() < o.digits.size()) {
            digits.resize(o.digits.size(), 0);
        }
        for (int i = 0; i < o.digits.size(); i++) {
            digits[i] -= o.digits[i];
        }
        return normalize();
    }

    BigInt &div2() {
        int carry = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            digits[i] += carry * MOD;
            carry = digits[i] & 1;
            digits[i] >>= 1;
        }
        return normalize();
    }

    BigInt operator*(const BigInt &o) {
        BigInt ret;
        ret.digits.resize(digits.size() + o.digits.size() - 1);
        int len = 1;
        while (len < ret.digits.size()) {
            len *= 2;
        }
        static Complex A[MAXB], B[MAXB], C[MAXB];
        for (int i = 0; i < len; i++) {
            A[i] = i < digits.size() ? digits[i] : 0;
            B[i] = i < o.digits.size() ? o.digits[i] : 0;
        }
        FFT(A, len, 1);
        FFT(B, len, 1);
        for (int i = 0; i < len; i++) {
            C[i] = A[i] * B[i];
        }
        FFT(C, len, -1);
        long long carry = 0;
        for (int i = 0; i < ret.digits.size(); i++) {
            long long now = carry + (long long)(C[i].x / len + 0.5);
            ret.digits[i] = now % MOD;
            carry = now / MOD;
        }
        while (carry) {
            ret.digits.push_back(carry % MOD);
            carry /= MOD;
        }
        return ret.normalize();
    }

    BigInt operator+(const BigInt &o) const {
        BigInt ret = *this;
        return ret += o;
    }

    BigInt operator-(const BigInt &o) const {
        BigInt ret = *this;
        return ret -= o;
    }

    void show() {
        printf("%d", digits.back());
        for (int i = (int)digits.size() - 2; i >= 0; i--) {
            printf("%03d", digits[i]);
        }
    }
};

char str[MAXB];

int main()
{
    freopen("theorem.in", "r", stdin);
    freopen("theorem.out", "w", stdout);
    scanf("%s", str);
    if (strcmp(str, "2") == 0 || strcmp(str, "1") == 0) {
        puts("I'm sorry, Hexy");
        return 0;
    }
    BigInt a(str), b;
    if (a.digits[0] & 1) {
        b = 1;
        a = a * a;
    } else {
        b = 2;
        a = a * a;
        a.div2();
    }
    BigInt c = a - b;
    c.div2();
    c.show();
    putchar(' ');
    c = a + b;
    c.div2();
    c.show();
    puts("");
}
