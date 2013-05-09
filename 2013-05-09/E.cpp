#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 5000;
const int M = 10000;

int n, m, a[N], b[N], a_order[N], b_order[N];
int edge_count, first_edge[N], to[M], next_edge[M];

bool by_a(int i, int j) {
    return a[i] > a[j];
}

bool by_b(int i, int j) {
    return b[i] > b[j];
}

bool visit[2][N];
int match[2][N], from[2][N];

void dfs(int u) {
    visit[0][u] = true;
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        int v = to[iter];
        if (!visit[1][v]) {
            from[1][v] = u;
            visit[1][v] = true;
            int u = match[1][v];
            if (u != -1 && !visit[0][u]) {
                visit[0][u] = true;
                from[0][u] = v;
                dfs(u);
            }
        }
    }
}

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    int k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        a_order[i] = i;
    }
    std::sort(a_order, a_order + n, by_a);
    for (int j = 0; j < m; ++ j) {
        scanf("%d", b + j);
        b_order[j] = j;
    }
    std::sort(b_order, b_order + m, by_b);
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
    while (k --) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        to[edge_count] = b;
        next_edge[edge_count] = first_edge[a];
        first_edge[a] = edge_count ++;
    }
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; ++ i) {
        if (match[0][a_order[i]] != -1) {
            continue;
        }
        memset(visit, 0, sizeof(visit));
        dfs(a_order[i]);
        for (int j = 0; j < m; ++ j) {
            int v = b_order[j];
            if (match[1][v] == -1 && visit[1][v]) {
                while (true) {
                    int u = from[1][v];
                    match[1][v] = u;
                    match[0][u] = v;
                    if (u == a_order[i]) {
                        break;
                    }
                    v = from[0][u];
                }
                break;
            }
        }
    }
    int answer = 0;
    int count = 0;
    for (int i = 0; i < n; ++ i) {
        if (match[0][i] != -1) {
            answer += a[i];
            count ++;
        }
    }
    for (int i = 0; i < m; ++ i) {
        if (match[1][i] != -1) {
            answer += b[i];
        }
    }
    printf("%d\n%d\n", answer, count);
    for (int i = 0; i < n; ++ i) {
        if (match[0][i] != -1) {
            for (int iter = first_edge[i]; iter != -1; iter = next_edge[iter]) {
                if (match[1][to[iter]] == i) {
                    count --;
                    printf("%d%c", iter + 1, " \n"[count == 0]);
                    break;
                }
            }
        }
    }
    return 0;
}
