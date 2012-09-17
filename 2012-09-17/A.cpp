#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 50;
const int S = 10;
const int DELTA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int n, m, s, switchMask[N][N];
char map[N][N + 1], switchMap[S][N][N + 1];
bool currentFloor[1 << S][N][N];
int step[N][N][2][1 << S];

struct State {
    int x, y, f, mask;

    State(int x, int y, int f, int mask): x(x), y(y), f(f), mask(mask) {}
};

queue <State> q;

void update(int x, int y, int mask, int f, int value) {
    if (value < step[x][y][f][mask]) {
        step[x][y][f][mask] = value;
        q.push(State(x, y, f, mask));
    }
}

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", map[i]);
    }
    memset(switchMask, 0, sizeof(switchMask));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (islower(map[i][j])) {
                switchMask[i][j] = map[i][j] - 'a';
            }
            if (isupper(map[i][j])) {
                switchMask[i][j] = map[i][j] - 'A';
            }
        }
    }
    scanf("%d", &s);
    for (int k = 0; k < s; ++ k) {
        for (int i = 0; i < n; ++ i) {
            scanf("%s", switchMap[k][i]);
        }
    }
    for (int mask = 0; mask < 1 << s; ++ mask) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                currentFloor[mask][i][j] = map[i][j] == '^' || isupper(map[i][j]);
                for (int k = 0; k < s; ++ k) {
                    if ((mask >> k & 1) == 1 && switchMap[k][i][j] == '*') {
                        currentFloor[mask][i][j] ^= 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            for (int k = 0; k < 2; ++ k) {
                for (int mask = 0; mask < 1 << s; ++ mask) {
                    step[i][j][k][mask] = INT_MAX;
                }
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (map[i][j] == '%') {
                step[i][j][0][0] = 0;
                q.push(State(i, j, 0, 0));
            }
        }
    }
    int result = INT_MAX;
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        int x = s.x;
        int y = s.y;
        int f = s.f;
        int mask = s.mask;
        int v = step[x][y][f][mask];
//printf("%d %d %d %d:	%d\n",x,y,f,mask,v);
        if (map[x][y] == '&') {
            result = min(result, v);
        }
        if (isalpha(map[x][y])) {
            int id = switchMask[x][y];
            update(x, y, mask ^ (1 << id), f ^ (switchMap[id][x][y] == '*'), v + 1);
        }
        if (map[x][y] == '|') {
            update(x, y, mask, f ^ 1, v + 1);
        }
        for (int k = 0; k < 4; ++ k) {
            int xx = x + DELTA[k][0];
            int yy = y + DELTA[k][1];
            if (0 <= xx && xx < n && 0 <= yy && yy < m) {
                if (map[xx][yy] != '#' && (map[xx][yy] == '|' || currentFloor[mask][xx][yy] == f)) {
                    update(xx, yy, mask, f, v + 1);
                }
            }
        }
    }
    printf("%d\n", result == INT_MAX? -1: result);
    return 0;
}
