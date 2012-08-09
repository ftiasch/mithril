#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int N = 222222;

int n, size[N], children[N][2], parent[N], type[N], cnt[N];

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

int findLeftMost(int x) {
    while (children[x][0]) {
        x = children[x][0];
    }
    return x;
}

void remove(int a) {
    splay(a);
    if (children[a][0]) {
        type[children[a][0]] = 2;
        parent[children[a][0]] = 0;
    }
    if (children[a][1]) {
        type[children[a][1]] = 2;
        parent[children[a][1]] = 0;
    }
    if (children[a][0] && children[a][1]) {
        int r = findLeftMost(children[a][1]);
        splay(r);
        children[r][0] = children[a][0];
        type[children[a][0]] = 0;
        parent[children[a][0]] = r;
        splay(children[a][0]);
    }
    type[a] = 2;
    parent[a] = children[a][0] = children[a][1] = 0;
}

int main() {
    size[0] = 0;
    memset(cnt, 0, sizeof(cnt));
    memset(parent, 0, sizeof(parent));
    memset(children, 0, sizeof(children));
    type[100001] = 2;
    splay(100001);
    int queryCount;
    scanf("%d", &queryCount);
    while (queryCount) {
        queryCount --;
        int op, a, b;
        scanf("%d%d", &op, &a);
        if (op == 2) {
            remove(a);
            cnt[a] --;
        } else {
            scanf("%d", &b);
            if (op == 0) {
                if (!cnt[a] || !cnt[b]) {
                    puts("0");
                } else {
                    splay(a);
                    int result = size[children[a][0]];
                    splay(b);
                    result -= size[children[b][0]];
                    printf("%d\n", abs(result) + 1);
                }
            } else {
                if (b == 0) {
                    b = 100001;
                }
                cnt[a] ++;
                splay(b);
                if (children[b][1]) {
                    int t = findLeftMost(children[b][1]);
                    children[t][0] = a;
                    type[a] = 0;
                    parent[a] = t;
                } else {
                    children[b][1] = a;
                    type[a] = 1;
                    parent[a] = b;
                }
                splay(a);
            }
        }
    }
    return 0;
}
