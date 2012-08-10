#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10001;

int n, m, weight[N];
bool isRoot[N];
long long maximum[N][2];
vector <int> depends[N], choice;

void dfs(int u) {
    maximum[u][0] = 0;
    maximum[u][1] = weight[u];
    for (vector <int> :: iterator iter = depends[u].begin(); iter != depends[u].end(); ++ iter) {
        int v = *iter;
        dfs(v);
        maximum[u][0] += max(maximum[v][0], maximum[v][1]);
        maximum[u][1] += maximum[v][1];
    }
}

void construct(int u, int t) {
    if (t) {
        choice.push_back(u);
    }
    for (vector <int> :: iterator iter = depends[u].begin(); iter != depends[u].end(); ++ iter) {
        int v = *iter;
        if (t) {
            construct(v, t);
        } else {
            construct(v, maximum[v][0] < maximum[v][1]);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", weight + i);
    }
    memset(isRoot, true, sizeof(isRoot));
    for (int i = 1; i <= m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        depends[a].push_back(b);
        isRoot[b] = false;
    }
    for (int i = 1; i <= n; ++ i) {
        if (isRoot[i]) {
            dfs(i);
        }
    }
    long long result = 0;
    for (int i = 1; i <= n; ++ i) {
        if (isRoot[i]) {
            result += max(maximum[i][0], maximum[i][1]);
            construct(i, maximum[i][0] < maximum[i][1]);
        }
    }
    cout << result << endl;
    sort(choice.begin(), choice.end());
    for (int i = 0; i < (int)choice.size(); ++ i) {
        printf("%d%c", choice[i], i == (int)choice.size() - 1? '\n': ' ');
    }
    return 0;
}
