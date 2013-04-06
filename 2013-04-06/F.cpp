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

const int N = 4;
const int S = 99;

struct State {
    int pos;
    int color[N];
    int num[N];

    vector<pair<int,int> > forbid;

    State() : pos(0), forbid(0) {
        memset(color, 0, sizeof(color));
        memset(num, 0, sizeof(num));
    }

    bool operator<(const State &o) const {
        if (pos != o.pos) {
            return pos < o.pos;
        }
        for (int i = 0; i < N; i++) {
            if (color[i] != o.color[i]) {
                return color[i] < o.color[i];
            }
            if (num[i] != o.num[i]) {
                return num[i] < o.num[i];
            }
        }
        return forbid < o.forbid;
    }

    void normalize() {
        for (int i = 0; i < N; i++) {
            color[i] = -color[i];
        }
        FOR (it, forbid) {
            it->first = -it->first;
            it->second = -it->second;
        }
        int colors = 0;
        for (int i = 0; i < N; i++) {
            if (color[i] < 0) {
                colors ++;
                FOR (it, forbid) {
                    if (it->first == color[i]) {
                        it->first = colors;
                    }
                    if (it->second == color[i]) {
                        it->second = colors;
                    }
                }
                for (int k = N - 1; k >= i; k--) {
                    if (color[k] == color[i]) {
                        color[k] = colors;
                        num[k] = num[i];
                    }
                }
            } else if (color[i] == 0) {
                num[i] = 0;
            }
        }
        FOR (it, forbid) {
            if (it->first == it->second || it->first <= 0 || it->second <= 0) {
                it->first = it->second = 9999;
            } else if (it->first > it->second) {
                swap(it->first, it->second);
            }
        }
        sort(forbid.begin(), forbid.end());
        forbid.erase(unique(forbid.begin(), forbid.end()), forbid.end());
        if (forbid.size() && forbid.back().first == 9999) {
            forbid.pop_back();
        }
    }

    int count(int c) const {
        int ret = 0;
        for (int i = 0; i < N; i++) {
            if (color[i] == c) {
                ret ++;
            }
        }
        return ret;
    }

    void change(int c, int nc) {
        if (c == 0 || nc == c) {
            return;
        }
        for (int i = 0; i < N; i++) {
            if (color[i] == c) {
                color[i] = nc;
            }
        }
        FOR (it, forbid) {
            if (it->first == c) {
                it->first = nc;
            }
            if (it->second == c) {
                it->second = nc;
            }
        }
    }

    bool check(int a, int b) const {
        if (a > b) {
            swap(a, b);
        }
        return find(forbid.begin(), forbid.end(), make_pair(a, b)) == forbid.end();
    }

    void changeNum(int c, int nnum) {
        for (int i = 0; i < N; i++) {
            if (color[i] == c) {
                num[i] = nnum;
            }
        }
    }

    vector<State> nextStates() const {
        vector<State> ret;
        for (int id = 0; id < 4; id++) {
            const bool connUp = id & 1, connLeft = id & 2;
            const int ncolor = 99;
            State ns = *this;
            int nsize = 1;
            if (connUp && color[pos] == 0) {
                continue;
            }
            if (connLeft && (pos == 0 || color[pos - 1] == 0)) {
                continue;
            }
            if (connUp && connLeft && !check(color[pos - 1], color[pos])) {
                continue;
            }
            if (connUp) {
                nsize += ns.num[pos];
                ns.change(ns.color[pos], ncolor);
            } else {
                if (ns.color[pos] > 0 && ns.count(ns.color[pos]) == 1) {
                    continue;
                }
                if (color[pos] > 0) {
                    ns.forbid.push_back(make_pair(ncolor, color[pos]));
                }
                ns.color[pos] = 0;
                ns.num[pos] = 0;
            }
            ns.color[pos] = ncolor;
            if (connLeft) {
                if (ns.color[pos - 1] != ncolor) {
                    nsize += ns.num[pos - 1];
                    ns.change(ns.color[pos - 1], ncolor);
                }
                if (!connUp && color[pos] == color[pos - 1]) {
                    continue;
                }
            } else {
                if (pos > 0 && color[pos - 1] > 0) {
                    if (connUp && color[pos] == color[pos - 1]) {
                        continue;
                    }
                    ns.forbid.push_back(make_pair(ncolor, color[pos - 1]));
                }
            }
            if (nsize > 4) {
                continue;
            }
            if (nsize == 4) {
                ns.change(ncolor, 0);
            } else {
                ns.changeNum(ncolor, nsize);
            }
            ns.pos = (pos + 1) % N;
            ns.normalize();
            ret.push_back(ns);
        }
        return ret;
    }

    void debug() const {
        for (int i = 0; i < N; i++) {
            putchar(i == pos ? '(' : ' ');
            if (color[i] == 0) {
                printf("  ");
            } else {
                printf("%c%d", color[i] - 1 + 'A', num[i]);
            }
            putchar(i == pos ? ')' : ' ');
        }
        printf(" :");
        FOR(it, forbid) {
            printf(" %c%c", 'A' + it->first - 1, 'A' + it->second - 1);
        }
        puts("");
    }
};

map<State,int> states[N];
State empty;

void prepare()
{
    states[0][empty] = 0;
    queue<State> Q;
    Q.push(empty);
    while (!Q.empty()) {
        State p = Q.front();
        Q.pop();
        vector<State> ns = p.nextStates();
        FOR (q, ns) {
            if (!states[q->pos].count(*q)) {
                int id = states[q->pos].size();
                states[q->pos][*q] = id;
                Q.push(*q);
            }
        }
    }
    assert(states[0].size() == S);
}

typedef int matrix[S][S];
int n, MOD;

void mul(matrix a, matrix b)
{
    static long long tmp[S][S];
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            for (int k = 0; k < S; k++) {
                tmp[i][j] += (long long)a[i][k] * b[k][j] % MOD;
            }
        }
    }
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            a[i][j] = tmp[i][j] % MOD;
        }
    }
}

void pow(matrix a, matrix r, int p)
{
    if (p == 0) {
        memset(r, 0, sizeof(matrix));
        for (int i = 0; i < S; i++) {
            r[i][i] = 1 % MOD;
        }
    } else {
        pow(a, r, p >> 1);
        mul(r, r);
        if (p & 1) {
            mul(r, a);
        }
    }
}

matrix ma;

void prepareMatrix()
{
    memset(ma, 0, sizeof(ma));
    FOR (it, states[0]) {
        State s = it->first;
        int id = it->second;
        map<State,int> mapping;
        mapping[s] = 1;
        for (int i = 0; i < N; i++) {
            map<State,int> nmapping;
            FOR (jt, mapping) {
                vector<State> ns = jt->first.nextStates();
                FOR (kt, ns) {
                    (nmapping[*kt] += jt->second) %= MOD;
                }
            }
            mapping = nmapping;
        }
        FOR (jt, mapping) {
            assert(states[0].count(jt->first));
            ma[states[0][jt->first]][id] = jt->second;
        }
    }
}

matrix ans;

int main()
{
    prepare();
    scanf("%d%d", &n, &MOD);
    prepareMatrix();
    pow(ma, ans, n);
    printf("%d\n", ans[0][0]);
}
