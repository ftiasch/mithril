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

const int maxn = 128;

int n, m;
vector<int> adj[maxn];
int price[maxn];

int main()
{
    int tests, cas = 0;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            scanf("%d", &price[i]);
        }
        for (int i = 0; i < m; i++) {
            int ai, bi;
            scanf("%d%d", &ai, &bi);
            adj[ai].push_back(bi);
        }
        int now = 0, ans = 0;
        while (adj[now].size() > 0) {
            int bestNode = -1;
            FOR (it, adj[now]) {
                if (bestNode < 0 || price[*it] > price[bestNode]) {
                    bestNode = *it;
                }
            }
            ans += price[bestNode];
            now = bestNode;
        }
        cout << "Case "<< ++cas << ": " << ans << " " << now << endl;
        //printf("Case %d: %d %d\n", ++cas, ans, now);
    }
}
