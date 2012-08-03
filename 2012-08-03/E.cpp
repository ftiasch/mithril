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

const int maxn = 50;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const char ds[] = "DURL";

int prev[maxn][maxn][maxn][maxn];
int dist[maxn][maxn][maxn][maxn];

int n, m;

char grid[maxn][maxn + 10];

inline void move(int x, int y, int k, int &nx, int &ny)
{
    nx = x + dx[k];
    ny = y + dy[k];
    if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
        if (grid[nx][ny] != '#') {
            return;
        }
    }
    nx = x;
    ny = y;
}

int main()
{
    scanf("%d%d", &n, &m);
    int x1 = -1, x2 = -1, y1 = -1, y2 = -2;
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '1') {
                x1 = i;
                y1 = j;
            } else if (grid[i][j] == '2') {
                x2 = i;
                y2 = j;
            }
        }
    }
    memset(dist, -1, sizeof(dist));
    memset(prev, -1, sizeof(prev));
    dist[x1][y1][x2][y2] = 0;
    queue<int> Q;
    Q.push(x1 << 18 | y1 << 12 | x2 << 6 | y2);
    int ans = -1;
    while (!Q.empty()) {
        int key = Q.front();
        Q.pop();
        x1 = key >> 18 & 63;
        y1 = key >> 12 & 63;
        x2 = key >> 6 & 63;
        y2 = key & 63;
        if (grid[x1][y1] == '*' && grid[x2][y2] == '*') {
            ans = dist[x1][y1][x2][y2];
            break;
        }
        for (int k = 0; k < 4; k++) {
            int nx1, ny1;
            move(x1, y1, k, nx1, ny1);
            int nx2, ny2;
            move(x2, y2, k, nx2, ny2);
            if (dist[nx1][ny1][nx2][ny2] < 0) {
                dist[nx1][ny1][nx2][ny2] = dist[x1][y1][x2][y2] + 1;
                prev[nx1][ny1][nx2][ny2] = key | k << 24;
                Q.push(nx1 << 18 | ny1 << 12 | nx2 << 6 | ny2);
            }
        }
    }
    printf("%d\n", ans);
    if (ans >= 0) {
        string ansS = "";
        while (true) {
            int key = prev[x1][y1][x2][y2];
            if (key < 0) {
                break;
            }
            x1 = key >> 18 & 63;
            y1 = key >> 12 & 63;
            x2 = key >> 6 & 63;
            y2 = key & 63;
            ansS += ds[key >> 24];
        }
        reverse(ansS.begin(), ansS.end());
        puts(ansS.c_str());
    }
}
