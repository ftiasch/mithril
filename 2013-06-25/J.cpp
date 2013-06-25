#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000;
const int M = 1000000;

int n, m, color[N], degree[N];
std::vector <int> graph[N];

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d", color + i);
            color[i] --;
            graph[i].clear();
        }
        for (int i = 0; i < m; ++ i) {
            int u, v;
            scanf("%d%d", &u, &v);
            graph[-- u].push_back(--v);
        }
        int answer = INT_MAX;
        for (int start = 0; start < 2; ++ start) {
            memset(degree, 0, sizeof(degree));
            for (int u = 0; u < n; ++ u) {
                foreach (iter, graph[u]) {
                    degree[*iter] ++;
                }
            }
            std::queue <int> queue[2];
            for (int u = 0; u < n; ++ u) {
                if (!degree[u]) {
                    queue[color[u]].push(u);
                }
            }
            int count = -1;
            int done = 0;
            int now = start;
            while (done < n) {
                count ++;
                while (!queue[now].empty()) {
                    done ++;
                    int u = queue[now].front();
                    queue[now].pop();
                    foreach (iter, graph[u]) {
                        int v = *iter;
                        degree[v] --;
                        if (!degree[v]) {
                            queue[color[v]].push(v);
                        }
                    }
                }
                now ^= 1;
            }
            answer = std::min(answer, count);
        }
        printf("%d\n", answer);
    }
    return 0;
}
