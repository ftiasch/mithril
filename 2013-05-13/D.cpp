#include <cstdio>
#include <cstring>
#include <climits>
#include <deque>

const int N = 1400;
const int M = 700;

int get_cost(int i, int j) {
    return i * 4 - j;
}

const int V = N + M + 2;
const int E = (N + M + N * 4) * 2;

int edge_count, first_edge[V], to[E], capacity[E], cost[E], next_edge[E];

void my_add_edge(int u, int v, int ca, int co) {
    to[edge_count] = v;
    capacity[edge_count] = ca;
    cost[edge_count] = co;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

void add_edge(int u, int v, int ca, int co) {
    my_add_edge(u, v, ca, co);
    my_add_edge(v, u, 0, -co);
}


bool visit[V];
int dist[V], back[V];

int main() {
    int n, m;
    while (scanf("%d%d", &m, &n) == 2 && n + m > 0) {
        edge_count = 0;
        memset(first_edge, -1, sizeof(first_edge));
        int source = n + m;
        int target = source + 1;
        for (int i = 0; i < m; ++ i) {
            int p;
            scanf("%d", &p);
            add_edge(n + i, target, p, 0);
        }
        int answer = 0;
        for (int i = 0; i < n; ++ i) {
            int year;
            scanf("%d", &year);
            answer += (year - 1) * 4 + 1;
            add_edge(source, i, 1, 0);
            for (int j = 0; j < 4; ++ j) {
                int p;
                scanf("%d", &p);
                add_edge(i, n + p, 1, 3 - j);
            }
        }
        while (true) {
            for (int i = 0; i <= target; ++ i) {
                dist[i] = INT_MIN;
            }
            memset(visit, 0, sizeof(visit));
            dist[source] = 0;
            std::deque <int> queue;
            queue.push_back(source);
            while (!queue.empty()) {
                int u = queue.front();
                queue.pop_front();
                visit[u] = false;
                for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
                    if (capacity[iter] > 0 && dist[u] + cost[iter] > dist[to[iter]]) {
                        dist[to[iter]] = dist[u] + cost[iter];
                        back[to[iter]] = iter;
                        if (!visit[to[iter]]) {
                            visit[to[iter]] = true;
                            if (!queue.empty() && dist[to[iter]] < dist[queue.front()]) {
                                queue.push_front(to[iter]);
                            } else {
                                queue.push_back(to[iter]);
                            }
                        }
                    }
                }
            }
            if (dist[target] == INT_MIN) {
                break;
            }
            for (int i = target; i != source; i = to[back[i] ^ 1]) {
                answer += cost[back[i]];
                capacity[back[i]] --;
                capacity[back[i] ^ 1] ++;
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}
