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

const int maxn = 3001;
const int inf = 1000000000;

int opt[2][maxn][maxn];
int prev[2][maxn][maxn];

const int ENTER_BLOCK = 0;
const int MOVE_BLOCK = 1;
const int LEAVE_BLOCK = 2;
const int INSERT = 3;
const int COPY = 4;
const int DELETE = 5;

char s[maxn], t[maxn];

int blockCost, insCost, delCost, copyCost;

int n, m;

void update(int &a, int v, int type)
{
    if (a > v) {
        a = v;
        *(&prev[0][0][0] + (&a - &opt[0][0][0])) = type;
    }
}

int main()
{
    scanf("%d%d%d%d", &blockCost, &insCost, &delCost, &copyCost);
    scanf("%s%s", s, t);
    n = strlen(s), m = strlen(t);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            opt[0][i][j] = opt[1][i][j] = inf;
        }
    }
    opt[0][0][0] = 0;
    memset(prev, -1, sizeof(prev));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            update(opt[0][i][j], opt[1][i][j], LEAVE_BLOCK);
            if (i < n) {
                update(opt[0][i+1][j], opt[0][i][j] + delCost, DELETE);
                update(opt[1][i+1][j], opt[0][i][j] + blockCost, ENTER_BLOCK);
                update(opt[1][i+1][j], opt[1][i][j], MOVE_BLOCK);
            }
            if (i < n && j < m && s[i] == t[j]) {
                update(opt[0][i+1][j+1], opt[0][i][j] + copyCost, COPY);
            }
            if (j < m) {
                update(opt[0][i][j+1], opt[0][i][j] + insCost, INSERT);
            }
        }
    }
    printf("%d\n", opt[0][n][m]);
    vector<pair<int,int> > blocks;
    int leavePos = -1;
    string seq = "";
    for (int x = n, y = m, z = 0; x > 0 || y > 0 || z > 0; ) {
        if (prev[z][x][y] == ENTER_BLOCK) {
            z ^= 1;
            x --;
            blocks.push_back(make_pair(x, leavePos));
            leavePos = -1;
        } else if (prev[z][x][y] == MOVE_BLOCK) {
            x --;
        } else if (prev[z][x][y] == LEAVE_BLOCK) {
            z ^= 1;
            leavePos = x;
        } else if (prev[z][x][y] == INSERT) {
            y --;
            seq += 'I';
        } else if (prev[z][x][y] == COPY) {
            x --;
            y --;
            seq += 'C';
        } else if (prev[z][x][y] == DELETE) {
            x --;
            seq += 'D';
        } else {
            assert(false);
        }
    }
    printf("%d\n", blocks.size());
    for (int i = 0; i < blocks.size(); i++) {
        printf("%d %d\n", blocks[i].first + 1, blocks[i].second);
    }
    reverse(seq.begin(), seq.end());
    printf("%s\n", seq.c_str());
}
