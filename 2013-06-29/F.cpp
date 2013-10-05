#include <cstdio>
#include <cstring>

const int N = 100000;

int parent[N], delta[N];

int find(int u) {
    int root = u;
    int sum = 0;
    while (parent[root] != root) {
        sum += delta[root];
        root = parent[root];
    }
    for (int v = u; v != root; ) {
        sum -= delta[v];
        delta[v] += sum;
        int old_parent = parent[v];
        parent[v] = root;
        v = old_parent;
    }
    return root;
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n) {
        for (int i = 0; i < n; ++ i) {
            delta[i] = 0;
            parent[i] = i;
        }
        for (int i = 0; i < m; ++ i) {
            char buffer[2];
            int a, b;
            scanf("%s%d%d", buffer, &a, &b);
            a --, b --;
            if (*buffer == '?') {
                if (find(a) != find(b)) {
                    puts("UNKNOWN");
                } else {
                    printf("%d\n", delta[b] - delta[a]);
                }
            } else {
                int c;
                scanf("%d", &c);
                if (find(a) != find(b)) {
                    delta[find(b)] = c - delta[b] + delta[a];
                    parent[find(b)] = find(a);
                }
            }
        }
    }
    return 0;
}
