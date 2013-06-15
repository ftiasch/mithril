#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000 + 1;
const int D = 19;

int n, parent[N], depth[N];
std::set <int> children[N];

int go[N][D];

std::set <int> lables;

struct SplayTree {
    int type[N], parent[N], children[N][2], size[N];

    SplayTree() {
        size[0] = 0;
    }

    void update(int x) {
        size[x] = size[children[x][0]] + 1 + size[children[x][1]];
    }

    void rotate(int x) {
        int t = type[x];
        int y = parent[x];
        int z = children[x][1 ^ t];
        type[x] = type[y];
        parent[x] = parent[y];
        if (type[x] != 2) {
            children[parent[x]][type[x]] = x;
        }
        type[y] = 1 ^ t;
        parent[y] = x;
        children[x][1 ^ t] = y;
        if (z) {
            type[z] = t;
            parent[z] = y;
        }
        children[y][t] = z;
        update(y);
    }

    void splay(int x) {
        while (type[x] != 2) {
            int y = parent[x];
            if (type[x] == type[y]) {
                rotate(y);
            } else {
                rotate(x);
            }
            if (type[x] == 2) {
                break;
            }
            rotate(x);
        }
        update(x);
    }

    void initialize() {
        type[1] = 2;
        children[1][0] = children[1][1] = 0;
        size[1] = 1;
    }

    int get_rank(int x) {
        splay(x);
        return size[children[x][0]] + 1;
    }

    int go(int x, int t) {
        while (children[x][t]) {
            x = children[x][t];
        }
        return x;
    }

    void link(int x, int t, int y) {
        type[y] = t;
        parent[y] = x;
        children[x][t] = y;
    }

    void insert(int x, int y) {
        children[y][0] = children[y][1] = 0;
        splay(x);
        if (!children[x][1]) {
            link(x, 1, y);
        } else {
            link(go(children[x][1], 0), 0, y);
        }
        splay(y);
    }

    void erase(int x) {
        splay(x);
        type[children[x][0]] = type[children[x][1]] = 2;
        if (children[x][0] && children[x][1]) {
            int p = go(children[x][0], 1);
            splay(p);
            link(p, 1, children[x][1]);
            update(p);
        }
    }
};

SplayTree splayTree;

void add_node(int p, int u) {
    depth[u] = p ? depth[p] + 1: 0;
    memset(go[u], 0, sizeof(go[u]));
    go[u][0] = p;
    for (int i = 0; go[u][i]; ++ i) {
        go[u][i + 1] = go[go[u][i]][i];
    }
}

void prepare(int u) {
    add_node(parent[u], u);
    foreach (iter, children[u]) {
        splayTree.insert(u, *iter);
        prepare(*iter);
    }
}

int jump(int u, int d) {
    for (int i = 0; i < D; ++ i) {
        if (d >> i & 1) {
            u = go[u][i];
        }
    }
    return u;
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        std::swap(u, v);
    }
    v = jump(v, depth[v] - depth[u]);
    if (u == v) {
        return u;
    }
    for (int i = D - 1; i >= 0; -- i) {
        if (go[u][i] != go[v][i]) {
            u = go[u][i];
            v = go[v][i];
        }
    }
    return parent[u];
}

void erase_tree(int u) {
    lables.insert(u);
    splayTree.erase(u);
    foreach (iter, children[u]) {
        erase_tree(*iter);
    }
}

int main() {
    int test_count = 0;
    int last_answer = -1;
    while (scanf("%d", &n) == 1) {
        printf("Case %d:", ++ test_count);
        for (int i = 1; i <= n; ++ i) {
            children[i].clear();
        }
        parent[1] = 0;
        for (int i = 2; i <= n; ++ i) {
            scanf("%d", parent + i);
            children[parent[i]].insert(i);
        }
        splayTree.initialize();
        prepare(1);
        int m;
        scanf("%d", &m);
        lables.clear();
        for (int i = 1; i <= m; ++ i) {
            lables.insert(n + i);
        }
        while (m --) {
            char buffer[2];
            scanf("%s", buffer);
            if (*buffer == '?') {
                int k;
                scanf("%d", &k);
                std::vector <std::pair <int, int> > order;
                for (int i = 0; i < k; ++ i) {
                    int x;
                    scanf("%d", &x);
                    order.push_back(std::make_pair(splayTree.get_rank(x), x));
                }
                std::sort(order.begin(), order.end());
                int answer = -1;
                for (int i = 1; i < k; ++ i) {
                    int a = order[i - 1].second;
                    int b = order[i].second;
                    int c = lca(a, b);
                    if (c != a && c != b) {
                        answer = std::max(answer, depth[c]);
                    }
                }
                printf(" %d", answer);
                last_answer = answer;
            } else if (*buffer == '+') {
                int u;
                scanf("%d", &u);
                u += last_answer;
                int v = *lables.begin();
                lables.erase(lables.begin());
                parent[v] = u;
                children[v].clear();
                children[u].insert(v);
                add_node(u, v);
                splayTree.insert(u, v);
            } else {
                int v;
                scanf("%d", &v);
                erase_tree(v);
                children[parent[v]].erase(v);
            }
        }
        puts("");
    }
    return 0;
}
