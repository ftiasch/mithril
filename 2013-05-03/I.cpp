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

const int maxn = 100;

int ma[maxn][maxn];

bool genMatrix(int n)
{
    if (n % 2 == 0) {
        return false;
    }
    memset(ma, -1, sizeof(ma));
    int x = 0, y = 0;
    vector<int> sumX(n, 0), sumY(n, 0);
    for (int it = 0; it < n * n; ++it) {
        assert(ma[x][y] < 0);
        ma[x][y] = it;
        sumX[x] += it;
        sumY[y] += it;
        if (ma[(x + 1) % n][(y + 2) % n] >= 0) {
            y = (y + 1) % n;
        } else {
            x = (x + 1) % n;
            y = (y + 2) % n;
        }
    }
    for (int i = 0; i < n; i++) {
        assert(sumX[i] == sumX[0]);
        assert(sumY[i] == sumY[0]);
    }
    return true;
}

const int MAGIC1[3][100] = {
    {1},
    {2, 3, 5, 4},
    {6}
};

const int MAGIC2[6][100] = {
    {2, 4},
    {3, 1},
    {3, 1, 2, 4, 3, 1, 2, 4},
    {2, 4, 3, 1, 2, 4, 3, 1},
    {2, 4},
    {3, 1},
};

vector<vector<int> > solve(int n)
{
    vector<vector<int> > ret(n * 3);
    for (int i = 0; i < n; i++) {
        ret[i].assign(n, -1);
        ret[i + n].assign(n * 4, -1);
        ret[i + n * 2].assign(n, -1);
    }
    if (n % 2 == 1) {
        genMatrix(n);
        for (int i = 0; i < ret.size(); i++) {
            for (int j = 0; j < ret[i].size(); j++) {
                ret[i][j] = ma[i % n][j % n] * 6 + (MAGIC1[i / n][j / n] - 1);
            }
        }
    } else {
        vector<vector<int> > small = solve(n / 2);
        for (int i = 0; i < ret.size(); i++) {
            for (int j = 0; j < ret[i].size(); j++) {
                ret[i][j] = small[i / 2][j / 2] * 4 + (MAGIC2[i / n * 2 + i % 2][j / n * 2 + j % 2] - 1);
            }
        }
    }
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<vector<int> > ans = solve(n);
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            if (j > 0) {
                putchar(' ');
            }
            printf("%d", ans[i][j] + 1);
        }
        puts("");
    }
}
