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

const int dx[] = {1,1,0,-1,-1,0};
const int dy[] = {0,1,1,0,-1,-1};

const int maxn = 512;
const int maxs = 100;

int label[maxs * 2][maxs * 2];
bool forbidden[maxn];
int sz = 0;

int adj[maxn][6];

void prepare()
{
    sz = 0;
    memset(label, -1, sizeof(label));
    int x = maxs, y = maxs, d = 2;
    label[x][y] = sz++;
    x += dx[d], y += dy[d];
    label[x][y] = sz++;
    d = 0;
    while (sz < maxn) {
        if (label[x + dx[(d + 5) % 6]][y + dy[(d + 5) % 6]] < 0) {
            d = (d + 5) % 6;
        }
        x += dx[d];
        y += dy[d];
        assert(0 <= x && x < maxs * 2 && 0 <= y && y < maxs * 2);
        assert(label[x][y] < 0);
        label[x][y] = sz ++;
    }
    memset(adj, -1, sizeof(adj));
    for (int i = 0; i < maxs * 2; i++)
        for (int j = 0; j < maxs * 2; j++) {
            if (label[i][j] >= 0) {
                for (int k = 0; k < 6; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (label[nx][ny] >= 0) {
                        adj[label[i][j]][k] = label[nx][ny];
                    }
                }
            }
        }
}

int n, m;
int s1, t1, s2, t2;

int dist[maxn][maxn];

int main()
{
    prepare();
    while (scanf("%d%d", &n, &m) == 2 && n) {
        scanf("%d%d%d%d", &s1, &t1, &s2, &t2);
        s1 --, t1 --, s2 --, t2 --;
        memset(forbidden, false, sizeof(forbidden));
        for (int i = 0; i < m; i++) {
            int ai;
            scanf("%d", &ai);
            ai --;
            forbidden[ai] = true;
        }
        memset(dist, -1, sizeof(dist));
        queue<pair<int,int> > Q;
        Q.push(make_pair(s1, s2));
        dist[s1][s2] = 0;
        while (!Q.empty()) {
            int px = Q.front().first;
            int py = Q.front().second;
            Q.pop();
            for (int i = 0; i < 6; i++) {
                int qx = adj[px][i];
                if (qx < 0 || qx >= n || forbidden[qx])
                    continue;
                for (int j = 0; j < 6; j++) {
                    int qy = adj[py][j];
                    if (qy < 0 || qy >= n || forbidden[qy])
                        continue;
                    if (i == j || qx == qy)
                        continue;
                    if (dist[qx][qy] < 0) {
                        dist[qx][qy] = dist[px][py] + 1;
                        Q.push(make_pair(qx, qy));
                    }
                }
            }
        }
        if (dist[t1][t2] < 0) {
            printf("neda sa\n");
        } else {
            printf("%d\n", dist[t1][t2]);
        }
    }
}
