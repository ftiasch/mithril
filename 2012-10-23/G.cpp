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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

#define MAGIC (23131312312312311ULL)

struct Rect
{
    int lx, rx, ly, ry;

    Rect(){}

    Rect(int x, int y, int l) : lx(x), rx(x + l), ly(y), ry(y + l) {
        if (l == 0) {
            clean();
        }
    }

    Rect(int lx, int rx, int ly, int ry) : lx(lx), rx(rx), ly(ly), ry(ry) {
        if (rx <= lx || ry <= ly) {
            clean();
        }
    }

    Rect intersection(const Rect &o) const {
        return Rect(max(lx, o.lx), min(rx, o.rx), max(ly, o.ly), min(ry, o.ry));
    }

    void clean() {
        lx = rx = ly = ry = 0;
    }

    bool empty() const {
        return lx == 0 && rx == 0  && ly == 0 && ry == 0;
    }

    bool operator==(const Rect &o) const {
        return lx == o.lx && rx == o.rx && ly == o.ly && ry == o.ry;
    }

    unsigned long long hashCode() const {
        return ((lx * MAGIC + rx) * MAGIC + ly) * MAGIC + ry;
    }

    void move(int dx, int dy) {
        lx += dx, rx += dx;
        ly += dy, ry += dy;
    }

};

struct Shape {
    Rect large, small;

    Shape(){}

    Shape(const Rect &l, const Rect &s) : large(l), small(l.intersection(s)) {
        if (large == small) {
            large.clean();
            small.clean();
        } else {
            bool ll = small.lx == large.lx && small.ly == large.ly;
            bool lr = small.lx == large.lx && small.ry == large.ry;
            bool rl = small.rx == large.rx && small.ly == large.ly;
            bool rr = small.rx == large.rx && small.ry == large.ry;
            if (ll && lr) {
                large.lx = small.rx;
                small.clean();
            } else if (rl && rr) {
                large.rx = small.lx;
                small.clean();
            } else if (ll && rl) {
                large.ly = small.ry;
                small.clean();
            } else if (lr && rr) {
                large.ry = small.ly;
                small.clean();
            } 
            int dx = -large.lx, dy = -large.ly;
            large.move(dx, dy);
            if (!small.empty()) {
                small.move(dx, dy);
            }
        }
    }

    bool operator==(const Shape &o) const {
        return large == o.large && small == o.small;
    }

    unsigned long long hashCode() const {
        return small.hashCode() * (MAGIC * MAGIC * MAGIC * MAGIC) + large.hashCode();
    }
};

int n;
Rect rect[444];

unsigned long long shape[444][444];

struct myhash
{
    unsigned operator()(unsigned long long a) const {
        return (unsigned)a;
    }
};

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int xi, yi, li;
        scanf("%d%d%d", &xi, &yi, &li);
        rect[i] = Rect(xi, yi, li);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            shape[i][j] = Shape(rect[i], rect[j]).hashCode();
        }
    }
    long long ret = 0;
    for (int a = 0; a < n; a++) {
        hash_map<unsigned long long,int,myhash> M;
        hash_map<unsigned long long,int,myhash>::iterator it;
        for (int b = 0; b < n; b++) {
            if (b != a) {
                M[shape[a][b]] ++;
            }
        }
        for (int c = a + 1; c < n; c++) {
            M[shape[a][c]] --;
            for (int d = 0; d < n; d++) {
                if (d != a && d != c) {
                    it = M.find(shape[c][d]);
                    if (it != M.end()) {
                        ret += it->second;
                        if (shape[a][d] == shape[c][d]) {
                            ret --;
                        }
                    }
                }
            }
            M[shape[a][c]] ++;
        }
    }
    cout << ret * 2 << endl;
}
