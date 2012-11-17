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

const int maxn = 1024;

vector<int> adj[maxn];

int dist[maxn];

int main()
{
    int n, f, m;
    scanf("%d%d%d", &n, &f, &m);
    queue<int> Q;
    memset(dist, -1, sizeof(dist));
    for (int i = 0; i < f; i++) {
        int ai;
        scanf("%d", &ai);
        dist[ai] = 0;
        Q.push(ai);
    }
    for (int i = 0; i < m; i++) {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        adj[ai].push_back(bi);
        adj[bi].push_back(ai);
    }
    while (!Q.empty()) {
        int p = Q.front();
        Q.pop();
        FOR(q, adj[p]) {
            if (dist[*q] < 0) {
                dist[*q] = dist[p] + 1;
                Q.push(*q);
            }
        }
    }
    int maxv = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] < 0) {
            maxv = -1;
            break;
        } else {
            maxv = max(maxv, dist[i]);
        }
    }
    int id = find(dist, dist + n, maxv) - dist;
    printf("%d\n", id);
}
