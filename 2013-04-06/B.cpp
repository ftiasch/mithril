#include <cstdio>
#include <cstring>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 1000;

bool visit[N];
int n, graph[N][N], match[N];
std::vector <int> adjacent[N];

bool find(int i) {
    if (visit[i]) {
        return false;
    }
    visit[i] = true;
    foreach (iter, adjacent[i]) {
        int j = *iter;
        if (match[j] == -1 || find(match[j])) {
            match[j] = i;
            return true;
        }
    }
    return false;
}

void dfs(int i) {
    for (int j = 0; j < n; ++ j) {
        if (graph[i][j]) {
            graph[i][j] --;
            graph[j][i] --;
            dfs(j);
            adjacent[i].push_back(j);
        }
    }
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    if (m == 0) {
        puts("Impossible");
        return 0;
    }
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        graph[a][b] ++;
        graph[b][a] ++;
    }
    for (int i = 0; i < n; ++ i) {
        dfs(i);
    }
    memset(visit, 0, sizeof(visit));
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; ++ i) {
        find(i);
        memset(visit, 0, sizeof(visit));
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++ i) {
        printf("%d %d\n", i + 1, match[i] + 1);
    }
    return 0;
}
