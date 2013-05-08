#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

const int N = 500;

int n, m, r, t, k;
bool can[N][N];

int visit_count, visit[N * N], match[N];

bool find(int u) {
    if (visit[u] == visit_count) {
        return false;
    }
    visit[u] = visit_count;
    for (int v = 0; v < m; ++ v) {
        if (!can[u % n][v]) {
            continue;
        }
        if (match[v] == -1 || find(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &r, &t, &k);
    memset(can, 0, sizeof(can));
    while (k --) {
        int a, b;
        scanf("%d%d", &a, &b);
        can[-- a][-- b] = true;
    }
    visit_count = 0;
    memset(visit, -1, sizeof(visit));
    memset(match, -1, sizeof(match));
    std::queue <int> queue;
    for (int i = 0; i < n; ++ i) {
        if (r <= t) {
            queue.push(i);
        }
    }
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        if (find(u)) {
            if (r * (u / n + 2) <= t) {
                queue.push(u + n);
            }
            visit_count ++;
        }
    }
    int problem = 0;
    int penalty = 0;
    for (int i = 0; i < m; ++ i) {
        if (match[i] != -1) {
            problem ++;
            penalty += r * (match[i] / n + 1);
        }
    }
    std::cout << problem << " " << penalty << std::endl;
    for (int i = 0; i < m; ++ i) {
        if (match[i] != -1) {
            std::cout << match[i] % n + 1 << " " <<  i + 1 << " " << r * (match[i] / n) << std::endl;
        }
    }
    return 0;
}
