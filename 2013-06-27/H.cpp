#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using std::vector;

const int N = 50;

int cost[3][N][N];

struct Solver {
    int n, cost[N][N];

    Solver(int _n, int _cost[N][N]) {
        n = _n;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                cost[i][j] = -_cost[i][j];
            }
        }
    }

    int lx[N], ly[N], match[N], delta[N];
    bool vx[N], vy[N];

    bool find(int u) {
        if (vx[u]) {
            return false;
        }
        vx[u] = true;
        for (int v = 0; v < n; ++ v) {
            if (lx[u] + ly[v] == cost[u][v]) {
                vy[v] = true;
                if (match[v] == -1 || find(match[v])) {
                    match[v] = u;
                    return true;
                }
            } else {
                delta[v] = std::min(delta[v], lx[u] + ly[v] - cost[u][v]);
            }
        }
        return false;
    }

    void solve(int assignment[N]) {
        for (int i = 0; i < n; ++ i) {
            lx[i] = ly[i] = 0;
            for (int j = 0; j < n; ++ j) {
                lx[i] = std::max(lx[i], cost[i][j]);
            }
        }
        memset(match, -1, sizeof(match));
        for (int i = 0; i < n; ++ i) {
            while (true) {
                memset(vx, 0, sizeof(vx));
                memset(vy, 0, sizeof(vy));
                std::fill(delta, delta + n, INT_MAX);
                if (find(i)) {
                    break;
                }
                int d = INT_MAX;
                for (int i = 0; i < n; ++ i) {
                    if (!vy[i]) {
                        d = std::min(d, delta[i]);
                    }
                }
                for (int i = 0; i < n; ++ i) {
                    if (vx[i]) {
                        lx[i] -= d;
                    }
                    if (vy[i]) {
                        ly[i] += d;
                    }
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            assignment[match[i]] = i;
        }
    }
};

int assignment[2][N], done[2][N];

int main() {
    int test_count = 0;
    int n;
    while (scanf("%d", &n) == 1 && n) {
        for (int t = 0; t < 2; ++ t) {
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < n; ++ j) {
                    scanf("%d", &cost[t][i][j]);
                }
            }
        }
        Solver *solver = new Solver(n, cost[0]);
        solver->solve(assignment[0]);
        for (int i = 0; i < n; ++ i) {
            done[0][assignment[0][i]] = cost[0][i][assignment[0][i]];
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                cost[2][i][j] = std::max(cost[0][i][assignment[0][i]], done[0][j]) + cost[1][i][j];
            }
        }
        solver = new Solver(n, cost[2]);
        solver->solve(assignment[1]);
        printf("Case %d:\n", ++ test_count);
        int total = 0;
        for (int i = 0; i < n; ++ i) {
            printf("Worker %d: %d %d %d\n", i + 1, assignment[0][i] + 1, assignment[1][i] + 1, cost[2][i][assignment[1][i]]);
            total += cost[2][i][assignment[1][i]] - cost[0][i][assignment[0][i]] - cost[1][i][assignment[1][i]];
        }
        printf("Total idle time: %d\n", total);
    }
    return 0;
}
