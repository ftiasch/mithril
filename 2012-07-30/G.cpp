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

const int maxn = 256;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int distR[maxn][maxn], distS[maxn][maxn];
char grid[maxn][maxn];

int n, m;
int rx, ry, sx, sy;

void bfs(int x, int y, int dist[maxn][maxn])
{
    memset(dist, -1, sizeof(distR));
    dist[x][y] = 0;
    queue<pair<int,int> > Q;
    Q.push(make_pair(x, y));
    while (!Q.empty()) {
        int px = Q.front().first;
        int py = Q.front().second;
        Q.pop();
        for (int k = 0; k < 4; k++) {
            int qx = px + dx[k];
            int qy = py + dy[k];
            if (0 <= qx && qx < n && 0 <= qy && qy < m) {
                if (grid[qx][qy] == 'B') {
                    continue;
                }
                if (dist[qx][qy] < 0) {
                    dist[qx][qy] = dist[px][py] + 1;
                    Q.push(make_pair(qx, qy));
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'R') {
                rx = i;
                ry = j;
            } else if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            }
        }
    }
    bfs(rx, ry, distR);
    bfs(sx, sy, distS);
    int dist = distR[sx][sy];
    if (dist < 0) {
        puts("2");
        return 0;
    }
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (distR[i][j] < 0 || distS[i][j] < 0) {
                continue;
            }
            if (distR[i][j] + distS[i][j] != dist) {
                continue;
            }
            int diff = distR[i][j] - distS[i][j];
            if (diff == 0) {
                cnt0 ++;
            } else if (diff == 1) {
                cnt1 ++;
            } else if (diff == -1) {
                cnt2 ++;
            }
        }
    }
    puts((dist % 2 == 0 ? cnt0 > 1 : cnt1 > 1 && cnt2 > 1) ? "2" : "1");
}
