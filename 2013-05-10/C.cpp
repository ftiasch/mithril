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

long long solve(int a, int b, bool flag = true)
{
    long long n = 1, m = 1, last = -1;
    if (flag && a != b) {
        n = m = max(1, min(a, b) / abs(a - b) - 10);
    }
    while (true) {
        if (n * a == m * b) {
            break;
        } if (n * a > m * b) {
            if (last == 1) {
                break;
            }
            last = 1;
            m ++;
        } else {
            if (last == 0) {
                break;
            }
            last = 0;
            n ++;
        }
    }
    long long ret = 0;
    ret += n * (n + 1);
    ret += m * (m + 1);
    return ret;
}

int main()
{
    int a, b;
    /*while (true) {
        a = (unsigned)rand() % 100 + 1;
        b = (unsigned)rand() % 100 + 1;
        long long ans1 = solve(a, b, false);
        long long ans2 = solve(a, b, true);
        cout << a << " " << b << " " << ans1 << " " << ans2 << endl;
        if (ans1 != ans2) {
            break;
        }
    }*/
    scanf("%d%d", &a, &b);
    cout << solve(a, b) << endl;
}
