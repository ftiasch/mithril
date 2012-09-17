#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 200000 + 1;

int type[N], parent[N], children[N][2];
bool isCovered[N];
int weight[N], size[N];

struct Information {
    int leftExpand, rightExpand, sum, maximum;

    Information(int leftExpand = 0, int rightExpand = 0, int sum = 0, int maximum = 0): 
        leftExpand(leftExpand), rightExpand(rightExpand), sum(sum), maximum(maximum) {
    }

    Information reverse() {
        return Information(rightExpand, leftExpand, sum, maximum);
    }
};

Information operator +(const Information &a, const Information &b) {
    return Information(max(a.leftExpand, a.sum + b.leftExpand),
                       max(b.rightExpand, b.sum + a.rightExpand),
                       a.sum + b.sum,
                       max(max(a.maximum, b.maximum), max(a.rightExpand + b.leftExpand, max(a.sum + b.leftExpand, b.sum + a.rightExpand))));
}

Information info[N];

void doCover(int x, int v) {
    if (x != 0) {
        isCovered[x] = true;
        weight[x] = v;
        if (v > 0) {
            info[x] = Information(v * size[x], v * size[x], v * size[x], v * size[x]);
        } else {
            info[x] = Information(v, v, v * size[x], v);
        }
    }
}

void push(int x) {
    if (isCovered[x]) {
        isCovered[x] = false;
        doCover(children[x][0], weight[x]);
        doCover(children[x][1], weight[x]);
    }
}

void update(int x) {
    size[x] = size[children[x][0]] + 1 + size[children[x][1]];
    info[x] = Information(weight[x], weight[x], weight[x], weight[x]);
    if (children[x][0] != 0) {
        info[x] = info[children[x][0]] + info[x];
    }
    if (children[x][1] != 0) {
        info[x] = info[x] + info[children[x][1]];
    }
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

int stack[N];

void splay(int x) {
    int top = 0;
    stack[top ++] = x;
    for (int i = x; type[i] != 2; i = parent[i]) {
        stack[top ++] = parent[i];
    }
    for (int i = top - 1; i >= 0; -- i) {
        push(stack[i]);
    }
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

void access(int x) {
    int z = 0;
    while (x != 0) {
        splay(x);
        type[children[x][1]] = 2;
        children[x][1] = z;
        type[z] = 1;
        update(x);
        z = x;
        x = parent[x];
    }
}

int n, q;
vector <int> adj[N];

bool visit[N];
//void dfs(int p, int u) {
//    parent[u] = p;
//    for (vector <int> :: iterator iter = adj[u].begin(); iter != adj[u].end(); ++ iter) {
//        if (*iter != p) {
//            dfs(u, *iter);
//        }
//    }
//}

int main() {
    size[0] = 0;
    memset(isCovered, 0, sizeof(isCovered));
    scanf("%d%d", &n, &q);
    memset(children, 0, sizeof(children));
    for (int i = 1; i <= n; ++ i) {
        type[i] = 2;
        scanf("%d", weight + i);
        update(i);
    }
    for (int i = 1; i <= n - 1; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    memset(visit, 0, sizeof(visit));
    {
    queue <int> q;
    q.push(1);
    parent[1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visit[u] = true;
        for (vector <int> :: iterator iter = adj[u].begin(); iter != adj[u].end(); ++ iter) {
            if (!visit[*iter]) {
                parent[*iter] = u;
                q.push(*iter);
            }
        }
    }
    }
    while (q > 0) {
        q --;
        int t, a, b, c;
        scanf("%d%d%d%d", &t, &a, &b, &c);
        if (t == 1) {
            access(a);
            int z = 0;
            int x = b;
            while (x) {
                splay(x);
                if (parent[x] == 0) {
                    int y = children[x][1];
                    weight[x] = c;
                    update(x);
                    doCover(y, c);
                    doCover(z, c);
                }
                type[children[x][1]] = 2;
                children[x][1] = z;
                type[z] = 1;
                update(x);
                z = x;
                x = parent[x];
            }
        } else {
            access(a);
            int z = 0;
            int x = b;
            while (x) {
                splay(x);
                if (parent[x] == 0) {
                    int y = children[x][1];
                    Information result(weight[x], weight[x], weight[x], weight[x]);
                    if (y != 0) {
                        result = result + info[y];
                    }
                    if (z != 0) {
                        result = info[z].reverse() + result;
                    }
                    printf("%d\n", result.maximum);
                }
                type[children[x][1]] = 2;
                children[x][1] = z;
                type[z] = 1;
                update(x);
                z = x;
                x = parent[x];
            }
        }
    }
    return 0;
}
