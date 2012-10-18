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

long long solve(long long n, long long a, long long b, long long m)
{
    if (b == 0) {
        return n * (a / m);
    }
    if (a >= m) {
        return n * (a / m) + solve(n, a % m, b, m);
    }
    if (b >= m) {
        return (n - 1) * n / 2 * (b / m) + solve(n, a, b % m, m);
    }
    long long q = (a + b * n) / m;
    return solve(q, (a + b * n) % m, m, b);
}

int main()
{
    int p, q;
    cin >> p >> q;
    if (__gcd(p, q) > 1) {
        puts("infinity infinity");
    } else {
        printf("%lld %lld\n", solve(q, 0, p, q), (long long)p * q - p - q);
    }
}
