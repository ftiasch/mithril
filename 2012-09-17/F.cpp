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

#include <ext/hash_map>
using namespace __gnu_cxx;

const char figures[12][6] = {
    "0000",
    "0101",
    "1010",
    "1100",
    "1001",
    "0011",
    "0110",
    "1101",
    "1011",
    "0111",
    "1110",
    "1111"
};

#define UP (1)
#define LEFT (2)
#define DOWN (3)
#define RIGHT (0)

const int width = 4;

struct State {
    int color[width], colors, one;

    int left[12];

    void rotate90() {
        swap(left[1], left[2]);
        swap(left[3], left[5]);
        swap(left[7], left[8]);
        swap(left[9], left[10]);
    }

    void clear() {
        memset(color, 0, sizeof(color));
        memset(left, 0, sizeof(left));
        colors = 1;
        one = 1;
    }

    bool normalize() {
        bool ret = false;
        for (int i = 0; i < width; i++) {
            if (color[i] != one) {
                color[i] = -color[i];
            } else {
                color[i] = 1;
                ret = true;
            }
        }
        one = 1;
        colors = 1;
        for (int i = 0; i < width; i++) {
            if (color[i] < 0) {
                colors ++;
                for (int j = width - 1; j >= i; j--) {
                    if (color[i] == color[j]) {
                        color[j] = colors;
                    }
                }
            }
        }
        return ret;
    }

    void changeAll(int a, int b) {
        if (a == 0) {
            return;
        }
        if (one == a) {
            one = b;
        }
        for (int i = 0; i < width; i++) {
            if (color[i] == a) {
                color[i] = b;
            }
        }
    }

    unsigned operator()(const State &o) const {
        unsigned ret = 0;
        for (int i = 0; i < width; i++) {
            ret = ret * 9277 + o.color[i];
        }
        for (int i = 0; i < 12; i++) {
            ret = ret * 4423 + o.left[i];
        }
        return ret;
    }

    bool operator==(const State &o) const {
        for (int i = 0; i < width; i++) {
            if (color[i] != o.color[i]) {
                return false;
            }
        }
        return memcmp(left, o.left, sizeof(left)) == 0;
    }
};

typedef hash_map<State, long long, State> HashMap;

HashMap wys[2];

int n, m;

int main()
{
    State src;
    src.clear();
    scanf("%d%d", &n, &m);
    for (int i = 0; i < 12; i++) {
        scanf("%d", &src.left[i]);
    }
    if (m > n) {
        swap(n, m);
        src.rotate90();
    }
    int now = 0;
    wys[now].clear();
    wys[now][src] = 1LL;
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int prev = now;
            now ^= 1;
            wys[now].clear();
            for (HashMap::iterator it = wys[prev].begin(); it != wys[prev].end(); ++it) {
                State s = it->first;
                long long r = it->second;
                if (j == 0) {
                    for (int k = m; k > 0; k--) {
                        s.color[k] = s.color[k - 1];
                    }
                    s.color[0] = 0;
                }
                for (int c = 0; c < 12; c++) {
                    if (s.left[c] == 0) {
                        continue;
                    }
                    State ns = s;
                    ns.left[c] --;
                    ns.one = 1;
                    int nc = i == 0 && j == 0 ? ns.one : s.colors + 2;
                    if (j > 0 && ns.color[j] && figures[c][LEFT] == '1') {
                        ns.changeAll(ns.color[j], nc);
                    }
                    if (ns.color[j + 1] && figures[c][UP] == '1') {
                        ns.changeAll(ns.color[j + 1], nc);
                    }
                    if (i + 1 == n && j + 1 == m && ns.one == nc) {
                        ret += r;
                    }
                    ns.color[j] = figures[c][DOWN] == '1' ? nc : 0;
                    ns.color[j + 1] = figures[c][RIGHT] == '1' ? nc : 0;
                    if (ns.normalize()) {
                        wys[now][ns] += r;
                    }
                }
            }
        }
    }
    cout << ret << endl;
}
