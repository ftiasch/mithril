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

const int maxn = 1 << 10;
const int maxm = 20000;
const int maxr = maxm * 2 + maxn * 2 + maxm;

map<string, int> mapping;

int getCode(string s)
{
    while (isspace(s[0])) {
        s = s.substr(1);
    }
    while (isspace(s[s.size() - 1])) {
        s = s.substr(0, s.size() - 1);
    }
    if (mapping.count(s) == 0) {
        int ret = mapping.size();
        return mapping[s] = ret;
    }
    return mapping[s];
}

char buf[maxn];

pair<int,int> readEdge()
{
    fgets(buf, maxn, stdin);
    string s = buf;
    int pos = s.find(',');
    assert(pos >= 0);
    string fst = s.substr(0, pos);
    string snd = s.substr(pos + 1);
    return make_pair(getCode(fst), getCode(snd));
}

int n, m, N;

pair<int,int> requests[maxn];
pair<int,int> airlines[maxm];

bool visOut[maxn], visIn[maxn];

int lnk[maxr];
int flag[maxn], flags;

vector<pair<int, pair<int,int> > > adj[maxn];

inline int get(int startingCity, int airline)
{
    if (airlines[airline].first == startingCity) {
        return airlines[airline].second;
    } else if (airlines[airline].second == startingCity) {
        return airlines[airline].first;
    } else {
        return -1;
    }
}

bool find(int p)
{
    if (flag[p] == flags)
        return false;
    flag[p] = flags;
    for (int i = 0; i < adj[p].size(); i++) {
        int q = adj[p][i].first;
        if (lnk[q] == -1 || find(lnk[q])) {
            lnk[q] = p;
            return true;
        }
    }
    return false;
}

int transferLabel[maxm * 2 + maxn * 2];
int transfers;

bool solve()
{
    memset(visIn, false, sizeof(visIn));
    memset(visOut, false, sizeof(visOut));
    for (int i = 0; i < n; i++) {
        if (visOut[requests[i].first] || visIn[requests[i].second]) {
            return false;
        }
        visOut[requests[i].first] = visIn[requests[i].second] = true;
    }
    memset(transferLabel, -1, sizeof(transferLabel));
    transfers = 0;
    for (int i = 0; i < N; i++) {
        if (i >= maxn || !visIn[i] && !visOut[i]) {
            transferLabel[i] = transfers++;
        }
    }
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        for (int j = 0; j < m; j++) {
            if (requests[i] == airlines[j] || 
                    requests[i].first == airlines[j].second && requests[i].second == airlines[j].first) {
                adj[i].push_back(make_pair(transfers + j, make_pair(j, -1)));
            }
        }
        map<int, int> M;
        for (int j = 0; j < m; j++) {
            int transferCity = get(requests[i].first, j);
            if (transferCity >= 0 && transferLabel[transferCity] >= 0) {
                M[transferCity] = j;
            }
        }
        for (int j = 0; j < m; j++) {
            int transferCity = get(requests[i].second, j);
            if (transferCity >= 0 && transferLabel[transferCity] >= 0 && M.count(transferCity)) {
                int k = M[transferCity];
                adj[i].push_back(make_pair(transferLabel[transferCity], make_pair(k, j)));
            }
        }
    }
    memset(lnk, -1, sizeof(lnk));
    for (int i = 0; i < n; i++) {
        flags++;
        if (!find(i)) {
            return false;
        }
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < transfers + m; i++) {
        if (lnk[i] >= 0) {
            ans[lnk[i]] = i;
        }
    }
    puts("YES");
    for (int i = 0; i < n; i++) {
        assert(ans[i] >= 0);
        bool found = false;
        for (int j = 0; j < adj[i].size(); j++) {
            if (adj[i][j].first == ans[i]) {
                pair<int,int> &ref = adj[i][j].second;
                if (ref.second == -1) {
                    printf("1 %d\n", ref.first + 1);
                } else {
                    printf("2 %d %d\n", ref.first + 1, ref.second + 1);
                }
                found = true;
                break;
            }
        }
        assert(found);
    }
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    fgets(buf, maxn, stdin);
    for (int i = 0; i < n; i++) {
        requests[i] = readEdge();
    }
    for (int i = 0; i < m; i++) {
        airlines[i] = readEdge();
    }
    N = mapping.size();
    if (!solve()) {
        puts("NO");
    }
}
