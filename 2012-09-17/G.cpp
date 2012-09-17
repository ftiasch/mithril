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
#include <climits>
using namespace std;

//#include <ext/hash_set>
//using namespace __gnu_cxx;

const int maxn = 111111;
const int maxlen = 1 << 20;

int lch[maxn], rch[maxn], size[maxn];
unsigned long long p9277[maxlen], strhash[maxlen], treehash[maxn];
int nodes;

map<unsigned long long, int> memo;

set<unsigned long long> sets[maxn];

void dfs(int root, int depth, int p, vector<pair<int,int> > &trees)
{
    if (p == 0) {
        return;
    }
    vector<int> st;
    st.push_back(p);
    while (!st.empty()) {
        int p = st.back();
        st.pop_back();
        if (p == 0) {
            continue;
        }
        st.push_back(lch[p]);
        st.push_back(rch[p]);
        if (size[root] % size[p] == 0 && sets[depth].insert(treehash[p]).second) {
            trees.push_back(make_pair(size[p], p));
        }
    }
}

int log2int(int p)
{
    return p < 2 ? 0 : 1 + log2int(p / 2);
}

int solve(int root, int depth = 0)
{
    if (size[root] <= 1) {
        return 0;
    }
    if (memo.count(treehash[root])) {
        return memo[treehash[root]];
    }
    int &ret = memo[treehash[root]];
    sets[depth].clear();
    vector<pair<int,int> > trees;
    dfs(root, depth, lch[root], trees);
    dfs(root, depth, rch[root], trees);
    ret = INT_MAX;
    sort(trees.rbegin(), trees.rend());
    for (int i = 0; i < trees.size(); i++) {
        int p = trees[i].second;
        vector<int> rootPieces;
        rootPieces.push_back(root);
        if (size[root] / size[p] - 1 + log2int(size[p]) >= ret) {
            continue;
        }
        bool valid = true;
        while (!rootPieces.empty()) {
            int r = rootPieces.back();
            rootPieces.pop_back();
            if (size[r] % size[p] != 0) {
                valid = false;
                break;
            }
            vector<pair<int,int> > subtreeNodes;
            subtreeNodes.push_back(make_pair(r, p));
            while (!subtreeNodes.empty()) {
                int big = subtreeNodes.back().first;
                int small = subtreeNodes.back().second;
                subtreeNodes.pop_back();
                if (lch[small] > 0 && lch[big] == 0 || rch[small] > 0 && rch[big] == 0) {
                    valid = false;
                    break;
                }
                if (lch[small] > 0) {
                    subtreeNodes.push_back(make_pair(lch[big], lch[small]));
                } else if (lch[big] > 0) {
                    rootPieces.push_back(lch[big]);
                }
                if (rch[small] > 0) {
                    subtreeNodes.push_back(make_pair(rch[big], rch[small]));
                } else if (rch[big] > 0) {
                    rootPieces.push_back(rch[big]);
                }
            }
            if (!valid) {
                break;
            }
        }
        if (valid) {
            ret = min(ret, size[root] / size[p] - 1 + solve(p, depth + 1));
        }
    }
    return ret;
}

int matching[maxlen];
int len;

char str[maxlen];

int build(int p)
{
    int q = matching[p];
    if (p + 1 == q) {
        return 0;
    }
    int r = nodes ++;
    lch[r] = build(p + 1);
    rch[r] = build(matching[q - 1]);
    size[r] = size[lch[r]] + size[rch[r]] + 1;
    treehash[r] = strhash[q + 1] - strhash[p] * p9277[q + 1 - p];
    return r;
}

int main()
{
    p9277[0] = 1;
    for (int i = 1; i < maxlen; i++) {
        p9277[i] = p9277[i] * 9277;
    }
    scanf("%s", str);
    len = strlen(str);
    strhash[0] = 0;
    for (int i = 0; i < len; i++) {
        strhash[i + 1] = strhash[i] * 9277 + str[i] * 3137;
    }
    vector<int> st;
    for (int i = 0; i < len; i++) {
        if (str[i] == '(') {
            st.push_back(i);
        } else {
            assert(!st.empty());
            int j = st.back();
            st.pop_back();
            matching[i] = j;
            matching[j] = i;
        }
    }
    assert(st.empty());
    size[0] = 0;
    nodes = 1;
    int root = build(0);
    int result = solve(root);
    printf("%d\n", result);
}
