#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

const int N = 100;

int n, a, b, p[N], q[N], s[N];

#define foreach(i, v) for (typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

int main() {
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", p + i, q + i, s + i);
    }
    vector <long double> zeros(1, 0.0);
    for (int i = 0; i < n; ++ i) {
        zeros.push_back((long double)p[i] / s[i]);
    }
    long double optimum = 1e100;
    long double best;
    foreach (iter, zeros) {
        long double x = *iter;
        long double value = b * x;
        for (int i = 0; i < n; ++ i) {
            value += a * max(p[i] - s[i] * x, (long double)0.0) / q[i];
        }
        if (value < optimum) {
            best = x;
            optimum = value;
        }
    }
    printf("%.20f\n%.20f\n", (double)optimum, (double)best);
    for (int i = 0; i < n; ++ i) {
        printf("%.20f%c", (double)max((p[i] - s[i] * best) / q[i], (long double)0.0), i == n - 1? '\n': ' ');
    }
    return 0;
}
