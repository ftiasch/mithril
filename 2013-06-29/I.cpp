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

const int maxn = 555555;

int n, W;
int len[maxn];
long long psum[maxn];

inline long long getLen(int gap, int l, int r)
{
    return psum[r] - psum[l] + (r - l - 1) * (long long)gap;
}

int delta[maxn];

bool check(int gap)
{
    if (getLen(gap, 0, n) <= W) {
        return true;
    }
    int okay = 0;
    memset(delta, 0, sizeof(delta));
    delta[0] ++;
    delta[1] --;
    int ptr1 = 0, ptrG = 0;
    for (int i = 0; i < n; i++) {
        okay += delta[i];
        if (okay) {
            ptr1 = max(ptr1, i + 1);
            while (ptr1 < n && getLen(1, i, ptr1 + 1) <= W) {
                ptr1 ++;
            }
            ptrG = max(ptrG, i + 1);
            while (ptrG < n && getLen(gap, i, ptrG) < W) {
                ptrG ++;
            }
            assert(ptrG <= ptr1 + 1);
            if (ptr1 == n) {
                return true;
            }
            delta[ptrG] ++;
            delta[ptr1 + 1] --;
        }
    }
    return false;
}

int main()
{
    while (scanf("%d%d", &W, &n) == 2 && W) {
        psum[0] = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &len[i]);
            psum[i + 1] = psum[i] + len[i];
        }
        int lo = 1, hi = W;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (check(mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        printf("%d\n", lo);
    }
}
