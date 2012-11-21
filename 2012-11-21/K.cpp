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

const int dx[] = {0, -1, 0, 1};
const int dy[] = {1, 0, -1, 0};

const int RIGHT = 0;
const int UP = 1;
const int LEFT = 2;
const int DOWN = 3;

int n, L;

struct Position
{
    int x, y;

    Position(int x, int y) : x(x), y(y) {}

    Position() {}

    Position move(int dir) const {
        return Position(x + dx[dir], y + dy[dir]);
    }

    bool operator==(const Position &o) const {
        return x == o.x && y == o.y;
    }
};

vector<Position> line[2];

void expand(int dir)
{
    for (int i = 0; i < 2; i++) {
        line[i].push_back(line[i].back().move(dir));
    }
}

void turnDir(int dir)
{
    if (line[0].back().move(dir) == line[1].back()) {
        line[0].push_back(line[1].back());
        line[1].pop_back();
    } else if (line[1].back().move(dir) == line[0].back()) {
        line[1].push_back(line[0].back());
        line[0].pop_back();
    }
}

int main()
{
    scanf("%d%d", &n, &L);
    if (L < 4 || L > n * n || L % 2 == 1) {
        puts("Unsuitable device");
    } else {
        puts("Overwhelming power of magic");
        int base = n % 2;
        line[0].push_back(Position(base, 0));
        line[0].push_back(Position(base, 1));
        line[1].push_back(Position(base + 1, 0));
        line[1].push_back(Position(base + 1, 1));
        int dir = RIGHT;
        while (base < n && line[0].size() + line[1].size() < L) {
            for (int now = 2; now < n && line[0].size() + line[1].size() < L; now++) {
                expand(dir);
            }
            base += 2;
            if (base < n && line[0].size() + line[1].size() < L) {
                turnDir(DOWN);
                for (int it = 0; it < 2 && line[0].size() + line[1].size() < L; ++it) {
                    expand(DOWN);
                }
                dir = LEFT + RIGHT - dir;
                if (line[0].size() + line[1].size() < L) {
                    turnDir(dir);
                }
            }
        }
        if (line[0].size() + line[1].size() < L) {
            assert(n % 2 == 1);
            int upperBlocks = (L - line[0].size() - line[1].size()) / 2;
            vector<Position> upperLine;
            for (int i = 0; i < upperBlocks * 2; i += 2) {
                upperLine.push_back(line[0][i]);
                upperLine.push_back(line[0][i].move(UP));
                upperLine.push_back(line[0][i + 1].move(UP));
                upperLine.push_back(line[0][i + 1]);
            }
            line[0].erase(line[0].begin(), line[0].begin() + upperBlocks * 2);
            line[0].insert(line[0].begin(), upperLine.begin(), upperLine.end());
        }
        while (line[1].size() > 0) {
            line[0].push_back(line[1].back());
            line[1].pop_back();
        }
        for (int i = 0; i < line[0].size(); i++) {
            printf("%d %d\n", line[0][i].x + 1, line[0][i].y + 1);
        }
    }
}
