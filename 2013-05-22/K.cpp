#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
 
const int maxn = 300;
 
long long dist[2][maxn][maxn];
int edge[maxn][maxn];
bool adj[maxn][maxn], reach[2][maxn][maxn], answer[maxn];
 
int main()
{
    freopen("studies.in", "r", stdin);
    freopen("studies.out", "w", stdout);
     
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        -- a;
        -- b;
        adj[a][b] = true;
        edge[a][b] = c;
    }
    int now = 0, old = 1;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (adj[i][j]) {
                dist[now][i][j] = edge[i][j];
                reach[now][i][j] = true;
            }
        }
        dist[now][i][i] = 0;
        reach[now][i][i] = true;
    }
     
    for (int k = 0; k < n; ++ k) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if (adj[i][k] && adj[k][j] && reach[now][j][i]) {
                    if (edge[i][k] + edge[k][j] + dist[now][j][i] > 0) {
                        answer[k] = true;
                    }
                }
            }
        }
        now = 1 - now;
        old = 1 - old;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                dist[now][i][j] = dist[old][i][j];
                reach[now][i][j] = reach[old][i][j];
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if (reach[old][i][k] && reach[old][k][j]) {
                    if (!reach[now][i][j] || dist[now][i][j] < dist[old][i][k] + dist[old][k][j]) {
                        reach[now][i][j] = true;
                        dist[now][i][j] = dist[old][i][k] + dist[old][k][j];
                    }
                }
            }
        }
    }
     
    for (int i = 0; i < n; ++ i) {
        if (!answer[i]) {
            continue;
        }
        for (int j = 0; j < n; ++ j) {
            if (reach[now][i][j] && reach[now][j][i]) {
                answer[j] = true;
            }
        }
    }
     
    int cnt = 0;
    for (int i = 0; i < n; ++ i) {
        if (answer[i]) {
            ++ cnt;
        }
    }
    printf("%d\n", cnt);
    for (int i = 0; i < n; ++ i) {
        if (answer[i]) {
            -- cnt;
            printf("%d", i + 1);
            if (cnt) printf(" ");
        }
    }
    puts("");
     
    return 0;
}
