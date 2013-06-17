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

#include <ext/hash_set>
using namespace __gnu_cxx;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int dx[] = {1, -1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0};
const int dz[] = {0, 0, 0, 0, 1, -1};

int next[27][6];

void prepare()
{
#define CODE(x, y, z) (((x) * 3 + (y)) * 3 + (z))
    for (int x = 0; x < 3; x ++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                for (int i = 0; i < 6; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    int nz = z + dz[i];
                    if (0 <= nx && nx < 3 && 0 <= ny && ny < 3 && 0 <= nz && nz < 3) {
                        next[CODE(x, y, z)][i] = CODE(nx, ny, nz);
                    } else {
                        next[CODE(x, y, z)][i] = -1;
                    }
                }
            }
        }
    }
}

bool turn[27];
int path[27];

const int MAXDEP = 10;

hash_set<int> memo[MAXDEP][27][3];

bool search(int dep, int mask, int pos, int dir)
{
    if (dep == 27) {
        return true;
    }
    int &npos = path[dep];
    if (!turn[dep - 1]) {
        npos = next[pos][dir];
        return npos >= 0 && ~mask >> npos & 1 && search(dep + 1, mask | 1 << npos, npos, dir);
    } else {
        if (dep < MAXDEP && !memo[dep][pos][dir >> 1].insert(mask).second) {
            return false;
        }
        for (int ndir = 0; ndir < 6; ndir++) {
            if ((ndir >> 1) != (dir >> 1)) {
                npos = next[pos][ndir];
                if (npos >= 0 && ~mask >> npos & 1 && search(dep + 1, mask | 1 << npos, npos, ndir)) {
                    return true;
                }
            }
        }
        return false;
    }
}

bool solve(int s, int dir)
{
    int t = next[s][dir];
    assert(t >= 0);
    path[0] = s;
    path[1] = t;
    return search(2, 1 << s | 1 << t, t, dir);
}

bool solve()
{
    return solve(CODE(0, 0, 0), 0) || solve(CODE(0, 1, 1), 0) || solve(CODE(0, 1, 1), 2);
}

int main()
{
    freopen("folding.in", "r", stdin);
    freopen("folding.out", "w", stdout);
    prepare();
    vector<string> input;
    for (string row; cin >> row; input.push_back(row));
    vector<pair<int,int> > pos(27);
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (isalpha(input[i][j])) {
                pos[(tolower(input[i][j]) - 'a') * 2 + (isupper(input[i][j]) ? 0 : 1)] = make_pair(i, j);
            }
        }
    }
    for (int i = 1; i + 1 < 27; i++) {
        turn[i] = !(pos[i - 1].first + pos[i + 1].first == pos[i].first * 2 &&
                pos[i - 1].second + pos[i + 1].second == pos[i].second * 2);
    }
    if (solve()) {
        char ans[3][3][3];
        memset(ans, '.', sizeof(ans));
        for (int i = 0; i < 27; i++) {
            ans[path[i] / 9][path[i] / 3 % 3][path[i] % 3] = i % 2 == 0 ? i / 2 + 'A' : i / 2 + 'a';
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (j > 0) {
                    putchar(' ');
                }
                for (int k = 0; k < 3; k++) {
                    putchar(ans[i][j][k]);
                }
            }
            puts("");
        }
    } else {
        puts("Impossible");
    }
}
