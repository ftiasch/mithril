#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 10001;
const int INFINITY = 1000000000;

int n, m, weight[N], inQueue[N];
vector <int> friends[N];

int type[N], parent[N], children[N][2], size[N], maximum[N];

void update(int x) {
    size[x] = size[children[x][0]] + 1 + size[children[x][1]];
    maximum[x] = max(weight[x], max(maximum[children[x][0]], maximum[children[x][1]]));
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
    }
    update(x);
}

int find(int x, int t) {
    while (children[x][t]) {
        x = children[x][t];
    }
    return x;
}

int main() {
    size[0] = 1;
    maximum[0] = -INFINITY;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", weight + i);
    }
    for (int i = 1; i <= m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        friends[a].push_back(b);
        friends[b].push_back(a);
    }
    vector <int> result;
    memset(inQueue, 0, sizeof(inQueue));
    memset(children, 0, sizeof(children));
    int root = 0;
    int i = 0;
    for (int k = 0; k < 2 * n; ++ k) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            i ++;
            int j = -1;
            int best = INT_MAX;
            for (vector <int> :: iterator iter = friends[i].begin(); iter != friends[i].end(); ++ iter) {
                if (inQueue[*iter]) {
                    splay(*iter);
                    root = *iter;
                    if (weight[*iter] + weight[i] > 2 * maximum[children[*iter][1]] && size[children[*iter][0]] < best) {
                        j = *iter;
                        best = size[children[*iter][0]];
                    }
                }
            }
//printf("%d -- %d\n", i, j);
            if (j == -1) {
                if (root == 0) {
                    type[i] = 2;
                } else {
                    int x = find(root, 1);
                    children[x][1] = i;
                    type[i] = 1;
                    parent[i] = x;
                }
            } else {
                splay(j);
                root = j;
                int t = weight[i] > weight[j];
                if (children[j][1 ^ t]) {
                    int x = find(children[j][1 ^ t], t);
                    children[x][t] = i;
                    type[i] = t;
                    parent[i] = x;
                } else {
                    children[j][1 ^ t] = i;
                    type[i] = 1 ^ t;
                    parent[i] = j;
                }
            }
            splay(i);
            root = i;
            inQueue[i] = true;
        } else {
            int x = find(root, 0);
            splay(x);
            root = x;
            result.push_back(x);
            inQueue[x] = false;
            if (children[x][1]) {
                type[children[x][1]] = 2;
            }
            root = children[x][1];
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", result[i], i == n - 1? '\n': ' ');
    }
    return 0;
}
