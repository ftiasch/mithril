#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

#define FOR(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++ i)

const int maxn = 1000000 * 2 + 5;

char str[10000000 + 5];
int match[10000000 + 5];

set<int>* sets[maxn];
vector<set<int>*> pool;
bool isComplement[maxn];
int node = 0, oper[maxn];
vector<int> child[maxn];
string tmp;

inline void delSet(set<int>* ret)
{
    pool.push_back(ret);
}

inline set<int>* newSet()
{
    set<int>* ret;
    if (pool.size()) {
        ret = pool.back();
        pool.pop_back();
        ret->clear();
    } else {
        ret = new set<int>();
    }
    return ret;
}

inline int build(int l, int r)
{
    while (l <= r && str[l] == '(' && match[l] == r) {
        ++ l;
        -- r;
    }
    int ret = node ++, last = l;
//printf("%d: %d %d\n", ret, l, r);
    child[ret].clear();
    oper[ret] = -1;
    isComplement[ret] = 0;
    for (int i = l; i < r; ++ i) {
        if (str[i] == '(' || str[i] == '{') {
            i = match[i];
        }
        if (str[i] == '|') {
            oper[ret] = 0;
            child[ret].push_back(build(last, i - 1));
            last = i + 1;
        }
    }
    if (oper[ret] != -1) {
        child[ret].push_back(build(last, r));
        return ret;
    }
    for (int i = l; i < r; ++ i) {
        if (str[i] == '(' || str[i] == '{') {
            i = match[i];
        }
        if (str[i] == '&') {
            oper[ret] = 1;
            child[ret].push_back(build(last, i - 1));
            last = i + 1;
        }
    }
    if (oper[ret] != -1) {
        child[ret].push_back(build(last, r));
        return ret;
    }
    if (str[l] == '!') {
        oper[ret] = 2;
        child[ret].push_back(build(l + 1, r));
        return ret;
    }
    int x = 0;
    sets[ret] = newSet();
    bool found = false;
    for (int i = l; i <= r; ++ i) {
        if (isdigit(str[i])) {
            x = x * 10 + str[i] - '0';
            found = true;
        } else {
            if (found) {
                sets[ret]->insert(x);
            }
            found = false;
            x = 0;
        }
    }
    if (found) {
        sets[ret]->insert(x);
    }
    return ret;
}

inline void merge(int u, int v);

inline void intersect(int u, int v)
{
    if (!isComplement[u] && !isComplement[v]) {
        if (sets[u]->size() > sets[v]->size()) {
            swap(sets[u], sets[v]);
        }
        FOR(it, *sets[u]) {
            if (!sets[v]->count(*it)) {
                sets[u]->erase(*it);
            }
        }
        delSet(sets[v]);
        return;
    }
    if (isComplement[u] && isComplement[v]) {
        isComplement[u] = isComplement[v] = 0;
        merge(u, v);
        isComplement[u] = 1;
        return;
    }
    if (isComplement[u]) {
        swap(isComplement[u], isComplement[v]);
        swap(sets[u], sets[v]);
    }
//printf("intersect %d %d %d %d\n", u, v, sets[u]->size(), sets[v]->size());
    if (isComplement[v]) {
        if (sets[u]->size() <= sets[v]->size()) {
            FOR(it, *sets[u]) {
                if (sets[v]->count(*it)) {
                    sets[u]->erase(*it);
                }
            }
            delSet(sets[v]);
        } else {
            isComplement[u] = 1;
            isComplement[v] = 0;
            merge(u, v);
            isComplement[u] = 1;
        }
        return;
    }
    assert(false);
}

inline void merge(int u, int v)
{
    if (!isComplement[u] && !isComplement[v]) {
        if (sets[u]->size() < sets[v]->size()) {
            swap(sets[u], sets[v]);
        }
        FOR(it, *sets[v]) {
            sets[u]->insert(*it);
        }
        delSet(sets[v]);
        return;
    }
    
    if (isComplement[u] && isComplement[v]) {
        isComplement[u] = isComplement[v] = 0;
        intersect(u, v);
        isComplement[u] = 1;
        return;
    }
    if (isComplement[v]) {
        swap(isComplement[u], isComplement[v]);
        swap(sets[u], sets[v]);
    }
//printf("merge %d %d %d %d\n", u, v, sets[u]->size(), sets[v]->size());
    if (isComplement[u]) {
        if (sets[u]->size() <= sets[v]->size()) {
            FOR(it, *sets[u]) {
                if (sets[v]->count(*it)) {
                    sets[u]->erase(*it);
                }
            }
            delSet(sets[v]);
        } else {
            FOR(it, *sets[v]) {
                sets[u]->erase(*it);
            }
        }
        return;
    }
    assert(false);
}

inline void solve(int u)
{
    if (child[u].size() == 0) {
        return;
    }
    int best = -1;
//printf("node = %d\n", u);
    for (int i = 0; i < child[u].size(); ++ i) {
        int v = child[u][i];
//printf("    child %d\n", v);
        solve(v);
        if (best == -1 || sets[v]->size() > sets[best]->size()) {
            best = v;
        }
    }
//printf("best on node %d = %d\n", u, best);
    sets[u] = sets[best];
    isComplement[u] = isComplement[best];
    if (oper[u] == 2) {
        assert(child[u].size() == 1);
        isComplement[u] ^= 1;
    } else if (oper[u] == 1) {
        for (int i = 0; i < child[u].size(); ++ i) {
            int v = child[u][i];
            if (v == best) {
                continue;
            }
            intersect(u, v);
        }
    } else if (oper[u] == 0) {
        for (int i = 0; i < child[u].size(); ++ i) {
            int v = child[u][i];
            if (v == best) {
                continue;
            }
            merge(u, v);
        }
    }
}

int main()
{
    for (int test = 1;scanf("%s", str) == 1; ++ test) {
        printf("Case %d: ", test);
        
        int n = strlen(str);
        vector<int> stack1, stack2;
        for (int i = 0; i < n; ++ i) {
            if (str[i] == '(') {
                stack1.push_back(i);
            } else if (str[i] == '{') {
                stack2.push_back(i);
            } else if (str[i] == ')') {
                match[stack1.back()] = i;
                stack1.pop_back();
            } else if (str[i] == '}') {
                match[stack2.back()] = i;
                stack2.pop_back();
            }
        }
        node = 0;
        int root = build(0, n - 1);
        solve(root);
        int answer = sets[root]->size();
        if (isComplement[root]) {
            answer = 1000000000 - answer;
        }
        delSet(sets[root]);
        printf("%d\n", answer);
    }
    return 0;
}

