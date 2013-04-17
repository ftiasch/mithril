#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

const int N = 30;

int n, score[N];
char result[N][N + 1];

const int V = N * N + N + 2;
const int E = (N * N * 3 + N) * 2;

int edge_count, first_edge[V], to[E], capacity[E], next_edge[E];

void _add_edge(int u, int v, int w) {
    to[edge_count] = v;
    capacity[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

void add_edge(int a, int b, int c) {
//printf("%d -> %d: %d\n", a, b, c);
    _add_edge(a, b, c);
    _add_edge(b, a, 0);
}

int level[V];

bool bfs(int source, int target) {
    memset(level, -1, sizeof(level));
    level[target] = 0;
    std::queue <int> queue;
    queue.push(target);
    while (!queue.empty() && level[source] == -1) {
        int u = queue.front();
        queue.pop();
        for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
            if (capacity[iter ^ 1] > 0 && level[to[iter]] == -1) {
                level[to[iter]] = level[u] + 1;
                queue.push(to[iter]);
            }
        }
    }
    return level[source] != -1;
}

int dfs(int source, int target, int left) {
    if (source == target) { 
        return left;
    }
    int delta = left;
    for (int iter = first_edge[source]; iter != -1; iter = next_edge[iter]) {
        if (capacity[iter] > 0 && level[to[iter]] + 1 == level[source]) {
            int tmp = dfs(to[iter], target, std::min(delta, capacity[iter]));
            capacity[iter] -= tmp;
            capacity[iter ^ 1] += tmp;
            delta -= tmp;
            if (delta == 0) {
                break;
            }
        }
    }
    return left - delta;
}

bool can_win(int winner) {
    memset(score, 0, sizeof(score));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (result[i][j] == 'd') {
                score[i] ++;
            }
            if (result[i][j] == '1') {
                score[i] += 2;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (i != winner && result[winner][i] == '.') {
            score[winner] += 2;
        }
    }
//for (int i = 0; i < n; ++ i) {
//    printf("%d, ", score[i]);
//}
//puts("");
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
    int source = n * n + n;
    int target = source + 1;
    for (int i = 0; i < n; ++ i) {
        if (score[i] > score[winner]) {
            return false;
        }
        add_edge(source, i, score[winner] - score[i]);
    }
    int total = n;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            if (i != winner && j != winner && result[i][j] == '.') {
                add_edge(i, total, 2);
                add_edge(j, total, 2);
                add_edge(total ++, target, 2);
            }
        }
    }
    int answer = 0;
    while (bfs(source, target)) {
        answer += dfs(source, target, INT_MAX);
    }
    for (int iter = first_edge[target]; iter != -1; iter = next_edge[iter]) {
        if (capacity[iter ^ 1] > 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            scanf("%s", result[i]);
        }
        bool first = true;
        for (int i = 0; i < n; ++ i) {
            if (can_win(i)) {
                if (first) {
                    first = false;
                } else {
                    putchar(' ');
                }
                printf("%d", i + 1);
            }
        }
        puts("");
    }
    return 0;
}
