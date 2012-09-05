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

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        int n;
        scanf("%d", &n);
        long long delta = 0;
        while (true) {
            long long m = n + (long long)sqrt((long long)n + delta);
            if (n + delta == m) {
                break;
            }
            delta = m - n;
        }
        long long m = (long long)n + delta;
        long long sqrtm = (long long)sqrt(m);
        long long ans = m * sqrtm;
        ans -= sqrtm * (sqrtm + 1) * (2 * sqrtm + 1) / 6;
        ans += sqrtm;
        cout << m << " " << ans << endl;
    }
}
