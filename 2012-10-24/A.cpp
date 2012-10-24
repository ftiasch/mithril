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

const int maxn = 222222;

long long a[maxn], a0[maxn], a1[maxn];
long long ways[maxn], nways[maxn];
int n;

long long readLong()
{
    char ch;
    while (!isdigit(ch = getchar()));
    long long ret = 0;
    do {
        ret = ret * 10 + (ch - '0');
    } while (isdigit(ch = getchar()));
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        a[i] = readLong();
    }
    sort(a, a + n);
    long long xorSum = 0;
    for (int i = 0; i < n; i++) {
        xorSum ^= a[i] - a[0];
    }
    memset(ways, 0, sizeof(ways));
    ways[0] = 1;
    while (*max_element(a, a + n) > 0) {
        memset(nways, 0, sizeof(nways));
        int a0sz = 0, a1sz = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] & 1) {
                a1[a1sz++] = a[i];
            } else {
                a0[a0sz++] = a[i];
            }
        }
        int less0 = 0, less1 = 0;
        for (int i = 0; i <= n; i++) {
            int numOne = (a1sz - less1) + less0;
            // lowest bit is 0
            if (numOne % 2 == 0) {
                nways[less0] += ways[i];
            }
            // lowest bit is 1
            if ((n - numOne) % 2 == 0) {
                nways[a0sz + less1] += ways[i];
            }
            if (i < n) {
                if (a[i] == 0) {
                    break;
                }
                if (a[i] & 1) {
                    less1 ++;
                } else {
                    less0 ++;
                }
            }
        }
        memcpy(ways, nways, sizeof(nways));
        int sz = 0;
        for (int i = 0; i < a0sz; i++) {
            a[sz++] = a0[i] >> 1;
        }
        for (int i = 0; i < a1sz; i++) {
            a[sz++] = a1[i] >> 1;
        }
    }
    long long ret = ways[0];
    if (xorSum == 0) {
        ret --;
    }
    cout << ret << endl;
}
