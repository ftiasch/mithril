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

const int inf = 1000000000;

int main()
{
    int n, t1, t2;
    cin >> n >> t1 >> t2;
    int lo = 0, hi = inf;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (mid / t1 + mid / t2 >= n) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    int num = lo / t1 + lo / t2;
    int tm = lo;
    if (lo % t1) {
        num ++;
        tm = max(tm, (lo / t1 + 1) * t1);
    }
    if (lo % t2) {
        num ++;
        tm = max(tm, (lo / t2 + 1) * t2);
    }
    cout << num << " " << tm << endl;
}
