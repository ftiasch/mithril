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

int len;

set<vector<int> > S;

struct Tuple
{
    vector<int> prefix, suffix;

    Tuple() : prefix(0), suffix(0) {}

    Tuple(int a) : prefix(1, a), suffix(1, a) {}
    
    Tuple(const vector<int> &p, const vector<int> &s) : prefix(p), suffix(s) {}
};

void add(vector<int> &a, const vector<int> &b)
{
    int ptr = 0;
    while (a.size() < len - 1 && ptr < b.size()) {
        a.push_back(b[ptr++]);
    }
}

Tuple concat(const Tuple &a, const Tuple &b)
{
    if (a.suffix.size() + b.prefix.size() >= len) {
        vector<int> t = a.suffix;
        reverse(t.begin(), t.end());
        FOR (it, b.prefix) {
            t.push_back(*it);
        }
        for (int i = 0; i + len <= t.size(); i++) {
            S.insert(vector<int>(t.begin() + i, t.begin() + i + len));
        }
    }
    Tuple ret(a.prefix, b.suffix);
    add(ret.prefix, b.prefix);
    add(ret.suffix, a.suffix);
    return ret;
}

int n;

const int maxn = 128;
vector<int> adj[maxn];

bool seen[maxn];
Tuple memo[maxn];

Tuple go(int p)
{
    Tuple &ret = memo[p];
    if (seen[p]) {
        return ret;
    }
    seen[p] = true;
    if (adj[p].empty()) {
        return ret = Tuple(p);
    }
    ret = Tuple();
    FOR (q, adj[p]) {
        ret = concat(ret, go(*q));
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &len);
    for (int i = 0; i < n; i++) {
        int ki;
        scanf("%d", &ki);
        if (ki > 0) {
            adj[i].resize(ki);
            for (int j = 0; j < ki; j++) {
                scanf("%d", &adj[i][j]);
                adj[i][j] --;
            }
        }
    }
    memset(seen, false, sizeof(seen));
    S.clear();
    for (int i = 0; i < n; i++) {
        go(i);
    }
    printf("%d\n", S.size());
}
