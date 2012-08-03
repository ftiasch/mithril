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

const int maxn = 128;

bool input[maxn][maxn][maxn];
int a, b, c;
int grid[maxn][maxn];

struct Ans
{
    pair<int,int> x, y, z;

    Ans() : x(0,-1), y(0,-1), z(0,-1) {}

    inline int getVol() const {
        return (x.second - x.first + 1) * (y.second - y.first + 1) * (z.second - z.first + 1);
    }

    bool operator<(const Ans &o) const {
        return getVol() < o.getVol();
    }
};

int L[maxn], R[maxn], H[maxn];

void solve(int n, int m, int x1, int x2, Ans &ans)
{
    Ans ret;
    ret.x.first = x1;
    ret.x.second = x2;
    memset(H, 0, sizeof(H));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] > 0) {
                H[j] = 0;
            } else {
                H[j] ++;
            }
        }
        for (int j = 0; j < m; j++) {
            L[j] = j;
            while (L[j] > 0 && H[L[j] - 1] >= H[j]) {
                L[j] = L[L[j] - 1];
            }
        }
        for (int j = m - 1; j >= 0; j--) {
            R[j] = j;
            while (R[j] + 1 < m && H[R[j] + 1] >= H[j]) {
                R[j] = R[R[j] + 1];
            }
        }
        for (int j = 0; j < m; j++) {
            ret.y.first = i - H[j] + 1;
            ret.y.second = i;
            ret.z.first = L[j];
            ret.z.second = R[j];
            ans = max(ans, ret);
        }
    }
}

int main()
{
    scanf("%d%d%d", &a, &b, &c);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            for (int k = 0; k < c; k++) {
                int aijk;
                scanf("%d", &aijk);
                input[i][j][k] = aijk != 0;
            }
        }
    }
    int ansX = 0;
    for (int y = 0; y < b; y++) {
        for (int z = 0; z < c; z++) {
            int cnt = 0;
            for (int x = 0; x < a; x++) {
                if (!input[x][y][z]) {
                    ansX = max(ansX, ++cnt);
                } else {
                    cnt = 0;
                }
            }
        }
    }
    Ans ans;
    memset(grid, 0, sizeof(grid));
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            for (int k = 0; k < c; k++) {
                if (input[i][j][k]) {
                    grid[j][k] ++;
                }
            }
        }
        if (i >= ansX - 1) {
            solve(b, c, i - ansX + 1, i, ans);
            for (int j = 0; j < b; j++) {
                for (int k = 0; k < c; k++) {
                    if (input[i - ansX + 1][j][k]) {
                        grid[j][k] --;
                    }
                }
            }
        }
    }
    printf("%d %d %d\n", ans.x.first + 1, ans.y.first + 1, ans.z.first + 1);
    printf("%d %d %d\n", ans.x.second + 1, ans.y.second + 1, ans.z.second + 1);
}
