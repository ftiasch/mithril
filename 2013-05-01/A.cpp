#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <iostream>
#include <algorithm>

const int N = 50000;
const int M = 300000 << 1;
const long long INF = 1000000000000000000LL;

int n, m, p[4], edge_count, first_edge[N], to[M], weight[M], next_edge[M];
long long minimum[1 << 4][N];

bool visit[N];

void add_edge(int u, int v, int w) {
    to[edge_count] = v;
    weight[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

int main() {
    scanf("%d%d", &n, &m);
    p[0] = 0;
    for (int i = 1; i < 4; ++ i) {
        scanf("%d", p + i);
        p[i] --;
    }
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a --;
        b --;
        add_edge(a, b, c);
        add_edge(b, a, c);
    }
    for (int mask = 0; mask < 1 << 4; ++ mask) {
        for (int i = 0; i < n; ++ i) {
            minimum[mask][i] = INF;
        }
    }
    for (int i = 0; i < 4; ++ i) {
        minimum[1 << i][p[i]] = 0;
    }
    for (int mask = 0; mask < 1 << 4; ++ mask) {
        for (int sub = mask; sub > 0; sub = sub - 1 & mask) {
            for (int i = 0; i < n; ++ i) {
                minimum[mask][i] = std::min(minimum[mask][i], minimum[sub][i] + minimum[mask ^ sub][i]);
            }
        }
        std::priority_queue <std::pair <long long, int> > queue;
        for (int i = 0; i < n; ++ i) {
            queue.push(std::make_pair(-minimum[mask][i], i));
        }
        while (!queue.empty()) {
            std::pair <long long, int> ret = queue.top();
            queue.pop();
            if (-ret.first != minimum[mask][ret.second]) {
                continue;
            }
            int u = ret.second;
            for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
                if (minimum[mask][u] + weight[iter] < minimum[mask][to[iter]]) {
                    minimum[mask][to[iter]] = minimum[mask][u] + weight[iter];
                    queue.push(std::make_pair(-minimum[mask][to[iter]], to[iter]));
                }
            }
        }
    }
    long long answer = INF;
    for (int i = 0; i < n; ++ i) {
        answer = std::min(answer, minimum[15][i]);
    }
    std::cout << answer << std::endl;
    return 0;
}
