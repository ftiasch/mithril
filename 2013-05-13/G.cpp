#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 1000;
const int M = 100000;
const int Q = 2000 + 1;

struct Query {
    int id, a, b, c;

    Query(int id, int a, int b, int c) : id(id), a(a), b(b), c(c) {}
};

int n, m, q, a[M], b[M], c[M], params[Q][2], answer[M];
bool changed[M];
std::vector <Query> queries[Q];

std::vector <int> candidates;

int parent[N], minimum[N];

int findRoot(int u) {
    if (parent[u] == -1) {
        return u;
    }
    return parent[u] = findRoot(parent[u]);
}

bool by_c(int i, int j) {
    return c[i] > c[j];
}

std::vector <std::pair <int, int> > edges[N];

void add_edge(int u, int v, int w) {
    edges[u].push_back(std::make_pair(v, w));
}

struct LCAQuery {
    int id, v;

    LCAQuery(int id, int v) : id(id), v(v) {}
};

bool done[N];
std::vector <LCAQuery> lca_queries[N];

int access(int u) {
    if (parent[u] != u) {
        int tmp = access(parent[u]);
        minimum[u] = std::min(minimum[u], minimum[parent[u]]);
        parent[u] = tmp;
    }
    return parent[u];
}

void process(int p, int u) {
    parent[u] = u;
    minimum[u] = INT_MAX;
    foreach (iter, edges[u]) {
        int v = iter->first;
        if (v != p) {
            process(u, v);
            parent[v] = u;
            minimum[v] = iter->second;
        }
    }
    foreach (iter, lca_queries[u]) {
        if (done[iter->v]) {
            access(iter->v);
            answer[iter->id] = std::min(answer[iter->id], minimum[iter->v]);
        }
    }
    done[u] = true;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2 && n + m) {
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d%d", a + i, b + i , c + i);
            a[i] --, b[i] --;
        }
        int e;
        scanf("%d", &e);
        q = 0;
        queries[q].clear();
        memset(changed, 0, sizeof(changed));
        for (int i = 0; i < e; ++ i) {
            char buffer[2];
            scanf("%s", buffer);
            if (*buffer == 'S') {
                int a, b, c;
                scanf("%d%d%d", &a, &b, &c);
                queries[q].push_back(Query(i, a - 1, b - 1, c));
            } else {
                q ++;
                queries[q].clear();
                scanf("%d%d", &params[q][0], &params[q][1]);

                params[q][0] --;
                changed[params[q][0]] = true;
            }
        }
        memset(parent, -1, sizeof(parent));
        std::vector <int> order;
        candidates.clear();
        for (int i = 0; i < m; ++ i) {
            if (!changed[i]) {
                order.push_back(i);
            } else {
                candidates.push_back(i);
            }
        }
        std::sort(order.begin(), order.end(), by_c);
        for (int i = 0; i < (int)order.size(); ++ i) {
            if (findRoot(a[order[i]]) != findRoot(b[order[i]])) {
                candidates.push_back(order[i]);
                parent[findRoot(a[order[i]])] = findRoot(b[order[i]]);
            }
        }
        for (int i = 0; i < e; ++ i) {
            answer[i] = INT_MAX;
        }
        for (int i = 0; i <= q; ++ i) {
            memset(parent, -1, sizeof(parent));
            if (i) {
                c[params[i][0]] = params[i][1];
            }
            std::sort(candidates.begin(), candidates.end(), by_c);
            for (int u = 0; u < n; ++ u) {
                edges[u].clear();
                lca_queries[u].clear();
            }
            for (int k = 0; k < (int)candidates.size(); ++ k) {

                int &u = a[candidates[k]];
                int &v = b[candidates[k]];
                int &w = c[candidates[k]];
                if (findRoot(u) != findRoot(v)) {
                    parent[findRoot(u)] = findRoot(v);
                    add_edge(u, v, w);
                    add_edge(v, u, w);
                }
            }
            foreach (iter, queries[i]) {
                if (findRoot(iter->a) != findRoot(iter->b)) { 
                    answer[iter->id] = -1;
                } else {
                    lca_queries[iter->a].push_back(LCAQuery(iter->id, iter->b));
                    lca_queries[iter->b].push_back(LCAQuery(iter->id, iter->a));
                }
            }
            memset(done, 0, sizeof(done));
            for (int u = 0; u < n; ++ u) {
                if (!done[u]) {
                    process(-1, u);
                }
            }
            for (int k = 0; k < n; ++ k) {
                std::reverse(edges[k].begin(), edges[k].end());
            }
            memset(done, 0, sizeof(done));
            for (int u = 0; u < n; ++ u) {
                if (!done[u]) {
                    process(-1, u);
                }
            }
            foreach (iter, queries[i]) {
                answer[iter->id] = answer[iter->id] >= iter->c;
            }
        }
        for (int i = 0; i < e; ++ i) {
            if (answer[i] != INT_MAX) {
                printf("%d\n", answer[i]);
            }
        }
    }
    return 0;
}
