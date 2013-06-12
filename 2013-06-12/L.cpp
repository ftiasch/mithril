#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 222222;

int n, a[N], b[N], degree[N], parent[N], c[N];
int count[N];
bool mark[N];

std::vector <int> tree[N];

int find(int i) {
    if (parent[i] == -1) {
        return i;
    }
    return parent[i] = find(parent[i]);
}

int main() {
    scanf("%d", &n);
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        count[a[i]] ++;
    }
    std::set <int> set;
    for (int i = 1; i <= n + 1; ++ i) {
        if (count[i] == 0) {
            set.insert(i);
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (set.empty()) {
            puts("Error");
            return 0;
        }
        b[i] = *set.begin();
        set.erase(set.begin());
        count[a[i]] --;
        if (count[a[i]] == 0) {
            set.insert(a[i]);
        }
    }
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < n; ++ i) {
        if (find(a[i]) == find(b[i])) {
            puts("Error");
            return 0;
        }
        parent[find(a[i])] = find(b[i]);
        tree[a[i]].push_back(b[i]);
        tree[b[i]].push_back(a[i]);
        degree[a[i]] ++;
        degree[b[i]] ++;
    }
    set.clear();
    for (int i = 1; i <= n + 1; ++ i) {
        if (degree[i] == 1) {
            set.insert(i);
        }
    }
    memset(mark, 0, sizeof(mark));
    int total = 0;
    while (!set.empty()) {
        int u = *set.begin();
        set.erase(set.begin());
        mark[u] = true;
        foreach (iter, tree[u]) {
            if (!mark[*iter]) {
                c[total ++] = *iter;
            }
        }
        foreach (iter, tree[u]) {
            int v = *iter;
            if (degree[v] > 1) {
                degree[v] --;
                if (degree[v] == 1) {
                    set.insert(v);
                }
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (a[i] != c[i]) {
            puts("Error");
            return 0;
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d\n", b[i]);
    }
    return 0;
}
