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

const int maxn = 100;

int parent[maxn];

int findRoot(int a)
{
    return parent[a] >= 0 ? parent[a] = findRoot(parent[a]) : a;
}

int n, m, MOD;

vector<pair<int,pair<int,int> > > edges;

int ma[maxn][maxn];

int solve(const vector<pair<int,int> > &es)
{
    vector<int> nodes;
    for (int i = 0; i < es.size(); i++) {
        nodes.push_back(es[i].first);
        nodes.push_back(es[i].second);
    }
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    int N = nodes.size();
    memset(ma, 0, sizeof(ma));
    for (int i = 0; i < es.size(); i++) {
        int ai = lower_bound(nodes.begin(), nodes.end(), es[i].first) - nodes.begin();
        int bi = lower_bound(nodes.begin(), nodes.end(), es[i].second) - nodes.begin();
        ma[ai][bi] --;
        ma[bi][ai] --;
        ma[ai][ai] ++;
        ma[bi][bi] ++;
    }
    N --;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ma[i][j] = (ma[i][j] % MOD + MOD) % MOD;
        }
    }
    int det = 1;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            while (ma[j][i] != 0) {
                det = (MOD - det) % MOD;
                for (int k = 0; k < N; k++) {
                    swap(ma[i][k], ma[j][k]);
                }
                int times = ma[j][i] / ma[i][i];
                for (int k = 0; k < N; k++) {
                    ma[j][k] = (ma[j][k] + MOD - (long long)ma[i][k] * times % MOD) % MOD;
                }
            }
        }
        det = (long long)det * ma[i][i] % MOD;
    }
    return det;
}


int main()
{
    while (scanf("%d%d%d", &n, &m, &MOD) == 3 && n) {
        edges.clear();
        for (int i = 0; i < m; i++) {
            int ai, bi, ci;
            scanf("%d%d%d", &ai, &bi, &ci);
            ai --, bi --;
            edges.push_back(make_pair(ci, make_pair(ai, bi)));
        }
        sort(edges.begin(), edges.end());
        memset(parent, -1, sizeof(parent));
        long long ans = 1LL;
        for (int i = 0; i < edges.size(); ) {
            int ni = i;
            while (ni < edges.size() && edges[i].first == edges[ni].first) {
                ni ++;
            }
            for (int j = i; j < ni; j++) {
                int &ai = edges[j].second.first;
                int &bi = edges[j].second.second;
                ai = findRoot(ai);
                bi = findRoot(bi);
            }
            for (int j = i; j < ni; j++) {
                int ai = edges[j].second.first;
                int bi = edges[j].second.second;
                ai = findRoot(ai);
                bi = findRoot(bi);
                if (ai != bi) {
                    parent[ai] = bi;
                }
            }
            for (int j = 0; j < n; j++) {
                if (parent[j] < 0) {
                    vector<pair<int,int> > es;
                    for (int k = i; k < ni; k++) {
                        int ai = edges[k].second.first;
                        int bi = edges[k].second.second;
                        if (findRoot(ai) == j && findRoot(bi) == j) {
                            es.push_back(make_pair(ai, bi));
                        }
                    }
                    ans = ans * solve(es) % MOD;
                }
            }
            i = ni;
        }
        int comps = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] < 0) {
                comps ++;
            }
        }
        if (comps > 1) {
            ans = 0;
        }
        ans = (ans % MOD + MOD) % MOD;
        printf("%d\n", (int)ans);
    }
}
