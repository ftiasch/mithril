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

const int N = 100;

int match[N];

bool check(int n, char *str)
{
    return true;
    memcpy(str + n, str, sizeof(char) * n);
    match[0] = 0;
    int j = 0;
    for (int i = 1; i < n; ++ i) {
        match[i] = j + match[j] - 1 >= i ? min(match[i - j], j + match[j] - i) : 0;
        while (i + match[i] < n << 1 && str[match[i]] == str[i + match[i]]) {
            match[i] ++;
        }
        if (match[i] >= n || str[match[i]] > str[i + match[i]]) {
            return false;
        }
        if (match[i] + i > match[j] + j) {
            j = i;
        }
    }
    return true;
}

int n, m, l, r;

int len;
char str[1 << 10];

int main()
{
    int cas = 0;
    while (scanf("%d%d%d%d", &n, &m, &l, &r) == 4) {
        printf("Case %d:\n", ++cas);
        str[0] = 'a';
        len = 1;
        for (int id = 1; id <= r; id++) {
            if (id >= l) {
                str[len] = 0;
                puts(str);
            }
            if (id < r) {
                do {
                    for (int i = len; i < n; i++) {
                        str[i] = str[i % len];
                    }
                    len = n;
                    while (len > 0 && str[len - 1] == 'a' + m - 1) {
                        len --;
                    }
                    assert(len > 0);
                    str[len - 1] ++;
                } while (!check(len, str));
            }
        }
    }
}
