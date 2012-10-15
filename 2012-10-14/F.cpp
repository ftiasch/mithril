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

#define FOR(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int MAXN = 100000;
const int MOD = 1000000007;
const int BASE = 4423;

long long modInv[MAXN + 1];
long long powBase[MAXN * 2 + 1];
int phi[MAXN + 1];

void prepare()
{
    modInv[1] = 1;
    for (int i = 2; i <= MAXN; i++) {
        modInv[i] = (MOD - MOD / i) * modInv[MOD % i] % MOD;
    }
    powBase[0] = 1;
    for (int i = 1; i <= MAXN * 2; i++) {
        powBase[i] = powBase[i - 1] * BASE;
    }
    for (int i = 1; i <= MAXN; i++) {
        phi[i] = i;
    }
    for (int i = 1; i <= MAXN; i++) {
        for (int j = i + i; j <= MAXN; j += i) {
            phi[j] -= phi[i];
        }
    }
}

struct Node
{
    long long ways;
    int hashLen;
    long long hashValue;

    inline bool operator<(const Node &o) const {
        return hashValue < o.hashValue;
    }

    inline bool operator==(const Node &o) const {
        return hashValue == o.hashValue;
    }
};

bool inCycle[MAXN];
Node nodes[MAXN];
vector<int> children[MAXN];

long long countCycle(int n, int m)
{
    long long ans = 0, mul = m;
    for (int i = 2; i <= n; i++) {
        mul = mul * (m - 1) % MOD;
        ans = (mul + MOD - ans) % MOD;
    }
    return ans;
}

long long solve(int m, const vector<int> &cycle)
{
    FOR (i, cycle) {
        inCycle[*i] = true;
    }
    FOR (root, cycle) {
        vector<int> order;
        order.push_back(*root);
        for (int i = 0; i < order.size(); i++) {
            int p = order[i];
            FOR (q, children[p]) {
                if (!inCycle[*q]) {
                    order.push_back(*q);
                }
            }
        }
        for (int i = order.size() - 1; i >= 0; i--) {
            int p = order[i];
            nodes[p].ways = 1;
            nodes[p].hashLen = 1;
            nodes[p].hashValue = 1;
            vector<Node> chd;
            FOR (q, children[p]) {
                if (!inCycle[*q]) {
                    chd.push_back(nodes[*q]);
                }
            }
            sort(chd.begin(), chd.end());
            FOR (c, chd) {
                nodes[p].hashLen += c->hashLen;
                nodes[p].hashValue *= powBase[c->hashLen];
                nodes[p].hashValue += c->hashValue;
            }
            nodes[p].hashLen ++;
            nodes[p].hashValue *= BASE;
            nodes[p].hashValue += 2;
            for (int j = 0; j < chd.size(); ) {
                int nj = j + 1;
                while (nj < chd.size() && chd[j] == chd[nj]) {
                    nj ++;
                }
                int cnt = nj - j;
                long long allways = chd[j].ways * (m - 1) % MOD;
                for (int k = 0; k < cnt; k++) {
                    nodes[p].ways = nodes[p].ways * (allways + (cnt - 1) - k) % MOD;
                    nodes[p].ways = nodes[p].ways * modInv[k + 1] % MOD;
                }
                j = nj;
            }
        }
    }
    int n = cycle.size();
    int shiftCounts = 0;
    long long shiftSum = 0;
    for (int len = 1; len <= n; len++) {
        if (n % len != 0) {
            continue;
        }
        int groupSize = phi[n / len];
        bool valid = true;
        for (int s = 0; s < len && valid; s++) {
            for (int i = s + len; i < n; i += len) {
                if (!(nodes[cycle[i]] == nodes[cycle[s]])) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) {
            shiftCounts += groupSize;
            long long mul = countCycle(len, m);
            for (int s = 0; s < len; s++) {
                mul = mul * nodes[cycle[s]].ways % MOD;
            }
            shiftSum += groupSize * mul % MOD;
        }
    }
    return shiftSum * modInv[shiftCounts] % MOD;
}

int next[MAXN];
int visited[MAXN], visitCount;

int solve(int n, int m)
{
    memset(visited, 0, sizeof(*visited) * n);
    visitCount = 0;
    for (int i = 0; i < n; i++) {
        children[i].clear();
    }
    for (int i = 0; i < n; i++) {
        children[next[i]].push_back(i);
    }
    memset(inCycle, false, sizeof(*inCycle) * n);
    long long ans = 1;
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            visitCount ++;
            int ptr = i;
            while (visited[ptr] == 0) {
                visited[ptr] = visitCount;
                ptr = next[ptr];
            }
            if (visited[ptr] != visitCount) {
                continue;
            }
            vector<int> cycle;
            cycle.push_back(ptr);
            for (int nptr = next[ptr]; nptr != ptr; nptr = next[nptr]) {
                cycle.push_back(nptr);
            }
            ans = ans * solve(m, cycle) % MOD;
        }
    }
    return (int)ans;
}

int main()
{
    prepare();
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; i++) {
            scanf("%d", next + i);
            next[i] --;
        }
        printf("%d\n", solve(n, m));
    }
}
