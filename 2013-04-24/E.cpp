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

struct Tableaux
{
    int n;
    int len[18], bits[18];

    void read() {
        n = 0;
        while (true) {
            static char buf[1 << 10];
            gets(buf);
            len[n] = bits[n] = 0;
            istringstream ssin(buf);
            for (int aij; ssin >> aij; ) {
                if (aij < 0) {
                    len[n] = bits[n] = 0;
                    return;
                }
                len[n] ++;
                bits[n] |= 1 << aij - 1;
            }
            n ++;
        }
    }

    bool canRemove(int row) const {
        if (len[row] == 0 || len[row] == len[row + 1]) {
            return false;
        }
        return true;
    }
    
    int remove(int row) {
        int val = 31 -  __builtin_clz(bits[row]);
        len[row] --;
        bits[row] &= ~(1 << val);
        if (row == n - 1 && len[row] == 0) {
            n --;
        }
        return val;
    }

    bool canAdd(int row, int val) const {
        if (row > 0 && len[row] == len[row - 1]) {
            return false;
        }
        if (bits[row] >= (2 << val)) {
            return false;
        }
        if (row > 0 && __builtin_popcount(bits[row - 1] & (1 << val) - 1) < len[row] + 1) {
            return false;
        }
        return true;
    }

    void add(int row, int val) {
        len[row] ++;
        bits[row] |= 1 << val;
        if (row == n) {
            n ++;
            bits[n] = len[n] = 0;
        }
    }

    bool operator==(const Tableaux &o) const {
        if (n != o.n) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (bits[i] != o.bits[i]) {
                return false;
            }
        }
        return true;
    }

    unsigned long long hashCode() const {
        unsigned long long h = n;
        for (int i = 0; i < n; i ++) {
            h = h * 3137 + bits[i];
        }
        return h;
    }

    void selfCheck() const {
        vector<vector<int> > S(n);
        int mask = 0, num = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 20; j++) {
                if (bits[i] >> j & 1) {
                    S[i].push_back(j);
                    mask |= 1 << j;
//printf("%d ", j);
                    num ++;
                }
            }
//puts("");
            assert(S[i].size() == len[i]);
            if (i > 0) {
                assert(len[i] <= len[i - 1]);
                for (int j = 0; j < S[i].size(); j++) {
                    assert(S[i][j] > S[i - 1][j]);
                }
            }
        }
//puts("");
        assert(mask + 1 == (1 << num));
    }
};

const int MAXN = 11111111;

unsigned long long keys[MAXN];

bool insert(unsigned long long val)
{
    int pos = val % MAXN;
    while (keys[pos] && keys[pos] != ~val) {
        if (++pos == MAXN) {
            pos = 0;
        }
    }
    if (keys[pos]) {
        return false;
    }
    keys[pos] = ~val;
    return true;
}

int main()
{
    Tableaux src, target;
    src.read();
    target.read();
    queue<pair<Tableaux, int> > Q;
    insert(src.hashCode());
    Q.push(make_pair(src, 0));
    if (src == target) {
        puts("0");
        return 0;
    }
    while (!Q.empty()) {
        Tableaux p = Q.front().first;
        int d = Q.front().second;
        Q.pop();
        for (int i = 0; i < p.n; i++) {
            if (p.canRemove(i)) {
                int val = p.remove(i);
                for (int j = 0; j <= p.n; j++) {
                    if (i != j && p.canAdd(j, val)) {
                        p.add(j, val);
                        if (insert(p.hashCode())) {
                            if (p == target) {
                                printf("%d\n", d + 1);
                                return 0;
                            }
                            Q.push(make_pair(p, d + 1));
                        }
                        p.remove(j);
                    }
                }
                p.add(i, val);
            }
        }
    }
    puts("-1");
}
