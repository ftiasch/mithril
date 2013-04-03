#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

const int N = 500;
const int M = 5000;
const long long INF = 1000000000000000000LL;

int n, m, c;
int edge_count, first_edge[N], to[M << 1], weight[M << 1], next_edge[M << 1];

void add_edge(int u, int v, int w) {
    to[edge_count] = v;
    weight[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

int back[N];
long long distance[N];
bool visit[N];

int main() {
    scanf("%d%d%d", &n, &m, &c);
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
    std::fill(distance, distance + n, INF);
    distance[0] = 0;
    memset(visit, 0, sizeof(visit));
    while (true) {
        int u = -1;
        for (int j = 0; j < n; ++ j) {
            if (!visit[j] && (u == -1 || distance[j] < distance[u])) {
                u = j;
            }
        }
        if (u == -1) {
            break;
        }
        visit[u] = true;
        for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
            if (distance[u] + weight[iter] < distance[to[iter]]) {
                distance[to[iter]] = distance[u] + weight[iter];
                back[to[iter]] = iter;
            }
        }
    }
    if (distance[n - 1] < c) {
        puts("Unfair");
        std::vector <int> choices;
        for (int i = n - 1; i != 0; i = to[back[i] ^ 1]) {
            choices.push_back(back[i] >> 1);
        }
        std::sort(choices.begin(), choices.end());
        printf("%d\n", (int)choices.size());
        for (int i = 0; i < (int)choices.size(); ++ i) {
            printf("%d%c", 1 + choices[i], i == (int)choices.size() - 1 ? '\n' : ' ');
        }
    } else {
        puts("Fair");
    }
    return 0;
}
