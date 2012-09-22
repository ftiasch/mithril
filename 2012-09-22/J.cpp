#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#pragma comment(linker, "/STACK:10777216")

map <string, int> ids;

int getID(const string &name) {
    if (ids.find(name) == ids.end()) {
        ids[name] = ids.size() - 1;
    }
    return ids[name];
}

const int N = 30000;

int n;
char buffer[N << 1];
int closest[N];
string names[N];

vector <int> children[N];

bool byName(int i, int j) {
    return names[i] < names[j];
}

void print(int lv, int u) {
    for (int i = 0; i < lv; ++ i) {
        putchar('.');
    }
    puts(names[u].c_str());
    for (vector <int> :: iterator iter = children[u].begin(); iter != children[u].end(); ++ iter) {
        print(lv + 1, *iter);
    }
}

const int D = 16;

int depth[N], go[N][D];

void dfs(int p, int u) {
    depth[u] = p == -1? 0: depth[p] + 1;
    go[u][0] = p;
    for (int i = 0; go[u][i] != -1; ++ i) {
        go[u][i + 1] = go[go[u][i]][i];
    }
    for (vector <int> :: iterator iter = children[u].begin(); iter != children[u].end(); ++ iter) {
        dfs(u, *iter);
    }
}

int jump(int u, int d) {
    for (int i = D - 1; i >= 0; -- i) {
        if ((1 << i) <= d) {
            u = go[u][i];
            d -= 1 << i;
        }
    }
    return u;
}


int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    v = jump(v, depth[v] - depth[u]);
    for (int i = D - 1; i >= 0; -- i) {
        if (go[u][i] != go[v][i]) {
            u = go[u][i];
            v = go[v][i];
        }
    }
    return go[u][0];
}

int main() {
    while (scanf("%d", &n) == 1 && n != 0) {
        ids.clear();
        for (int i = 0; i < n; ++ i) {
            children[i].clear();
        }
        for (int i = 0; i < n; ++ i) {
            scanf("%s", buffer);
            int level = 0;
            while (buffer[level] == '.') {
                level ++;
            }
            names[i] = buffer + level;
            int id = getID(names[i]);
//printf("-- %d\n", id);
            if (id != 0) {
                children[closest[level - 1]].push_back(id);
            }
            closest[level] = id;
        }
        for (int i = 0; i < n; ++ i) {
            sort(children[i].begin(), children[i].end(), byName);
        }
        memset(go, -1, sizeof(go));
        dfs(-1, 0);
        int q;
        scanf("%d", &q);
        while (q > 0) {
            q --;
            scanf("%s", buffer);
            if (*buffer == 'L') {
                print(0, 0);
            }
            if (*buffer == 'b') {
                scanf("%s", buffer);
                int id = getID(buffer);
                if (id == 0) {
                    puts("1");
                } else {
                    printf("%d\n", (int)children[go[id][0]].size());
                }
            } 
            if (*buffer == 'c') {
                scanf("%s", buffer);
                int u = getID(buffer);
                scanf("%s", buffer);
                int v = getID(buffer);
                int w = lca(u, v);
                puts(names[w].c_str());
            }
        }
    }
    return 0;
}
