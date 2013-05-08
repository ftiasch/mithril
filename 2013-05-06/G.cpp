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

const int maxn = 3000;
vector<int> adj[maxn];

int n, m;
int degree[maxn];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        ai --, bi --;
        adj[ai].push_back(bi);
        adj[bi].push_back(ai);
        degree[ai] ++;
        degree[bi] ++;
    }
    int turns = n / 3 * 2;
    while (turns --) {
        int minp = -1;
        for (int i = 0; i < n; i++) {
            if (degree[i] >= 0 && (minp < 0 || degree[i] < degree[minp])) {
                minp = i;
            }
        }
        FOR (it, adj[minp]) {
            if (degree[*it] >= 0) {
                degree[*it] --;
            }
        }
        degree[minp] = -1;
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (degree[i] < 0) {
            continue;
        }
        assert(degree[i] == n / 3 - 1);
        ans.push_back(i);
    }
    assert(ans.size() == n / 3);
    for (int i = 0; i < ans.size(); i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", ans[i] + 1);
    }
    puts("");
}
