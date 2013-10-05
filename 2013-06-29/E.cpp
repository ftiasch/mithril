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

const int inf = 1000000000;
const int maxn = 52;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int H, W;
char input[maxn][maxn];
bool empty[maxn][maxn];

inline bool checkValid(int X, int Y, int x, int y)
{
    return 0 <= x && x < H && 0 <= y && y < W && empty[x][y] && (x < X || x > X + 1 || y < Y || y > Y + 1);
}

void bfs(int x, int y, int X, int Y, int dist[maxn][maxn])
{
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            dist[i][j] = inf;
        }
    }
    queue<pair<int,int> > Q;
    if (checkValid(X, Y, x, y)) {
        dist[x][y] = 0;
        Q.push(make_pair(x, y));
    }
    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (checkValid(X, Y, nx, ny) && dist[nx][ny] == inf) {
                dist[nx][ny] = dist[x][y] + 1;
                Q.push(make_pair(nx, ny));
            }
        }
    }
}

vector<pair<int,int> > adj2[maxn][maxn][4];

void solve(int x1, int y1, int x2, int y2, int X, int Y, int dist4[])
{
    static int dist1[maxn][maxn];
    static int dist2[maxn][maxn];
    bfs(x1, y1, X, Y, dist1);
    bfs(x2, y2, X, Y, dist2);
    for (int k = 0; k < 4; k++) {
        const vector<pair<int,int> > &pts = adj2[X][Y][k];
        dist4[k] = inf;
        if (pts.size() == 2) {
            dist4[k] = min(dist4[k], dist1[pts[0].first][pts[0].second] + dist2[pts[1].first][pts[1].second]);
            dist4[k] = min(dist4[k], dist2[pts[0].first][pts[0].second] + dist1[pts[1].first][pts[1].second]);
        }
    }
}

#define CODE(x, y, z) ((x) | (y) << 6 | (z) << 12)

int dist[maxn][maxn][4];

int main()
{
    while (scanf("%d%d", &H, &W) == 2 && H) {
        for (int i = 0; i < H; i++) {
            scanf("%s", input[i]);
        }
        int x1 = -1, y1, x2, y2;
        int X, Y;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                empty[i][j] = input[i][j] != '*';
                if (input[i][j] == '.') {
                    if (x1 < 0) {
                        x1 = i;
                        y1 = j;
                    } else {
                        x2 = i;
                        y2 = j;
                    }
                } else if (input[i][j] == 'X') {
                    X = i - 1;
                    Y = j - 1;
                }
            }
        }
        for (int X = 0; X < H; X++) {
            for (int Y = 0; Y < W; Y++) {
                for (int k = 0; k < 4; k++) {
                    vector<pair<int,int> > &pts = adj2[X][Y][k];
                    pts.clear();
                    for (int mask = 0; mask < 4; mask++) {
                        int nx = dx[k] + X + (mask & 1);
                        int ny = dy[k] + Y + (mask >> 1);
                        if (checkValid(X, Y, nx, ny)) {
                            pts.push_back(make_pair(nx, ny));
                        }
                    }
                }
            }
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                for (int k = 0; k < 4; k++) {
                    dist[i][j][k] = inf;
                }
            }
        }
        solve(x1, y1, x2, y2, X, Y, dist[X][Y]);
        set<pair<int,int> > PQ;
        for (int k = 0; k < 4; k++) {
            if (dist[X][Y][k] < inf) {
                int code = CODE(X, Y, k);
                PQ.insert(make_pair(dist[X][Y][k], code));
            }
        }
        while (!PQ.empty()) {
            int x = PQ.begin()->second & 63;
            int y = PQ.begin()->second >> 6 & 63;
            int z = PQ.begin()->second >> 12;
            PQ.erase(PQ.begin());
            int dist4[4];
            solve(adj2[x][y][z][0].first, adj2[x][y][z][0].second,
                    adj2[x][y][z][1].first, adj2[x][y][z][1].second,
                    x, y, dist4);
            assert(adj2[x][y][z].size() == 2);
            for (int k = 0; k < 4; k++) {
                if (dist4[k] < inf) {
                    int ncode = CODE(x, y, k);
                    int ndist = dist[x][y][z] + dist4[k];
                    if (ndist < dist[x][y][k]) {
                        PQ.erase(make_pair(dist[x][y][k], ncode));
                        dist[x][y][k] = ndist;
                        PQ.insert(make_pair(dist[x][y][k], ncode));
                    }
                }
            }
            int nx = x + dx[z], ny = y + dy[z], nz = z ^ 2;
            int ncode = CODE(nx, ny, nz);
            int ndist = dist[x][y][z] + 1;
            if (ndist < dist[nx][ny][nz]) {
                PQ.erase(make_pair(dist[nx][ny][nz], ncode));
                dist[nx][ny][nz] = ndist;
                PQ.insert(make_pair(dist[nx][ny][nz], ncode));
            }
        }
        int ans = min(dist[0][0][1], dist[0][0][2]);
        if (X == 0 && Y == 0) {
            ans = 0;
        }
        printf("%d\n", ans == inf ? -1 : ans);
    }
}
