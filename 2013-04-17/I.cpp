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

const int maxn = 111111;

int getint()
{
    char ch;
    while (!isdigit(ch = getchar()));
    int ret = 0;
    do {
        ret = ret * 10 + ch - '0';
    } while (isdigit(ch = getchar()));
    return ret;
}

int n;
int a[maxn];
char str[maxn];

bool isRD(char ch)
{
    return ch == 'R' || ch == 'D';
}

void readStr()
{
    int len = 0;
    char ch;
    while (!isRD(ch = getchar()));
    do {
        str[len ++] = ch;
    } while (isRD(ch = getchar()));
    str[len] = 0;
}

int main()
{
    int tests = getint();
    while (tests --) {
        readStr();
        n = getint();
        for (int i = 0; i < n; i++) {
            a[i] = getint();
        }
        int l = 0, r = n - 1;
        bool rev = false;
        for (int i = 0; str[i]; i++) {
            if (str[i] == 'R') {
                rev = !rev;
            } else {
                if (rev) {
                    r --;
                } else {
                    l ++;
                }
            }
        }
        if (l > r + 1) {
            puts("error");
        } else {
            if (rev) {
                reverse(a + l, a + r + 1);
            }
            putchar('[');
            for (int i = l; i <= r; i++) {
                if (i > l) {
                    putchar(',');
                }
                printf("%d", a[i]);
            }
            puts("]");
        }
    }
}
