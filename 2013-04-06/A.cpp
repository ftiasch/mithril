#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const double EPS = 1e-8;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

const int N = 20;
const int L = 10;
const int M = 50;

int n, l, m;
std::map <int, int> graph[N];

char string[L + 1], sequence[M + 1];
int fail[L + 1], go[L + 1][26];

const int S = N * (L + 1);
const int V = (M + 1) * N * (L + 1);

bool reach[2][M + 1][N][L + 1];
double expected[M + 1][N][L + 1], coefficient[S][S + 1], solution[S];

bool reachable[2][V];
std::vector <int> outgo[V], income[V];

int get_id(int x, int y, int z) {
    return ((x * n) + y) * (l + 1) + z;
}

void floodfill(std::vector <int> graph[V], bool reachable[V]) {
    std::queue <int> queue;
    for (int i = 0; i < V; ++ i) {
        if (reachable[i]) {
            queue.push(i);
        }
    }
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        foreach (iter, graph[u]) {
            int v = *iter;
            if (!reachable[v]) {
                reachable[v] = true;
                queue.push(v);
            }
        }
    }
}

int vars;

void eliminate() {
    for (int j = 0; j < vars; ++ j) {
        for (int i = j + 1; i < vars; ++ i) {
            if (signum(coefficient[i][j]) != 0) {
                double times = coefficient[i][j] / coefficient[j][j];
                for (int k = 0; k <= vars; ++ k) {
                    coefficient[i][k] -= times * coefficient[j][k];
                }
            }
        }
    }
    for (int j = vars - 1; j >= 0; -- j) {
        solution[j] = -coefficient[j][vars];
        for (int i = j + 1; i < vars; ++ i) {
            solution[j] -= coefficient[j][i] * solution[i];
        }
        solution[j] /= coefficient[j][j];
    }
}

int state_id[V];

int main() {
    scanf("%d%d", &n, &m);
    while (m --) {
        int u, v;
        char buffer[2];
        scanf("%d%d%s", &u, &v, buffer);
        graph[u - 1][*buffer - 'a'] = v - 1;
    }
    scanf("%s", string);
    l = strlen(string);
    memset(go, 0, sizeof(go));
    go[0][string[0] - 'a'] = 1;
    fail[1] = 0;
    for (int i = 1; i < l; ++ i) {
        fail[i + 1] = go[fail[i]][string[i] - 'a'];
        for (int j = 0; j < 26; ++ j) {
            if (string[i] - 'a' == j) {
                go[i][j] = i + 1;
            } else {
                go[i][j] = go[fail[i]][j];
            }
        }
    }
    scanf("%s", sequence);
    m = strlen(sequence);

    for (int k = 0; k < m; ++ k) {
        for (int u = 0; u < n; ++ u) {
            for (int i = 0; i < l; ++ i) {
                foreach (iter, graph[u]) {
#define ADD_EDGE(u, v) outgo[u].push_back(v); income[v].push_back(u)//; printf("%d -> %d\n", u, v)
                    ADD_EDGE(get_id(k, u, i), get_id(iter->first == sequence[k] - 'a' ? k + 1 : k, iter->second, go[i][iter->first]));
#undef ADD_EDGE
                }
            }
        }
    }
    memset(reachable, 0, sizeof(reachable));
    reachable[0][get_id(0, 0, 0)] = true;
    floodfill(outgo, reachable[0]);
    for (int u = 0; u < n; ++ u) {
        for (int i = 0; i <= l; ++ i) {
            reachable[1][get_id(m, u, i)] = true;
        }
    }
    for (int k = 0; k < m; ++ k) {
        for (int u = 0; u < n; ++ u) {
            reachable[1][get_id(k, u, l)] = true;
        }
    }
//for (int i = 0; i < V; ++ i) {
//    if (reachable[1][i]) {
//        printf("%d, ", i);
//    }
//}
//puts("");
    floodfill(income, reachable[1]);
    for (int i = 0; i < V; ++ i) {
        if (reachable[0][i] && !reachable[1][i]) {
            puts("Infinity");
            return 0;
        }
    }

    memset(expected, 0, sizeof(expected));
    //vars = n * l;
    for (int k = m - 1; k >= 0; -- k) {
        memset(coefficient, 0, sizeof(coefficient));
        vars = 0;
        for (int u = 0; u < n; ++ u) {
            for (int i = 0; i < l; ++ i) {
                if (reachable[0][get_id(k, u, i)]) {
                    state_id[get_id(k, u, i)] = vars ++;
                }
            }
        }
        for (int u = 0; u < n; ++ u) {
            for (int i = 0; i < l; ++ i) {
                if (reachable[0][get_id(k, u, i)]) {
                    double total = graph[u].size();
                    int id = state_id[get_id(k, u, i)];
                    coefficient[id][id] -= 1.0;
                    foreach (iter, graph[u]) {
                        int v = iter->second;
                        int j = go[i][iter->first];
                        if (j == l) {
                            continue;
                        }
                        if (iter->first == sequence[k] - 'a') {
                            coefficient[id][vars] += expected[k + 1][v][j] / total;
                        } else {
                            coefficient[id][state_id[get_id(k, v, j)]] += 1 / total;
                        }
                    }
                    coefficient[id][vars] += 1.0;
                }
            }
        }
//for (int i = 0; i < vars; ++ i) {
//    for (int j = 0; j <= vars; ++ j) {
//        printf("%.2f ", coefficient[i][j]);
//    }
//    puts("");
//}
        eliminate();
        for (int u = 0; u < n; ++ u) {
            for (int i = 0; i < l; ++ i) {
                if (reachable[0][get_id(k, u, i)]) {
                    expected[k][u][i] = solution[state_id[get_id(k, u, i)]];
//printf("%d, %d, %d, %.2f\n", k, u, i, expected[k][u][i]);
                }
            }
        }
    }
    printf("%.2f\n", expected[0][0][0]);
    return 0;
}
