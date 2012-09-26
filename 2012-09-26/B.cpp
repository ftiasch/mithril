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

const int maxn = 1024;

int n, T;
int a[maxn], b[maxn];

int main()
{
    while (scanf("%d%d", &n, &T) == 2) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            sum += a[i];
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", b + i);
            sum += b[i];
        }
        sort(a, a + n);
        sort(b, b + n);
        reverse(b, b + n);
        int minAns = 1 << 30;
        for (int i = 0; i < 10 && i < n; i++) {
            int ptr = i;
            int ans = sum;
            for (int j = 0; j < n; j++) {
                ans -= min(T, a[j] + b[ptr]);
                if (++ptr == n) {
                    ptr = 0;
                }
            }
            minAns = min(minAns, ans);
        }
        printf("%d\n", minAns);
    }
}
