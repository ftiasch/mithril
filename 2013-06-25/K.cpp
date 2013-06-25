#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int maxn = 1000 * 2;

struct Tree
{
    int node, inner, leaf; // 0 .. inner - 1,  inner .. node - 1
    int next[maxn], father[maxn], depth[maxn];
    vector<int> adj[maxn];
    
    int getId(int inner, char s[]) {
        int id;
        sscanf(s + 2, "%d", &id);
        -- id;
        
        if (s[1] == 'S') {
            id += inner;
        }
        return id;
    }
    
    void read(int a, int b){
        inner = a;
        leaf = b;
        node = inner + leaf;
        for (int i = 0; i < node; ++ i) {
            adj[i].clear();
        }
        static char sa[100], sb[100];
        for (int i = 1; i < node; ++ i) {
            scanf("%s%s", sa, sb);
            int a = getId(inner, sa), b = getId(inner, sb);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
    
    int dfs(int u, int fa, vector<int> &permutation) {
        father[u] = fa;
        if (adj[u].size() == 1) {
            next[u] = u - inner;
            return 1;
        }
        vector<int> son;
        for (int i = 0; i < adj[u].size() && son.size() <= 2; ++ i) {
            int v = adj[u][i];
            if (v == fa) {
                continue;
            }
            depth[v] = depth[u] + 1;
            int res = dfs(v, u, permutation);
            if (res == -1) {
                return -1;
            }
            if (res == 1) {
                son.push_back(next[v]);
            }
        }
        if (son.size() == 2) {
            permutation[son[0]] = son[1];
            permutation[son[1]] = son[0];
            return 0;
        }
        if (son.size() == 1) {
            next[u] = son[0];
            return 1;
        }
        return -1;
    }
    
    bool findMatch(vector<int> &permutation) {
        permutation.resize(leaf);
        depth[0] = 0;
        return dfs(0, -1, permutation) == 0;
    }
    
    void show(char prefix, int x) {
        printf(" %c", prefix);
        if (x < inner) {
            printf("P%d", x + 1);
        } else {
            printf("S%d", x - inner + 1);
        }
    }
    
    void findPath(char prefix, int a, int b) {
        a += inner;
        b += inner;
        vector<int> pa, pb;
        while (a != b) {
            if (depth[a] > depth[b]) {
                a = father[a];
                pa.push_back(a);
            } else {
                pb.push_back(b);
                b = father[b];
            }
        }
        for (int i = 0; i < pa.size(); ++ i) {
            show(prefix, pa[i]);
        }
        for (int i = (int)pb.size() - 1; i >= 0; -- i) {
            show(prefix, pb[i]);
        }
    }
}treeA, treeB;

int nodeA, nodeB, leaf;
bool vis[maxn];
vector<int> adj[maxn];

inline bool solve()
{
    vector<int> pa, pb;
    if (!treeA.findMatch(pa)) {
//puts("A");
        return false;
    }
    if (!treeB.findMatch(pb)) {
//puts("B");
        return false;
    }
    
    for (int i = 0; i < leaf; ++ i) {
//printf("A %d %d\n", i, pa[i]);
//printf("B %d %d\n", i, pb[i]);
        adj[i].push_back(pa[i]);
        adj[i + leaf].push_back(pb[i] + leaf);
    }
    
    vector<int> cycle;
    memset(vis, false, sizeof(vis));
    int cur = 0;
    while (!vis[cur]) {
        vis[cur] = true;
        cycle.push_back(cur);
        for (int i = 0; i < adj[cur].size(); ++ i) {
            int v = adj[cur][i];
            if (!vis[v]) {
                cur = v;
                break;
            }
        }
    }
    if (cycle.size() != leaf * 2) {
        return false;
    }
    
    printf("YES");
    for (int i = 0; i < cycle.size(); ++ i) {
        int u = cycle[i], v = cycle[(i + 1) % cycle.size()];
        if ((u < leaf) == (v < leaf)) {
            if (u < leaf) {
                treeA.findPath('A', u, v);
            } else {
                treeB.findPath('B', u - leaf, v - leaf);
            }
        } else {
            if (v < leaf) {
                printf(" AS%d", v + 1);
            } else {
                printf(" BS%d", v - leaf + 1);
            }
        }
    }
    puts("");
    return true;
}

int main()
{
    int T;
    for (scanf("%d", &T); T--;) {
        scanf("%d%d%d", &leaf, &nodeA, &nodeB);
        treeA.read(nodeA, leaf);
        treeB.read(nodeB, leaf);
        
        for (int i = 0; i < 2 * leaf; ++ i) {
            adj[i].clear();
        }
        for (int i = 0; i < leaf; ++ i) {
            static char sa[100], sb[100];
            scanf("%s%s", sa, sb);
            int a, b;
            sscanf(sa + 2, "%d", &a);
            sscanf(sb + 2, "%d", &b);
            -- a; -- b;
            if (sa[0] == 'B') {
                swap(a, b);
            }
            b += leaf;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        if (!solve()) {
            puts("NO");
        }
    }
    return 0;
}

