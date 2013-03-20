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

const int maxn = 50;
const int limit = 5 * 60;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const char dirC[] = "DURL";

int n;
char grid[maxn][maxn + 1];

int visited[maxn][maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    if (n % 2 == 1) {
        grid[n / 2][n / 2] = '#';
    }
    for (int x = 0; x < n; x ++) {
        for (int y = 0; y < n; y++) {
            if (x < n - 1 - x || x == n - 1 - x && y < n - 1 - y) {
                if (grid[x][y] != '*' || grid[n - 1 - x][n - 1 - y] != '*') {
                    continue;
                }
                memset(visited, -1, sizeof(visited));
                queue<pair<int,int> > Q;
                Q.push(make_pair(x, y));
                visited[x][y] = -2;
                while (!Q.empty()) {
                    int i = Q.front().first;
                    int j = Q.front().second;
                    Q.pop();
                    if ((i != x || j != y) && (i != n - 1 - x || j != n - 1 - y)) {
                        if (grid[i][j] == '*' && grid[n - 1 - i][n - 1 - j] == '*') {
                            string steps = "";
                            while (i != x || j != y) {
                                int k = visited[i][j];
                                steps += dirC[k];
                                i -= dx[k];
                                j -= dy[k];
                            }
                            reverse(steps.begin(), steps.end());
                            if (steps.size() <= limit) {
                                puts("Possible");
                                printf("%d %d\n", x + 1, y + 1);
                                puts(steps.c_str());
                                return 0;
                            }
                        }
                    }
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni < 0 || ni >= n || nj < 0 || nj >= n) {
                            continue;
                        }
                        if (grid[ni][nj] == '#' || grid[n - 1 - ni][n - 1 - nj] == '#') {
                            continue;
                        }
                        if (visited[ni][nj] != -1) {
                            continue;
                        }
                        visited[ni][nj] = k;
                        Q.push(make_pair(ni, nj));
                    }
                }
            }
        }
    }
    puts("Impossible");
}
