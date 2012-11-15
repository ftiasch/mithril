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

const double PI = acos(-1.0);

const int maxn = 222;

int n, m;
char grid[maxn][maxn];

int label[maxn][maxn], labels;
double area[maxn * maxn / 2];

vector<int> adj[maxn * maxn / 2];

int flag[maxn * maxn / 2], flags;

int main()
{
    int tests, cas = 0;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%s", grid[i]);
        }
        labels = 0;
        memset(label, -1, sizeof(label));
        for (int i = 0; i <= 2 * n; i++) {
            for (int j = 0; j <= 2 * m; j++) {
                if ((i + j) % 2 == 0) {
                    if (i % 2 == 1) {
                        area[labels] = 4 - PI;
                    } else {
                        area[labels] = PI;
                        if (i == 0 || i == 2 * n) {
                            area[labels] /= 2;
                        }
                        if (j == 0 || j == 2 * m) {
                            area[labels] /= 2;
                        }
                    }
                    adj[labels].clear();
                    label[i][j] = labels ++;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int dir = grid[i][j] == '1' ? 1 : -1;
                int a = label[i * 2 + 1][j * 2 + 1];
                for (int dx = -1; dx <= 1; dx += 2) {
                    int dy = dx * dir;
                    int b = label[i * 2 + 1 + dx][j * 2 + 1 + dy];
                    assert(a >= 0 && b >= 0);
                    adj[a].push_back(b);
                    adj[b].push_back(a);
                }
            }
        }
        int qs;
        scanf("%d", &qs);
        printf("Case %d:", ++cas);
        cout << endl;
        while (qs--) {
            int sx, sy;
            scanf("%d%d", &sx, &sy);
            int src = label[sx][sy];
            if (src < 0) {
                printf("0.0000");
            } else {
                flags ++;
                queue<int> Q;
                Q.push(src);
                flag[src] = flags;
                double ans = 0;
                while (!Q.empty()) {
                    int p = Q.front();
                    Q.pop();
                    ans += area[p];
                    FOR (q, adj[p]) {
                        if (flag[*q] != flags) {
                            flag[*q] = flags;
                            Q.push(*q);
                        }
                    }
                }
                printf("%.4f", ans);
            }
            cout << endl;
        }
    }
}
