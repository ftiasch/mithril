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

const int maxn = 200011;

vector<int> times[maxn];
int times0label[maxn];

int input[maxn][4];

int n, m;

vector<pair<int, int> > adj[maxn];

int findID(int a, int b)
{
    return lower_bound(times[a].begin(), times[a].end(), b) - times[a].begin() + times0label[a];
}

int prev[maxn], prevEdge[maxn];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &input[i][j]);
        }
        times[--input[i][0]].push_back(input[i][2]);
        times[--input[i][1]].push_back(input[i][3]);
    }
    for (int i = 0; i < n; i++) {
        sort(times[i].begin(), times[i].end());
        times[i].erase(unique(times[i].begin(), times[i].end()), times[i].end());
    }
    times0label[0] = 0;
    for (int i = 0; i < n; i++) {
        times0label[i + 1] = times0label[i] + times[i].size();
    }
    int N = times0label[n];
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < times[i].size(); j++) {
            adj[times0label[i] + j - 1].push_back(make_pair(times0label[i] + j, -1));
        }
    }
    int S = findID(input[m][0], input[m][2]);
    int T = findID(input[m][1], input[m][3]);
    for (int i = 0; i < m; i++) {
        adj[findID(input[i][0], input[i][2])].push_back(make_pair(findID(input[i][1], input[i][3]), i));
    }
    memset(prev, -1, sizeof(prev));
    prev[S] = -2;
    queue<int> Q;
    Q.push(S);
    while (!Q.empty()) {
        int p = Q.front();
        Q.pop();
        FOR (it, adj[p]) {
            if (prev[it->first] == -1) {
                prev[it->first] = p;
                prevEdge[it->first] = it->second;
                Q.push(it->first);
            }
        }
    }
    if (prev[T] == -1) {
        puts("Impossible");
    } else {
        int ptr = T;
        vector<int> ans;
        while (ptr != S) {
            if (prevEdge[ptr] >= 0) {
                ans.push_back(prevEdge[ptr]);
            }
            ptr = prev[ptr];
        }
        reverse(ans.begin(), ans.end());
        printf("%d\n", (int)ans.size());
        for (int i = 0; i < ans.size(); i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", ans[i] + 1);
        }
        puts("");
    }
}
