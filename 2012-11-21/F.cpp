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

const int maxn = 1 << 20;

int st[maxn * 4];
int sp;

int main()
{
    int n;
    scanf("%d", &n);
    sp = 0;
    while (n --) {
        int x;
        scanf("%d", &x);
        if (x < 0) {
            assert(sp > 0);
            printf("%d\n", st[--sp]);
        } else if (x == 0) {
            if (sp < maxn) {
                for (int i = 0; i < sp; i++) {
                    st[sp + i] = st[i];
                }
                sp *= 2;
            }
        } else {
            st[sp++] = x;
        }
    }
}
