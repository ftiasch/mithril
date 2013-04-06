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
int a[1 << 20];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; i++) {
        scanf("%d", a + i);
    }
    int lo = 1;
    if (n == 0 && a[1] == 1) {
        lo = 1;
    } else if (a[1] == 0) {
        lo = 2;
    } else {
        lo = 0;
    }
    printf("%d\n", n - lo + 1);
    for (int i = lo; i <= n + 1; i++) {
        if (i > lo) {
            putchar(' ');
        }
        printf("%d", a[i]);
    }
    puts("");
}
