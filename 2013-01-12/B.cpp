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
#define next next__

// table, for each of 20 vertices, the adjacent 3 vertices in clockwise order

const int adj3[20][3] = {
    {8, 19, 16},
    {2, 11, 10},
    {3, 1, 17},
    {4, 12, 2},
    {5, 3, 18},
    {6, 13, 4},
    {7, 5, 19},
    {8, 14, 6},
    {9, 7, 0},
    {10, 15, 8},
    {1, 9, 16},
    {1, 12, 15},
    {3, 13, 11},
    {12, 5, 14},
    {7, 15, 13},
    {9, 11, 14},
    {17, 10, 0},
    {2, 16, 18},
    {4, 17, 19},
    {6, 18, 0}
};

int edgeLabel[20][20];
vector<pair<int,int> > edges;

// each of 60 directed edges, left or right turn result
int next[60][2];

// left or right turn sequence from edge 0
string seq[60];

// for each of 60 ways of rotation, mapping of undirected edges
int mapping[60][30];

void prepare()
{
    edges.clear();
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 3; j++) {
            int times = 0;
            for (int k = 0; k < 3; k++) {
                if (adj3[adj3[i][j]][k] == i) {
                    times ++;
                }
            }
            assert(times == 1);
            if (adj3[i][j] > i) {
                edges.push_back(make_pair(i, adj3[i][j]));
                edges.push_back(make_pair(adj3[i][j], i));
            }
        }
    }
    assert(edges.size() == 60);
    memset(edgeLabel, -1, sizeof(edgeLabel));
    for (int i = 0; i < edges.size(); i++) {
        edgeLabel[edges[i].first][edges[i].second] = i;
    }
    for (int i = 0; i < 60; i++) {
        int a = edges[i].first, b = edges[i].second;
        int pos = find(adj3[b], adj3[b] + 3, a) - adj3[b];
        assert(pos != 3);
        for (int j = 0; j < 2; j ++) {
            next[i][j] = edgeLabel[b][adj3[b][(pos + 1 + j) % 3]];
        }
    }
    for (int i = 0; i < 60; i++) {
        assert(next[next[i][0]^1][1] == (i^1));
        assert(next[next[i][1]^1][0] == (i^1));
    }
    vector<bool> vis(60, false);
    vis[0] = true;
    seq[0] = "";
    queue<int> Q;
    Q.push(0);
    while (!Q.empty()) {
        int p = Q.front();
        Q.pop();
        for (int i = 0; i < 2; i++) {
            int q = next[p][i];
            if (!vis[q]) {
                vis[q] = true;
                seq[q] = seq[p] + "LR"[i];
                Q.push(q);
            }
        }
    }
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 30; j++) {
            int now = i;
            for (int k = 0; k < seq[j << 1].size(); k++) {
                now = next[now][seq[j << 1][k] == 'L' ? 0 : 1];
            }
            mapping[i][j] = now >> 1;
        }
    }
}

const int BASE = 10000;

struct Integer
{
    vector<int> digits;

    Integer(int num = 0) : digits(1, num) {
        normalize();
    }

    Integer &normalize() {
        int carry = 0;
        for (int i = 0; i < digits.size() || carry; i++) {
            if (i == digits.size()) {
                digits.push_back(0);
            }
            digits[i] += carry;
            carry = digits[i] / BASE;
            digits[i] %= BASE;
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    Integer operator+(const Integer &o) const {
        Integer ret = *this;
        if (ret.digits.size() < o.digits.size()) {
            ret.digits.resize(o.digits.size(), 0);
        }
        for (int i = 0; i < o.digits.size(); i++) {
            ret.digits[i] += o.digits[i];
        }
        return ret.normalize();
    }

    Integer operator/(int num) const {
        Integer ret = *this;
        int carry = 0;
        for (int i = ret.digits.size() - 1; i >= 0; i--) {
            ret.digits[i] += carry * BASE;
            carry = ret.digits[i] % num;
            ret.digits[i] /= num;
        }
        return ret.normalize();
    }

};

ostream &operator<<(ostream &out, const Integer &o)
{
    out << o.digits.back();
    for (int i = (int)o.digits.size() - 2; i >= 0; i--) {
        static char buf[128];
        sprintf(buf, "%04d", o.digits[i]);
        out << buf;
    }
    return out;
}

map<vector<int>, Integer> memoCycles;
map<vector<int>, Integer> memo[33];

vector<int> input, cycles;

Integer go(int pos, vector<int> colors)
{
    sort(colors.rbegin(), colors.rend());
    while (!colors.empty() && colors.back() == 0) {
        colors.pop_back();
    }
    if (memo[pos].count(colors)) {
        return memo[pos][colors];
    }
    Integer &ret = memo[pos][colors];
    if (pos == cycles.size()) {
        return ret = colors.empty() ? 1 : 0;
    }
    ret = 0;
    for (int i = 0; i < colors.size(); i++) {
        if (colors[i] >= cycles[pos]) {
            colors[i] -= cycles[pos];
            ret = ret + go(pos + 1, colors);
            colors[i] += cycles[pos];
        }
    }
    return ret;
}

Integer solveCycles(vector<int> cycles)
{
    sort(cycles.begin(), cycles.end());
    if (memoCycles.count(cycles)) {
        return memoCycles[cycles];
    }
    ::cycles = cycles;
    for (int i = 0; i < 33; i++) {
        memo[i].clear();
    }
    return memoCycles[cycles] = go(0, input);
}

int main()
{
    prepare();
    input.assign(30, 0);
    for (int i = 0; i < 30; i++) {
        int ai;
        scanf("%d", &ai);
        input[ai - 1] ++;
    }
    memoCycles.clear();
    Integer sum = 0;
    for (int i = 0; i < 60; i++) {
        vector<bool> vis(30, false);
        vector<int> cycles;
        for (int j = 0; j < 30; j++) {
            if (!vis[j]) {
                int len = 0, ptr = j;
                while (!vis[ptr]) {
                    vis[ptr] = true;
                    len ++;
                    ptr = mapping[i][ptr];
                }
                cycles.push_back(len);
            }
        }
        sum = sum + solveCycles(cycles);
    }
    cout << sum / 60 << endl;
}
