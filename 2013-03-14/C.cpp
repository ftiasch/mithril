#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int INF = 1000000000;
const int source = 64;
const int target = 65;

int id[8][8];

const int DELTA[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

bool has[64], graph[64][64];

const int V = 66;
const int E = (V * V + V) * 2;

int edge_count, first_edge[V], to[E], flow[E], capacity[E], cost[E], next_edge[E], distance[V], back[V];
bool visit[V];

void _add_edge(int u, int v, int c, int w) {
    to[edge_count] = v;
    flow[edge_count] = 0;
    capacity[edge_count] = c;
    cost[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

void add_edge(int u, int v, int c, int w) {
    _add_edge(u, v, c, w);
    _add_edge(v, u, 0, -w);
}

int solve(std::vector <int> froms, std::vector <int> tos) {
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < 64; ++ i) {
        for (int j = 0; j < 64; ++ j) {
            if (graph[i][j]) {
                add_edge(i, j, INF, 1);
            }
        }
    }
    foreach (iter, froms) {
        if (has[*iter]) {
            add_edge(source, *iter, 1, 0);
        }
    }
    foreach (iter, tos) {
        if (!has[*iter]) {
            add_edge(*iter, target, 1, 0);
        }
    }

    int answer = 0;
    while (true) {
        for (int i = 0; i < V; ++ i) {
            distance[i] = INF;
        }
        memset(visit, 0, sizeof(visit));
        distance[source] = 0;
        std::queue <int> queue;
        queue.push(source);
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            visit[u] = false;
            for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
                if (flow[iter] < capacity[iter] && distance[u] + cost[iter] < distance[to[iter]]) {
                    distance[to[iter]] = distance[u] + cost[iter];
                    back[to[iter]] = iter;
                    if (!visit[to[iter]]) {
                        visit[to[iter]] = true;
                        queue.push(to[iter]);
                    }
                }
            }
        }
        if (distance[target] == INF) {
            break;
        }
        for (int i = target; i != source; i = to[back[i] ^ 1]) {
            flow[back[i]] ++;
            flow[back[i] ^ 1] --;
            answer += cost[back[i]];
        }
    }
    return answer;
}

int next[V];

void print_id(int id) {
    int x = 8 - id / 8;
    int y = id % 8;
    printf("%c%d", 'a' + y, x);
}

void go(int u) {
    if (next[u] != target && next[u] != -1) {
        if (has[next[u]]) {
            go(next[u]);
            print_id(u);
            putchar('-');
            print_id(next[u]);
            putchar('\n');
            has[u] = false;
            has[next[u]] = true;
        } else {
            print_id(u);
            putchar('-');
            print_id(next[u]);
            putchar('\n');
            has[u] = false;
            has[next[u]] = true;
            go(next[u]);
        }
    }
}

int main() {
    for (int i = 0; i < 8; ++ i) {
        for (int j = 0; j < 8; ++ j) {
            id[i][j] = i * 8 + j;
        }
    }
    for (int i = 0; i < 8; ++ i) {
        for (int j = 0; j < 8; ++ j) {
            for (int k = 0; k < 8; ++ k) {
                int x = i + DELTA[k][0];
                int y = j + DELTA[k][1];
                if (0 <= x && x < 8 && 0 <= y && y < 8) {
                    graph[id[i][j]][id[x][y]] = true;
                }
            }
        }
    }
    bool first = true;
    while (true) {
        char buffer[9];
        if (scanf("%s", buffer) == 1) {
            memset(has, 0, sizeof(has));
            for (int i = 0; i < 8; ++ i) {
                for (int j = 0; j < 8; ++ j) {
                    has[id[i][j]] = buffer[j] == 'N';
                }
                if (i < 7) {
                    scanf("%s", buffer);
                }
            }
        } else {
            break;
        }
        std::vector <int> froms;
        std::vector <int> tos;
        for (int i = 0; i < 8; ++ i) {
            for (int j = 0; j < 8; ++ j) {
                if (i + j & 1) {
                    tos.push_back(id[i][j]);
                } else {
                    froms.push_back(id[i][j]);
                }
            }
        }
        if (solve(tos, froms) < solve(froms, tos)) {
            std::swap(froms, tos);
        }
        int answer = solve(froms, tos);
        if (first) {
            first = false;
        } else {
            puts("");
        }
        printf("%d\n", answer);
        memset(next, -1, sizeof(next));
        for (int u = 0; u < 64; ++ u) {
            for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
                if (flow[iter] > 0) {
                    assert(next[u] == -1);
                    next[u] = to[iter];
                }
            }
        }
        foreach (iter, froms) {
            if (has[*iter]) {
                for (int i = *iter; i != target; ) {
                    for (int it = first_edge[i]; it != -1; it = next_edge[it]) {
                        if (flow[it] > 0) {
                            next[i] = to[it];
                            i = to[it];
                            break;
                        }
                    }
                }
                go(*iter);
            }
        }
    }
    return 0;
}
