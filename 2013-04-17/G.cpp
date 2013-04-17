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

const int maxn = 155;

int n;
int s[maxn];
double p[maxn];

double opt[maxn][maxn];

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%lf", s + i, p + i);
            p[i] *= 0.01;
        }
        memset(opt, 0, sizeof(opt));
        opt[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= 150; j++) {
                opt[i + 1][j] = max(opt[i + 1][j], opt[i][j]);
                opt[i + 1][j + s[i]] = max(opt[i + 1][j + s[i]], opt[i][j] * p[i]);
            }
        }
        double ans = 0;
        for (int i = 76; i <= 150; i++) {
            ans = max(ans, opt[n][i]);
        }
        printf("%.10f\n", ans * 100);
    }
}
