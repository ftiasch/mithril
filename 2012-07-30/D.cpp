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

const int maxn = 2048;

long long comb[maxn][maxn];

int readDouble()
{
    double a;
    scanf("%lf", &a);
    return (int)(a * 100000 + 0.5);
}

int solve(long long a, long long b, long long x)
{
    if (a > b) {
        swap(a, b);
    }
    if (x <= 0) {
        return 0;
    }
    if (x <= a) {
        return 1;
    }
    int ans = 1;
    if (x >= b) {
        long long b_remain = x % b;
        while (b_remain + b <= a) {
            b_remain += b;
        }
        if (b_remain > 0 && b_remain <= a) {
            ans ++;
        }
    }
    for (int i = 1; i < maxn; i++) {
        long long nx = x - a * i;
        if (nx <= a) {
            break;
        }
        int j = (nx - a) / b;
        while (nx - b * j > a) {
            j ++;
        }
        if (j == 0) {
            break;
        }
        if (nx - b * j > 0) {
            ans += comb[i + j][i];
        }
    }
    return ans;
}

int main()
{
    for (int i = 0; i < maxn; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++) {
            comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
        }
    }
    int a = readDouble();
    int b = readDouble();
    int x = readDouble();
    printf("%d\n", solve(a, b, x));
}
