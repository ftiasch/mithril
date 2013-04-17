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

const int maxn = 111;

char str[maxn * maxn];

int main()
{
    int tests;
    scanf("%d", &tests);
    for (int cas = 1; cas <= tests; ++cas) {
        scanf("%s", str);
        int n = 0, len = strlen(str);
        while (n * n < len) {
            n ++;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                putchar(str[j * n + (n - 1 - i)]);
            }
        }
        puts("");
    }
}
