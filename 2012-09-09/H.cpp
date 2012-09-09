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

const int MOD = 1000000007;

#define IX(x) ((x) << 1)

#define GET(p, x) ((p) >> IX(x) & 3U)

#define SET(p, x, v) ((p) & ~(3U << IX(x)) | (v) << IX(x))

#define SET2(p, x, v) ((p) & ~(15U << IX(x)) | (v) << IX(x))

#define NONE (0U)
#define LEFT (1U)
#define RIGHT (2U)

struct State
{
    unsigned mask;
    int circuits;

    State(unsigned mask, int circuits) : mask(mask), circuits(circuits) { }
    State(){}

    unsigned hashCode() const {
        return mask * 9277 + circuits * 3137;
    }

    bool operator==(const State &o) const {
        return mask == o.mask && circuits == o.circuits;
    }
};

const int table_size = 377777;
const int max_states = 877777;

struct HashMap {

    State states[max_states];
    int nextState[max_states];
    int values[max_states];

    int used;

    int firstPos[table_size];

    void clear() {
        memset(firstPos, -1, sizeof(firstPos));
        used = 0;
    }

    int &operator[](const State &s) {
        unsigned hash = s.hashCode() % table_size;
        int ptr = firstPos[hash];
        while (~ptr && !(states[ptr] == s)) {
            ptr = nextState[ptr];
        }
        if (ptr < 0) {
            ptr = used ++;
            states[ptr] = s;
            nextState[ptr] = firstPos[hash];
            values[ptr] = 0;
            firstPos[hash] = ptr;
        }
        return values[ptr];
    }
};

HashMap maps[2];

inline void addmod(int &a, int v)
{
    if ((a += v) >= MOD) {
        a -= MOD;
    }
}

int findMatching(int mask, int p)
{
    int dx = 0, depth = 0;
    int target, tmp;
    if ((tmp = GET(mask, p)) == LEFT) {
        dx = 1;
        target = LEFT;
    } else if (tmp == RIGHT) {
        dx = -1;
        target = RIGHT;
    } else {
        return -1;
    }
    while (true) {
        //assert(p >= 0 && p < 16);
        if (tmp = GET(mask, p)) {
            if (tmp == target) {
                depth ++;
            } else {
                if (--depth == 0) {
                    return p;
                }
            }
        }
        p += dx;
    }
}

char grid[16][16];
int n, m, num;

int main()
{
    //printf("%d\n", sizeof(maps) >> 20);
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        int now = 0;
        maps[now].clear();
        maps[now][State(0, 0)] = 1;
        scanf("%d%d%d", &n, &m, &num);
        for (int i = 0; i < n; i++) {
            scanf("%s", grid[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                bool occupied = grid[i][j] == '*';
                int prev = now;
                now ^= 1;
                maps[now].clear();
                for (int it = 0; it < table_size; ++it) {
                    for (int jt = maps[prev].firstPos[it]; ~jt; jt = maps[prev].nextState[jt]) {
                        unsigned mask = maps[prev].states[jt].mask;
                        int circuits = maps[prev].states[jt].circuits;
                        int val = maps[prev].values[jt];
                        if (mask && circuits == num) {
                            continue;
                        }
                        int maxCircuits = circuits;
                        int leftCells = n * m - i * m - j;
                        int bits = __builtin_popcount(mask) >> 1;
                        maxCircuits += bits;
                        leftCells -= bits;
                        if (leftCells >= 0) {
                            maxCircuits += leftCells >> 2;
                        } else {
                            continue;
                        }
                        if (maxCircuits < num) {
                            continue;
                        }
                        if (j == 0) {
                            if (GET(mask, m)) {
                                continue;
                            }
                            mask <<= 2;
                        }
                        int left = GET(mask, j);
                        int up = GET(mask, j + 1);
                        if (occupied) {
                            if (left == 0 && up == 0) {
                                addmod(maps[now][State(mask, circuits)], val);
                            }
                        } else {
                            if (left == 0 && up == 0) {
                                addmod(maps[now][State(SET2(mask, j, RIGHT << 2 | LEFT), circuits)], val);
                            } else if (left == 0 || up == 0) {
                                addmod(maps[now][State(SET2(mask, j, left | up), circuits)], val);
                                addmod(maps[now][State(SET2(mask, j, (left | up) << 2), circuits)], val);
                            } else if (left != up) {
                                if (left == LEFT && up == RIGHT) {
                                    int depth = 0, tmp;
                                    for (int k = 0; k < j; k++) {
                                        if ((tmp = GET(mask, k)) == LEFT) {
                                            depth ++;
                                        } else if (tmp == RIGHT) {
                                            depth --;
                                        }
                                    }
                                    if (~depth & 1 && circuits < num) {
                                        addmod(maps[now][State(SET2(mask, j, 0), circuits + 1)], val);
                                    }
                                } else if (left == RIGHT && up == LEFT) {
                                    addmod(maps[now][State(SET2(mask, j, 0), circuits)], val);
                                }
                            } else {
                                if (left == LEFT) {
                                    int p = findMatching(mask, j + 1);
                                    unsigned nmask = SET2(mask, j, 0);
                                    nmask = SET(nmask, p, LEFT);
                                    addmod(maps[now][State(nmask, circuits)], val);
                                } else if (left == RIGHT) {
                                    int p = findMatching(mask, j);
                                    unsigned nmask = SET2(mask, j, 0);
                                    nmask = SET(nmask, p, RIGHT);
                                    addmod(maps[now][State(nmask, circuits)], val);
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%d\n", maps[now][State(0, num)]);
    }
}
