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

void print(const vector<string> &grid) {
    printf("    +%s+\n", string(grid[0].size(), '-').c_str());
    for (int j = 0; j < grid.size(); j++) {
        printf("    |%s|\n", grid[j].c_str());
    }
    printf("    +%s+\n", string(grid[0].size(), '-').c_str());
}

int findOffset(const vector<string> &a, const vector<string> &b, int &offsetX, int &offsetY)
{
    static int cnt[200][200];
    for (int i = 0; i < a.size() + b.size(); i++) {
        memset(cnt[i], 0, sizeof(cnt[0][0]) * (a[0].size() + b[0].size()));
    }
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            for (int x = 0; x < b.size(); x++) {
                for (int y = 0; y < b[0].size(); y++) {
                    if (a[i][j] == b[x][y]) {
                        if (a[i][j] != '-') {
                            cnt[b.size() - x + i][b[0].size() - y + j] ++;
                        }
                    } else if (a[i][j] != '-' && b[x][y] != '-') {
                        cnt[b.size() - x + i][b[0].size() - y + j] = -inf;
                    }
                }
            }
        }
    }
    int ret = 0;
    offsetX = offsetY = 0;
    for (int i = 0; i < a.size() + b.size(); i++) {
        for (int j = 0; j < a[0].size() + b[0].size(); j++) {
            if (ret < cnt[i][j]) {
                ret = cnt[i][j];
                offsetX = i - b.size();
                offsetY = j - b[0].size();
            }
        }
    }
    return ret;
}

vector<string> mergeBy(const vector<string> &a, const vector<string> &b, int offsetX, int offsetY)
{
    int lx = min(0, offsetX), rx = max(a.size() - 1, b.size() - 1 + offsetX);
    int ly = min(0, offsetY), ry = max(a[0].size() - 1, b[0].size() - 1 + offsetY);
    vector<string> ret(rx - lx + 1, string(ry - ly + 1, '-'));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            if (a[i][j] != '-') {
                ret[i - lx][j - ly] = a[i][j];
            }
        }
    }
    for (int i = 0; i < b.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            if (b[i][j] != '-') {
                ret[i + offsetX - lx][j + offsetY - ly] = b[i][j];
            }
        }
    }
    return ret;
}

void read(vector<string> &input)
{
    static char tmp[1000000];
    int n, m;
    scanf("%d%d", &n, &m);
    input.resize(n);
    for (int i = 0; i < n; i++) {
        static char str[100];
        scanf("%s", str);
        gets(tmp);
        input[i] = str;
        input[i].resize(m);
    }
}

int main()
{
    int n, cas = 0;
    while (scanf("%d", &n) == 1 && n) {
        if (cas > 0) {
            puts("");
        }
        vector<pair<int, vector<string> > > maps(n);
        for (int i = 0; i < n; i++) {
            maps[i].first = i + 1;
            read(maps[i].second);
        }
        int num = n;
        while (true) {
            int score = 0, u, v, x, y;
            for (int i = 0; i < maps.size(); i++) {
                for (int j = i + 1; j < maps.size(); j++) {
                    int s, nx, ny;
                    s = findOffset(maps[i].second, maps[j].second, nx, ny);
                    if (s > score) {
                        score = s;
                        u = i, v = j;
                        x = nx, y = ny;
                    }
                }
            }
            if (score == 0) {
                break;
            }
            vector<string> merged = mergeBy(maps[u].second, maps[v].second, x, y);
//printf("%d %d -> %d (Score = %d, offsetX = %d, offsetY = %d)\n", maps[u].first, maps[v].first, num + 1, score, x, y);
            maps.erase(maps.begin() + v);
            maps.erase(maps.begin() + u);
            maps.push_back(make_pair(++num, merged));
//print(merged);
        }
        printf("Case %d\n", ++cas);
        for (int i = 0; i < maps.size(); i++) {
            if (i > 0) {
                puts("");
            }
            printf("    MAP %d:\n", maps[i].first);
            print(maps[i].second);
        }
    }
}
