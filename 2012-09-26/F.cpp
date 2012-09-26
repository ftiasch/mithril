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

const int maxn = 10;
const int inf = 1000000000;

int n;

bool onSeaside[maxn];
int dist[maxn][maxn];

int main()
{
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = i == j ? 0 : inf;
            }
        }
        for (int i = 0; i < n; i++) {
            int mi, pi;
            scanf("%d%d", &mi, &pi);
            onSeaside[i] = pi != 0;
            for (int j = 0; j < mi; j++) {
                int si, li;
                scanf("%d%d", &si, &li);
                dist[i][si] = min(dist[i][si], li);
            }
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        int ans = inf;
        for (int i = 0; i < n; i++) {
            if (onSeaside[i]) {
                ans = min(ans, dist[0][i]);
            }
        }
        printf("%d\n", ans);
    }
}
