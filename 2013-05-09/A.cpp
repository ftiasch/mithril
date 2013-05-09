#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 30;
const int maxm = maxn * maxn;

vector<int> adj[maxm];
int n, m, degree[maxn], a[maxm], b[maxm];
int color[maxm], order[maxm];
int forbid[maxm][3];

inline bool flood(int u, int c)
{
    if (color[u] != -1) {
        return color[u] == c;
    }
    color[u] = c;
    for (int i = 0; i < adj[u].size(); ++ i) {
        if (!flood(adj[u][i], c ^ 1)) {
            return false;
        }
    }
    return true;
}

inline void output()
{
    puts("YES");
    for (int i = 0; i < m; ++ i) {
        if (i) {
            printf(" ");
        }
        printf("%d", color[i] + 1);
    }
    puts("");
}

inline void paint(int u, int c, int sign)
{
    for (int i = 0; i < adj[u].size(); ++ i) {
        int v = adj[u][i];
        forbid[v][c] += sign;
    }
}

inline bool dfs(int i)
{
    if (i == m) {
        output();
        return true;
    }
    int u = order[i];
    for (int c = 0; c < 3; ++ c) {
        if (forbid[u][c]) {
            continue;
        }
        color[u] = c;
        paint(u, c, 1);
        if (dfs(i + 1)) {
            return true;
        }
        paint(u, c, -1);
        
        if (i == 0) {
            break;
        }
    }
    return false;
}

inline bool cmp(const int &i, const int &j)
{
    return adj[i].size() > adj[j].size() || adj[i].size() == adj[j].size() && i < j;
}

int main()
{
    freopen("coloring.in", "r", stdin);
    freopen("coloring.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d", &a[i], &b[i]);
        -- a[i];
        -- b[i];
        ++ degree[a[i]];
        ++ degree[b[i]];
        for (int j = 0; j < i; ++ j) {
            if (a[i] == a[j] || a[i] == b[j] || b[i] == a[j] || b[i] == b[j]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    
    for (int i = 0; i < n; ++ i) {
        if (degree[i] >= 4) {
            puts("NO");
            return 0;
        }
    }
    
    memset(color, -1, sizeof(color));
    bool valid = true;
    for (int i = 0; i < m && valid; ++ i) {
        if (color[i] == -1) {
            valid &= flood(i, 0);
        }
    }
    
    if (valid) {
        output();
    } else {
        memset(color, -1, sizeof(color));
        
        int len = 0;
        for (int i = 0; i < m; ++ i) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                while (q.size()) {
                    int u = q.front();
                    order[len ++] = u;
                    q.pop();
                    for (int j = 0; j < adj[u].size(); ++ j) {
                        int v = adj[u][j];
                        if (color[v] == -1) {
                            color[v] = 0;
                            q.push(v);
                        }
                    }
                }
            }
        }
        
        memset(color, -1, sizeof(color));
        memset(forbid, 0, sizeof(forbid));
        if (!dfs(0)) {
            puts("NO");
        }
    }
    
    return 0;
}

