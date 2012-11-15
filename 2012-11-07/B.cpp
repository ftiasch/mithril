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

const int maxn = 100;
const int maxl = 1024 >> 5;

unsigned bits[maxn + 1][maxl];
unsigned all[maxl];

void touch(unsigned *bits, int a, int b)
{
    static char buf[1024];
    if (b < 0) {
        sprintf(buf, "%d", a);
    } else {
        sprintf(buf, "%d%d", a, b);
    }
    int len = strlen(buf);
    sort(buf, buf + len);
    if (unique(buf, buf + len) != buf + len) {
        return;
    }
    int mask = 0;
    for (int i = 0; i < len; i++) {
        mask |= 1 << (buf[i] - '0');
    }
    for (int nmask = 0; nmask < 1024; nmask++) {
        if ((nmask & mask) == mask) {
            bits[nmask >> 5] |= 1 << (nmask & 31);
        }
    }
}

bool better(int a, int b)
{
    int bitsA = __builtin_popcount(a);
    int bitsB = __builtin_popcount(b);
    if (bitsA != bitsB) {
        return bitsA < bitsB;
    }
    return a < b;
}

int main()
{
    for (int n = 1; n <= maxn; n++) {
        touch(bits[n], n, -1);
        for (int i = 1; i < n - i; i++) {
            touch(bits[n], i, n - i);
        }
    }
    int n, cas = 0;
    while (scanf("%d", &n) == 1 && n) {
        memset(all, -1, sizeof(all));
        for (int i = 0; i < n; i++) {
            int age;
            scanf("%d", &age);
            for (int j = 0; j < maxl; j++) {
                all[j] &= bits[age][j];
            }
        }
        int best = -1;
        for (int i = 0; i < 1024; i++) {
            if (all[i >> 5] >> (i & 31) & 1) {
                if (best < 0 || better(i, best)) {
                    best = i;
                }
            }
        }
        printf("Case %d: ", ++cas);
        for (int i = 9; i >= 0; i--) {
            if (best >> i & 1) {
                putchar('0' + i);
            }
        }
        cout << endl;
    }
}
