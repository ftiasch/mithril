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

bool solve(int n)
{
    int cnt = 0;
    while (n % 2 == 0) {
        cnt ++;
        n /= 2;
    }
    if (n == 1) {
        return cnt % 2 == 1;
    }
    if ((cnt + 1) % 2 == 1) {
        return true;
    }
    if (!isPrime(n) && (cnt + 2) % 2 == 1) {
        return true;
    }
    return false;
}

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        int n;
        scanf("%d", &n);
        puts(solve(n) ? "YES" : "NO");
    }
}
