#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000;

int n, t[N], k[N];

int edge_count, first_edge[N], to[N << 1], length[N << 1], next_edge[N << 1];

void add_edge(int u, int v, int w) {
    to[edge_count] = v;
    length[edge_count] = w;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

long long weight[N], cost[N], best[N];
vector <int> order[N];

bool compare(int i, int j) {
    return cost[i] * weight[j] < cost[j] * weight[i];
}

void dfs(int p, int u) {
    weight[u] = k[u];
    cost[u] = t[u];
    long long total_weight = k[u];
    long long total_cost = t[u];
    order[u].push_back(u);
    best[u] = t[u]*k[u];
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        if (to[iter] != p) {
            order[u].push_back(to[iter]);
            dfs(u, to[iter]);
            best[u] += best[to[iter]] + length[iter] * weight[to[iter]];
            total_weight += weight[to[iter]];
            cost[to[iter]] += length[iter] * 2;
            total_cost += cost[to[iter]];
        }
    }
    sort(order[u].begin(), order[u].end(), compare);
    long long now = 0;
    foreach (iter, order[u]) {
        best[u] += now * weight[*iter];
        now += cost[*iter];
    }
    weight[u] = total_weight;
    cost[u] = total_cost;
}

void construct(int u) {
    foreach (iter, order[u]) { 
        if (*iter == u) {
            printf("P %d\n", u + 1);
        } else {
            printf("M %d\n", *iter + 1);
            construct(*iter);
            printf("M %d\n", u + 1);
        }
    }
}

int main() {
    freopen("beetles.in", "r", stdin);
    freopen("beetles.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", t + i);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", k + i);
    }
    edge_count = 0;
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < n - 1; ++ i) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        u --, v --;
        add_edge(u, v, d);
        add_edge(v, u, d);
    }
    memset(weight, 0, sizeof(weight));
    memset(cost, 0, sizeof(cost));
    memset(best, 0, sizeof(best));
    dfs(-1, 0);
    cout << best[0] << endl;
    construct(0);
    return 0;
}
