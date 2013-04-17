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

int n;
int a[50];

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
        }
        long long ans = 0;
        while (true) {
            int pos = -1;
            for (int i = 0; i + 1 < n; i++) {
                if (a[i + 1] < a[i]) {
                    pos = i + 1;
                    break;
                }
            }
            if (pos < 0) {
                break;
            }
            int inspos = lower_bound(a, a + pos, a[pos]) - a;
            sort(a, a + pos + 1);
            long long innerAns = 1, last = 0;
            for (int i = 0; i + 1 < inspos; i++) {
                if (a[i] == a[i + 1]) {
                    innerAns += 1 + last;
                } else {
                    last = innerAns;
                    innerAns = innerAns * 2 + 1;
                }
            }
            ans += innerAns + (inspos > 0 ? 1 : 0);
//            cerr << ans << endl;
        }
        cout << ans << endl;
    }
}
