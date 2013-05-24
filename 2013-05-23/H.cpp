#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>

const int N = 100 + 2;

const int TRIES = 150;

const double INF = 1e9;
const double EPS = 1e-12;

int n, h, b[N], c[N][N];

double capacity[N][N];

int level[N];

bool bfs(int source, int target) {
    memset(level, -1, sizeof(level));
    std::queue <int> queue;
    queue.push(source);
    level[source] = 0;
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int v = 0; v <= target; ++ v) {
            if (capacity[u][v] > EPS && level[v] == -1) {
                level[v] = level[u] + 1;
                queue.push(v);
            }
        }
    }
    return level[target] != -1;
}

double dfs(int u, int target, double limit) {
    if (u == target) {
        return limit;
    }
    double delta = 0.0;
    for (int v = 0; v <= target; ++ v) {
        if (capacity[u][v] > EPS && level[v] == level[u] + 1) {
            double ret = dfs(v, target, std::min(limit - delta, capacity[u][v]));
            capacity[u][v] -= ret;
            capacity[v][u] += ret;
            delta += ret;
            if (limit - delta <= EPS) {
                break;
            }
        }
    }
    return delta;
}

double solve(double lambda) {
    int source = n;
    int target = n + 1;
    memset(capacity, 0, sizeof(capacity));
    for (int i = 0; i < n; ++ i) {
        capacity[source][i] += b[i];
        capacity[i][target] += lambda;
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            capacity[i][j] += c[i][j];
        }
    }
    while (bfs(source, target)) {
        dfs(source, target, INF);
    }
    int size = 0;
    double ret = 0.0;
    for (int j = 0; j < n; ++ j) {
        if (level[j] == -1) {
            size ++;
            ret += b[j];
            for (int i = 0; i < n; ++ i) {
                if (level[i] != -1) {
                    ret += c[i][j];
                }
            }
        }
    }
    assert(size > 0);
    return ret / size;
}

int main() {
    int test_count = 0;
    while (scanf("%d%d", &n, &h) == 2 && n) {
        double lambda = 0.0;
        for (int i = 0; i < n; ++ i) {
            scanf("%d", b + i);
            lambda += b[i];
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                scanf("%d", &c[i][j]);
            }
        }
        lambda /= n;
        for (int _ = 0; _ < TRIES; ++ _) {
            lambda = solve(lambda + EPS);
        }
        printf("Case %d:\n", ++ test_count);
        int size = 0;
        for (int i = 0; i < n; ++ i) {
            size += level[i] == -1;
        }
        for (int i = 0; i < n; ++ i) {
            printf("%.12f%c", level[i] == -1 ? (double)h / size : 0.0, " \n"[i == n - 1]);
        }
    }
    return 0;
}
