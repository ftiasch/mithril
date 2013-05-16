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

const int maxn = 1024;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int n, m;
char input[2][maxn][maxn];
int s, t;

int dist[2 << 20];

int main()
{
#define ID(a, b, c) ((a) << 20 | (b) << 10 | (c))
    scanf("%d%d", &n, &m);
    s = -1, t = -1;
    for (int u = 0; u < 2; u++) {
        for (int i = 0; i < n; i++) {
            scanf("%s", input[u][i]);
            if (u == 1) {
                reverse(input[u][i], input[u][i] + m);
            }
            for (int j = 0; j < m; j++) {
                if (input[u][i][j] == 'D') {
                    s = ID(u, i, j);
                } else if (input[u][i][j] == 'K') {
                    t = ID(u, i, j);
                }
            }
        }
    }
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int p = Q.front();
        int u = p >> 20;
        int x = p >> 10 & 1023;
        int y = p & 1023;
        Q.pop();
        for (int k = 0; k < 4; k++) {
            int nu = u;
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (0 <= nx && nx < n) {
                if (ny < 0 || ny >= m) {
                    if (ny < 0) {
                        ny = m - 1;
                    } else {
                        ny = 0;
                    }
                    nx = n - 1 - nx;
                    nu = 1 - nu;
                }
            } else {
                continue;
                /*nu = 1 - nu;
                nx = x;
                ny = y;*/
            }
            if (input[nu][nx][ny] == '*') {
                continue;
            }
            int q = ID(nu, nx, ny);
            if (dist[q] < 0) {
                dist[q] = dist[p] + 1;
                Q.push(q);
            }
        }
    }
    printf("%d\n", dist[t]);
}
