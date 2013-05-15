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

const int maxn = 10;
const int dx[] = {1, -1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0};
const int dz[] = {0, 0, 0, 0, 1, -1};

int n;

int label[maxn][maxn][maxn][6];

char face[6][maxn][maxn + 1];
bool exists[maxn][maxn][maxn];

int main()
{
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            for (int id = 0; id < 6; id++) {
                scanf("%s", face[id][i]);
            }
        }
        memset(label, -1, sizeof(label));
        for (int id = 0; id < 6; id++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int ch = face[id][i][j] == '.' ? -2 : face[id][i][j] - 'A';
                    if (id == 0) {
                        // FRONT
                        label[j][n - 1 - i][0][4] = ch;
                    } else if (id == 1) {
                        // LEFT
                        label[0][n - 1 - i][n - 1 - j][0] = ch;
                    } else if (id == 2) {
                        // BACK
                        label[n - 1 - j][n - 1 - i][n - 1][5] = ch;
                    } else if (id == 3) {
                        // RIGHT
                        label[n - 1][n - 1 - i][j][1] = ch;
                    } else if (id == 4) {
                        // TOP
                        label[j][n - 1][n - 1 - i][3] = ch;
                    } else {
                        // BOTTOM
                        label[j][0][i][2] = ch;
                    }
                }
            }
        }
        memset(exists, true, sizeof(exists));
        int ans = n * n * n;
        bool valid = true;
        while (true) {
            bool found = false;
            for (int x = 0; x < n && !found; x++) {
                for (int y = 0; y < n && !found; y++) {
                    for (int z = 0; z < n && !found; z++) {
                        if (!exists[x][y][z]) {
                            continue;
                        }
                        int color = -1;
                        for (int i = 0; i < 6; i++) {
                            int ch = label[x][y][z][i];
                            if (ch == -2) {
                                color = -2;
                                break;
                            } else if (ch >= 0) {
                                if (color < 0) {
                                    color = ch;
                                } else if (color != ch) {
                                    color = -2;
                                    break;
                                }
                            }
                        }
                        if (color == -2) {
                            found = true;
                            ans --;
                            exists[x][y][z] = false;
                            for (int i = 0; i < 6; i++) {
                                int &ch = label[x][y][z][i];
                                if (ch != -1) {
                                    int nx = x + dx[i];
                                    int ny = y + dy[i];
                                    int nz = z + dz[i];
                                    while (0 <= nx && nx < n && 0 <= ny && ny < n && 0 <= nz && nz < n && !exists[nx][ny][nz]) {
                                        nx += dx[i];
                                        ny += dy[i];
                                        nz += dz[i];
                                    }
                                    if (0 <= nx && nx < n && 0 <= ny && ny < n && 0 <= nz && nz < n) {
                                        label[nx][ny][nz][i] = ch;
                                    } else if (ch >= 0) {
                                        valid = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (!found) {
                break;
            }
        }
        if (!valid) {
            puts("ERROR");
            vector<int> ret(0);
            return ret[10000];
        }
        printf("Maximum weight: %d gram(s)\n", ans);
    }
}
