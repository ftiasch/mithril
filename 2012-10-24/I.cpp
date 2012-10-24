#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 200000;
const int M = 1 + (N << 1);
const int EMPTY = M - 1;

const int MOD = 99990001;

int nodeCount, type[M], parent[M], children[M][2], id[M];

int scale[M], delta[M], weight[M], size[M], minimum[M];

void update(int x) {
    size[x] = size[children[x][0]] + 1 + size[children[x][1]];
    minimum[x] = min(min(minimum[children[x][0]], minimum[children[x][1]]), id[x]);
}

void modify(int x, int k, int b) {
    weight[x] = ((long long)k * weight[x] + b) % MOD;
    scale[x] = (long long)k * scale[x] % MOD;
    delta[x] = ((long long)k * delta[x] + b) % MOD;
}

void pushDown(int x) {
    for (int i = 0; i < 2; ++ i) {
        if (children[x][i] != EMPTY) {
            modify(children[x][i], scale[x], delta[x]);
        }
    }
    scale[x] = 1;
    delta[x] = 0;
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
    if (z != EMPTY) {
        type[z] = t;
        parent[z] = y;
    }
    children[y][t] = z;
    update(y);
}

void splay(int x) {
    if (x == EMPTY) {
        return;
    }
    vector <int> stack(1, x);
    for (int i = x; type[i] != 2; i = parent[i]) {
        stack.push_back(parent[i]);
    }
    while (!stack.empty()) {
        pushDown(stack.back());
        stack.pop_back();
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

int goLeft(int x) {
    while (children[x][0] != EMPTY) {
        x = children[x][0];
    }
    return x;
}

int join(int x, int y) {
    if (x == EMPTY || y == EMPTY) {
        return x != EMPTY ? x : y;
    }
    y = goLeft(y);
    splay(y);
    splay(x);
    type[x] = 0;
    parent[x] = y;
    children[y][0] = x;
    update(y);
    return y;
}

pair <int, int> split(int x) {
    splay(x);
    int a = children[x][0];
    int b = children[x][1];
    children[x][0] = children[x][1] = EMPTY;
    if (a != EMPTY) {
        type[a] = 2;
        parent[a] = EMPTY;
    }
    if (b != EMPTY) {
        type[b] = 2;
        parent[b] = EMPTY;
    }
    return make_pair(a, b);
}

int newNode(int init, int vid) {
    int x = nodeCount ++;
    type[x] = 2;
    parent[x] = children[x][0] = children[x][1] = EMPTY;
    id[x] = vid;
    weight[x] = init;
    scale[x] = 1;
    delta[x] = 0;
    update(x);
    return x;
}

int n;
int edgeCount, firstEdge[N], to[M], nextEdge[M], initWeight[N], position[M];

int root;

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount ++;
}

void dfs(int p, int u) {
    for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
        int v = to[iter];
        if (v != p) {
            position[iter] = nodeCount;
            root = join(root, newNode(initWeight[iter >> 1], min(u, v)));
            dfs(u, v);
            position[iter ^ 1] = nodeCount;
            root = join(root, newNode(initWeight[iter >> 1], min(u, v)));
        }
    }
}

int getRank(int x) { // 1-based
    splay(x);
    return size[children[x][0]] + 1;
}

void print(int root) {
    if (root != EMPTY) {
        printf("[ ");
        print(children[root][0]);
        printf(" %d ", root);
        print(children[root][1]);
        printf(" ]");
    }
}

int main() {
    size[EMPTY] = 0;
    minimum[EMPTY] = INT_MAX;
    parent[EMPTY] = 2;
    scanf("%d", &n);
    edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d%d", &a, &b, initWeight + i);
        a --;
        b --;
        addEdge(a, b);
        addEdge(b, a);
    }
    nodeCount = 0;
    root = EMPTY;
    dfs(-1, 0);
    for (int i = 0; i < n - 1; ++ i) {
        int id;
        scanf("%d", &id);
        id --;

        int a = position[id << 1];
        int b = position[(id << 1) ^ 1];
        if (getRank(a) > getRank(b)) {
            swap(a, b);
        }
        splay(a);

        int output = weight[a];
        printf("%d\n", output);
        fflush(stdout);

        pair <int, int> ret1 = split(a);
        pair <int, int> ret2 = split(b);
        int x = ret1.first;
        int y = ret2.first;
        int z = ret2.second;
        x = join(z, x);
        splay(x);
        splay(y);
        if (size[x] > size[y]) {
            swap(x, y);
        }
        if (size[x] == size[y] && minimum[x] > minimum[y]) {
            swap(x, y);
        }
        modify(x, output, 0);
        modify(y, 1, output);
    }
    return 0;
}
