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

const int MAXN = 1000000;

long long digitCnt[10];

int vis[100];

int main()
{
    long long n = 0;
    for (int i = 0; i < 10; i++) {
        cin >> digitCnt[i];
        n += digitCnt[i];
    }
    int g = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (digitCnt[i] > 0 && digitCnt[j] > 0) {
                g = __gcd(g, j - i);
            }
        }
    }
    g *= 9;
    if (g == 0) {
        if (n > MAXN) {
            puts("TOO LONG");
        } else {
            for (int i = 1; i < 10; i++) {
                for (int j = 0; j < digitCnt[i]; j++) {
                    putchar('0' + i);
                }
            }
            puts("");
        }
    } else {
        int now = 0;
        for (int i = 1; i < 10; i++) {
            memset(vis, -1, sizeof(vis));
            long long steps = digitCnt[i];
            for (long long j = 1; j <= steps; j++) {
                now = (now * 10 + i) % g;
                if (vis[now] >= 0 && (steps - j) % (j - vis[now]) == 0) {
                    break;
                } else {
                    vis[now] = j;
                }
            }
        }
        printf("%d\n", __gcd(now, g));
    }
}
