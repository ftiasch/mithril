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

const int maxn = 300;
const long long inf = 1LL << 60;

long long dist[maxn][maxn];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = i == j ? 0 : inf;
        }
    }
    for (int i = 0; i < m; i++) {
        int ai, bi, ci;
        scanf("%d%d%d", &ai, &bi, &ci);
        long long cost = (long long)ci << 10 | 1;
        ai --, bi --;
        dist[ai][bi] = min(dist[ai][bi], cost);
        dist[bi][ai] = min(dist[bi][ai], cost);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int sum = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            sum += dist[i][j] & 1023;
            cnt ++;
        }
    }
    printf("%.10f\n", (double)sum / cnt);
}
