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

const int maxn = 4444;

int n, k;
int mass[maxn], cost[maxn];

int main()
{
    scanf("%d%d", &n, &k);
    map<int,vector<int> > M;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", mass + i, cost + i);
        M[mass[i]].push_back(cost[i]);
    }
    vector<int> sz;
    FOR (it, M) {
        sz.push_back(it->second.size());
    }
    sort(sz.rbegin(), sz.rend());
    if (sz.size() < k) {
        printf("0 0\n");
        return 0;
    }
    int sets = sz[k - 1];
    vector<int> setCosts;
    FOR (it, M) {
        if (it->second.size() >= sets) {
            vector<int> costs = it->second;
            sort(costs.rbegin(), costs.rend());
            int sum = 0;
            for (int i = 0; i < sets; i++) {
                sum += costs[i];
            }
            setCosts.push_back(sum);
        }
    }
    sort(setCosts.rbegin(), setCosts.rend());
    int ret = 0;
    for (int i = 0; i < k; i++) {
        ret += setCosts[i];
    }
    cout << sets << " " << ret << endl;
}

