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

const int maxn = 111111;
const long long inf = 1LL << 60;

int n, k;
vector<pair<int,int> > adj[maxn];

long long minlen[2][maxn], maxlen[2][maxn];
int leafCount[maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int ai, bi, ci;
        scanf("%d%d%d", &ai, &bi, &ci);
        ai --, bi --;
        adj[ai].push_back(make_pair(bi, ci));
        adj[bi].push_back(make_pair(ai, ci));
    }
    k = 0;
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            k ++;
        } else {
            root = i;
        }
    }
    if (n == 1) {
        puts("0");
        puts("0");
        return 0;
    } else if (n == 2) {
        int len = adj[0][0].second;
        printf("%d\n%d\n", len, len);
        return 0;
    }
    vector<int> parent(n, -1);
    vector<int> order, lenToParent(n, 0);
    parent[root] = -2;
    order.push_back(root);
    for (int i = 0; i < order.size(); i++) {
        int p = order[i];
        FOR (it, adj[p]) {
            int q = it->first;
            if (parent[q] == -1) {
                parent[q] = p;
                lenToParent[q] = it->second;
                order.push_back(q);
            }
        }
    }
    for (int i = order.size() - 1; i >= 0; i--) {
        int p = order[i];
        if (adj[p].size() == 1) {
            minlen[0][p] = maxlen[0][p] = 0;
            minlen[1][p] = maxlen[1][p] = 0;
            leafCount[p] = 1;
        } else {
            minlen[0][p] = maxlen[0][p] = 0;
            minlen[1][p] = inf;
            maxlen[1][p] = -inf;
            leafCount[p] = 0;
            FOR (it, adj[p]) {
                int q = it->first;
                if (q == parent[p]) {
                    continue;
                }
                leafCount[p] += leafCount[q];
                long long min0 = minlen[0][p], min1 = minlen[1][p];
                long long max0 = maxlen[0][p], max1 = maxlen[1][p];
                minlen[0][p] = min0 + minlen[0][q];
                minlen[1][p] = min(min1 + minlen[0][q], min0 + minlen[1][q]);
                maxlen[0][p] = max0 + maxlen[0][q];
                maxlen[1][p] = max(max1 + maxlen[0][q], max0 + maxlen[1][q]);
            }
        }
        if (p != root) {
            int a = leafCount[p], b = k - a;
            minlen[0][p] += (a % 2 == 1 && (b - k % 2) % 2 == 1 ? 1 : 0) * (long long)lenToParent[p];
            minlen[1][p] += ((a - 1) % 2 == 1 && b % 2 == 1 ? 1 : 0) * (long long)lenToParent[p];
            maxlen[0][p] += min(a, b - k % 2) * (long long)lenToParent[p];
            maxlen[1][p] += min(a - 1, b) * (long long)lenToParent[p];
        }
    }
    long long minv = minlen[k % 2][root];
    long long maxv = maxlen[k % 2][root];
    cout << minv << endl;
    cout << maxv << endl;
}
