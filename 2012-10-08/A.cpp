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

const int maxn = 1 << 20;

int h[maxn];
int H, n;

int main()
{
    freopen("alpinism.in", "r", stdin);
    freopen("alpinism.out", "w", stdout);
    scanf("%d%d", &H, &n);
    h[n + 1] = H;
    h[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", h + i);
    }
    double len = 0;
    for (int j = 0; j <= n; j++) {
        double L = h[j + 1] - h[j];
        len += max(0.0, L - len / 2.0);
    }
    printf("%.20f\n", len);
}
