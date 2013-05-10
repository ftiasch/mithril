#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <map>
#include <iostream>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 1000;

int n, m;
std::vector <int> graph[N];

int dist[N][N], sumB[N][N], valueB[N][N];
std::map <long long, int> count;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        u --, v --;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 0; i < n; ++ i) {
        std::sort(ALL(graph[i]));
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            dist[i][j] = INT_MAX;
        }
    }
    for (int target = 0; target < n; ++ target) {
        std::vector <int> queue;
        queue.push_back(target);
        dist[target][target] = 0;
        for (int head = 0; head < (int)queue.size(); ++ head) {
            int u = queue[head];
            foreach (iter, graph[u]) {
                if (dist[u][target] + 1 < dist[*iter][target]) {
                    dist[*iter][target] = dist[u][target] + 1;
                    queue.push_back(*iter);
                }
            }
        }
        valueB[target][target] = sumB[target][target] = 0;
        for (int i = 1; i < n; ++ i) {
            int u = queue[i];
            foreach (iter, graph[u]) {
                int v = *iter;
                if (dist[u][target] == dist[v][target] + 1) {
                    sumB[u][target] = sumB[v][target] + u + 1;
                    valueB[u][target] = valueB[v][target] + sumB[u][target];
                    break;
                }
            }
        }
    }
    int r;
    scanf("%d", &r);
    while (r --) {
        int length;
        scanf("%d", &length);
        int now;
        scanf("%d", &now);
        now --, length --;
        long long value = 0;
        int current = 0;
        while (length --) {
            int next;
            scanf("%d", &next);
            next --;
            value += valueB[now][next];
            value += (long long)current * sumB[now][next];
            current += dist[now][next];
            now = next;
        }
        value += (current + 1) * (now + 1);
        count[value] ++;
        std::cout << value;
        if (count[value] > 1) {
            std::cout << "#" << count[value];
        }
        std::cout << std::endl;
    }
    return 0;
}
