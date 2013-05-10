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

const int maxn = 10001;
const double INF = 1e100;
const double EPS = 1e-11;

struct Edge {
    int dest, len, speed;
    double time;
    int id;

    Edge(int dest, int len, int speed, int id) : dest(dest), len(len), speed(speed), id(id){}
};

int n, m, T;
vector<Edge> adj[maxn];

double dist[maxn];
pair<int,int> prev[maxn];

bool check(double mid, bool flag = false)
{
    for (int i = 0; i < n; i++) {
        FOR (it, adj[i]) {
            it->time = (double)it->len / (it->speed + mid);
        }
        dist[i] = INF;
    }
    dist[0] = 0;
    priority_queue<pair<double,int> > Q;
    Q.push(make_pair(0, 0));
    while (!Q.empty()) {
        double distp = -Q.top().first;
        int p = Q.top().second;
        Q.pop();
        if (distp > dist[p] + EPS) {
            continue;
        }
        if (p == n - 1 && dist[p] < T) {
            return true;
        }
        FOR (it, adj[p]) {
            int q = it->dest;
            if (dist[q] > dist[p] + it->time) {
                if (flag) {
                    prev[q] = make_pair(p, it->id);
                }
                dist[q] = dist[p] + it->time;
                Q.push(make_pair(-dist[q], q));
            }
        }
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    double hi = 0;
    for (int i = 0; i < m; i++) {
        int ai, bi, si, li;
        scanf("%d%d%d%d", &ai, &bi, &si, &li);
        ai --, bi --;
        adj[ai].push_back(Edge(bi, li, si, i));
        adj[bi].push_back(Edge(ai, li, si, i));
        hi += li;
    }
    scanf("%d", &T);
    hi /= T;
    double lo = 0;
    for (int i = 0; i < 50; i++) {
        double mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    check(lo, true);
    vector<int> ans;
    int ptr = n - 1;
    while (ptr != 0) {
        ans.push_back(prev[ptr].second);
        ptr = prev[ptr].first;
    }
    reverse(ans.begin(), ans.end());
    printf("%.10f %d\n", lo, (int)ans.size());
    for (int i = 0; i < ans.size(); i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", ans[i] + 1);
    }
    puts("");
}
