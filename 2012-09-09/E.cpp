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

const int maxn = 1 << 12;

long long n;

long long powers[maxn];

int main()
{
    int input;
    while (scanf("%d", &input) == 1 && input) {
        n = input;
        // k == 2
        int sqrtn = (int)(sqrt((double)n) + 0.5);
        int ans = 0;
        if ((long long)sqrtn * sqrtn == n) {
            for (int x = 1; x + x < sqrtn; x++) {
                ans ++;
            }
        }
        int sz = maxn;
        for (int i = 1; i < sz; i++) {
            powers[i] = i * i;
        }
        for (int k = 3; (1LL << k) <= n; k++) {
            for (int i = 1; i < sz; i++) {
                powers[i] *= i;
                if (powers[i] > n) {
                    sz = i;
                    break;
                }
            }
            int y = sz - 1;
            for (int x = 1; x < sz; x++) {
                while (x < y && powers[x] + powers[y] + (long long)k * x * y > n) {
                    y --;
                }
                if (x < y && powers[x] + powers[y] + (long long)k * x * y == n) {
                    ans ++;
                }
            }
        }
        printf("%d\n", ans);
    }
}

