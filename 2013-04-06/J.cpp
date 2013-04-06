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

int n, m;
vector<pair<int,int> > adj[maxn];

bool visited[maxn];
long long num[maxn];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int ai, bi, ci;
        scanf("%d%d%d", &ai, &bi, &ci);
        ai --, bi--;
        adj[ai].push_back(make_pair(bi, ci));
        adj[bi].push_back(make_pair(ai, -ci));
    }
    bool valid = true;
    queue<int> Q;
    for (int i = 0; i < n && valid; i++) {
        if (!visited[i]) {
            visited[i] = true;
            num[i] = 0;
            Q.push(i);
            while (!Q.empty() && valid) {
                int p = Q.front();
                Q.pop();
                FOR (it, adj[p]) {
                    int q = it->first, numq = num[p] + it->second;
                    if (!visited[q]) {
                        visited[q] = q;
                        num[q] = numq;
                        Q.push(q);
                    } else if (num[q] != numq) {
                        valid = false;
                        break;
                    }
                }
            }
        }
    }
    puts(valid ? "YES" : "NO");
}
