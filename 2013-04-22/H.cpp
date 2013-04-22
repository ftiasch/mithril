#include <cstdio>
#include <climits>
#include <cstring>
#include <string>
#include <queue>
#include <iostream>
#include <algorithm>

const int N = 30;

int n, win[N], deg[N], duel[N][N];
std::string names[N];

const int V = N + 2;

int capacity[V][V];

void add_edge(int a, int b, int c) {
    capacity[a][b] += c;
}

int level[V];
std::queue <int> queue;

bool bfs(int source, int target) {
    memset(level, -1, sizeof(level));
    level[source] = 0;
    queue.push(source);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int v = 0; v <= target; ++ v) {
            if (capacity[u][v] > 0 && level[v] == -1) {
                level[v] = level[u] + 1;
                queue.push(v);
            }
        }
    }
    return level[target] != -1;
}

int dfs(int u, int target, int left) {
    if (u == target) {
        return left;
    }
    int delta = 0;
    for (int v = 0; v <= target; ++ v) {
        if (capacity[u][v] > 0 && level[u] + 1 == level[v]) {
            int ret = dfs(v, target, std::min(left - delta, capacity[u][v]));
            capacity[u][v] -= ret;
            capacity[v][u] += ret;
            delta += ret;
            if (delta == left) {
                break;
            }
        }
    }
    return delta;
}

void solve(int winner) {
    int max_win = win[winner];
    for (int i = 0; i < n; ++ i) {
        max_win += duel[winner][i];
    }
    int source = n;
    int target = n + 1;
    memset(capacity, 0, sizeof(capacity));
    for (int i = 0; i < n; ++ i) {
        deg[i] = 0;
        for (int j = 0; j < n; ++ j) {
            if (i != winner && j != winner) {
                deg[i] += duel[i][j];
                add_edge(i, j, duel[i][j]);
            }
        }
    }
    int value = 0;
    for (int i = 0; i < n; ++ i) {
        if (i == winner) {
            continue;
        }
        value += deg[i] + 2 * win[i];
        add_edge(source, i, deg[i] + 2 * win[i]);
        add_edge(i, target, 2 * max_win);
    }
    while (bfs(source, target)) {
        value -= dfs(source, target, INT_MAX);
    }
    if (value > 0) {
        printf("%s cannot win because of the following teams:\n  ", names[winner].c_str());
        bool first = true;
        for (int i = 0; i < n; ++ i) {
            if (level[i] != -1) {
                if (first) {
                    first = false;
                } else {
                    printf(", ");
                }
                printf("%s", names[i].c_str());
            }
        }
        puts("");
    } else {
        printf("%s can win\n", names[winner].c_str());
    }
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++ i) {
        std::cin >> names[i] >> win[i];
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            std::cin >> duel[i][j];
        }
    }
    for (int i = 0; i < n; ++ i) {
        solve(i);
    }
    return 0;
}
