#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <iostream>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()
#define SIZE(v) (int)(v).size()
#define UNIQUE(v) sort(ALL(v)); (v).erase(std::unique(ALL(v)), (v).end())
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

int n, m, k;
std::vector <int> rows, columns, diagonals;

inline int count(std::vector <int> &values, int l, int r) { // [l, r)
    return std::lower_bound(ALL(values), r) - std::lower_bound(ALL(values), l);
}

const double PI = acos(-1.0);

const int N = 1 << 17;

struct Complex {
    double x, y;

    Complex(double x = 0, double y = 0) : x(x), y(y) {
    }

    Complex operator +(const Complex &o) {
        return Complex(x + o.x, y + o.y);
    }

    Complex operator -(const Complex &o) {
        return Complex(x - o.x, y - o.y);
    }

    Complex operator*(const Complex &o) {
        return Complex(x * o.x - y * o.y, 
                       x * o.y + y * o.x);
    }
};

void FFT(Complex P[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; ++ i) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            std::swap(P[i], P[j]);
        }
    }
    Complex unit_p0;
    for (int d = 0; 1 << d < n; ++ d) {
        int m = 1 << d, m2 = m << 1;
        double p0 = PI / m * oper;
        sincos(p0, &unit_p0.y, &unit_p0.x);
        for (int i = 0; i < n; i += m2) {
            Complex unit = 1;
            for (int j = 0; j < m; ++ j) {
                Complex &P1 = P[i + j + m];
                Complex &P2 = P[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
}

Complex a[N], b[N], c[N];

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        rows.clear();
        columns.clear();
        diagonals.clear();
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < k; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            x --, y --;
            rows.push_back(x);
            columns.push_back(y);
            diagonals.push_back(x - y);
        }
        UNIQUE(rows);
        UNIQUE(columns);
        UNIQUE(diagonals);
        long long answer = (long long)n * m;
        answer -= (long long)SIZE(rows) * m;
        answer -= (long long)SIZE(columns) * n;
        answer += (long long)SIZE(rows) * SIZE(columns);
        int sz = 1;
        while (sz <= n + m) {
            sz *= 2;
        }
        memset(a, 0, sizeof(*a) * sz);
        memset(b, 0, sizeof(*b) * sz);
        foreach (iter, rows) {
            a[*iter] = 1;
        }
        foreach (iter, columns) {
            b[m - 1 - *iter] = 1;
        }
        FFT(a, sz, 1);
        FFT(b, sz, 1);
        for (int i = 0; i < sz; ++ i) {
            c[i] = a[i] * b[i];
        }
        FFT(c, sz, -1);
        foreach (iter, diagonals) {
            int d = *iter;
            answer -= std::max(0, std::min(d + m, n) - std::max(d, 0));
            answer += count(rows, d, d + m);
            answer += count(columns, -d, n - d);
            int x = d + m - 1;
            int ways = c[x].x / (double)sz + 0.5;
            answer -= ways;
        }
        std::cout << "Case " << t << ": " << answer << std::endl;
    }
    return 0;
}
