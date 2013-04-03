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

bool isPrime(int n)
{
    if (n < 2) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int solve(int n)
{
    static double A[100];
    int cnt = 0;
    for (int i = 2; cnt < n; i++) {
        if (isPrime(i)) {
            A[cnt++] = i;
        }
    }
    double ans = 1e300;
    unsigned long long ansi = 0;
    for (int i = 0; i < 1 << n - 1; i++) {
        double a = 1, b = 1;
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) {
                a *= A[j];
            } else {
                b *= A[j];
            }
        }
        double v = abs(a - b);
        if (v < ans) {
            ans = v;
            ansi = i;
        }
    }
    return ansi;
}

int main()
{
    for (int i = 1; i <= 30; i++) {
        cerr << i << endl;
        cout << solve(i) << ",";
    }
}
