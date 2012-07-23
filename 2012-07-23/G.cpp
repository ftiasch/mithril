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

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

const int MAXS = 64;
const int MAXN = 1024;

int height, width;
int n;
int src, dest;
int grid[MAXS][MAXS];

bool visited[MAXN][MAXN][4][4];
int adj[MAXN][4];

int main()
{
    scanf("%d%d", &width, &height);
    n = 0;
    memset(grid, -1, sizeof(grid));
    src = dest = -1;
    for (int i = 0; i < height; i++) {
        char line[MAXS + 1];
        scanf("%s", line);
        for (int j = 0; j < width; j++) {
            if (line[j] == '#') {
                continue;
            }
            grid[i][j] = n ++;
            if (line[j] == 'M') {
                src = grid[i][j];
            } else if (line[j] == 'K') {
                dest = grid[i][j];
            }
        }
    }
    assert(src >= 0 && dest >= 0);
    memset(adj, -1, sizeof(adj));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] >= 0) {
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni < 0 || ni >= height || nj < 0 || nj >= width)
                        continue;
                    if (grid[ni][nj] < 0)
                        continue;
                    adj[grid[i][j]][k] = grid[ni][nj];
                }
            }
        }
    }
    memset(visited, false, sizeof(visited));
    queue<int> Q;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (adj[src][(j + 2) & 3] < 0) {
                if (adj[src][i] >= 0) {
                    visited[src][src][i][j] = true;
                    Q.push(src | src << 10 | i << 20 | j << 22);
                }
            }
        }
    }
    bool find1 = false, find2 = false;
    while (!Q.empty()) {
        int x = Q.front() & 1023;
        int y = Q.front() >> 10 & 1023;
        int zx = Q.front() >> 20 & 3;
        int zy = Q.front() >> 22 & 3;
        if (y == dest && adj[y][(zy + 2) & 3] >= 0) {
            find1 = true;
            if (x == dest && adj[x][zx] < 0) {
                find2 = true;
            }
        }
        Q.pop();
        for (int delta = -1; delta <= 1; delta += 2) {
            int nzx = (zx + delta) & 3;
            int nzy = (zy + delta) & 3;
            if (adj[x][zx] < 0 && adj[y][(nzy + 2) & 3] < 0) {
                if (!visited[x][y][nzx][nzy]) {
                    visited[x][y][nzx][nzy] = true;
                    Q.push(x | y << 10 | nzx << 20 | nzy << 22);
                }
            }
        }
        if (adj[x][zx] >= 0) {
            int nx = adj[x][zx];
            if (!visited[nx][y][zx][zy]) {
                visited[nx][y][zx][zy] = true;
                Q.push(nx | y << 10 | zx << 20 | zy << 22);
            }
        }
        if (adj[y][zy] >= 0) {
            int ny = adj[y][zy];
            if (!visited[x][ny][zx][zy]) {
                visited[x][ny][zx][zy] = true;
                Q.push(x | ny << 10 | zx << 20 | zy << 22);
            }
        }
    }
    if (find2) {
        puts("He can accomplish his mission.");
    } else if (find1) {
        puts("He cannot return to the kitchen.");
    } else {
        puts("He cannot bring tea to his master.");
    }
}
