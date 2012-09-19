#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100000;

int n, m;
vector <int> graph[N];

bool valid;
vector <pair <int, int> > choice;

bool visit[N];
int size;

bool dfs(int p, int u) {
    size ++;
    visit[u] = true;
    int degree = p != -1;
    for (vector <int> :: iterator iter = graph[u].begin(); iter != graph[u].end(); ++ iter) {
        int v = *iter;
        if (!visit[v]) {
            degree += dfs(u, v);
        }
    }
    if (p != -1 && (degree & 1) == 1) {
        choice.push_back(make_pair(p, u));
        return true;
    }
    return false;
}

int main() {
    freopen("oddfactor.in", "r", stdin);
    freopen("oddfactor.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    valid = true;
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < n; ++ i) {
        if (!visit[i]) {
            size = 0;
            dfs(-1, i);
            valid &= (size & 1) == 0;
        }
    }
    if (!valid) {
        puts("-1");
    } else {
        printf("%d\n", (int)choice.size());
        for (int i = 0; i < (int)choice.size(); ++ i) {
            printf("%d %d\n", choice[i].first + 1, choice[i].second + 1);
        }
    }
    return 0;
}
