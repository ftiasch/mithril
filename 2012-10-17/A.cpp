#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 200000;
const int INF = 1000000000;

int n, maximum[N][2];
bool valid[N];
vector <int> adjacent[N];

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

void update(int &x, int a) {
    x = max(x, a);
}

void dfs(int p, int u) {
    int sum = 0;
    vector <int> delta;
    foreach (iter, adjacent[u]) {
        int v = *iter;
        if (v != p) {
            dfs(u, v);
            sum += maximum[v][0];
            if (maximum[v][1] >= 0) {
                delta.push_back(maximum[v][1] - maximum[v][0]);
            }
        }
    }
    sort(delta.begin(), delta.end(), greater <int>());
    maximum[u][1] = -INF;
    if (valid[u]) {
        update(maximum[u][1], sum);
    }
    if ((int)delta.size() >= 1) {
        update(maximum[u][1], sum + delta[0]);
    }
    maximum[u][0] = max(maximum[u][1], sum);
    if (valid[u] && (int)delta.size() >= 1) {
        update(maximum[u][0], sum + delta[0] + 1);
    }
    if ((int)delta.size() >= 2) {
        update(maximum[u][0], sum + delta[0] + delta[1] + 1);
    }
}

int main() {
    freopen("athletic.in", "r", stdin);
    freopen("athletic.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        adjacent[a].push_back(b);
        adjacent[b].push_back(a);
    }
    memset(valid, 0, sizeof(valid));
    if (true) {
        int k;
        scanf("%d", &k);
        while (k --) {
            int x;
            scanf("%d", &x);
            x --;
            valid[x] = true;
        }
    }
    dfs(-1, 0);
    printf("%d\n", maximum[0][0]);
    return 0;
}
