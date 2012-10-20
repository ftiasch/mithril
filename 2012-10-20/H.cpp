#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 200000 + 1;

int nodeCount, size[N], weight[N], children[N][2], value[N], minimum[N];

void update(int &x) {
    size[x] = size[children[x][0]] + 1 + size[children[x][1]];
    minimum[x] = min(value[x], min(minimum[children[x][0]], minimum[children[x][1]]));
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, int k, int v) {
    if (!x) {
        x = ++ nodeCount;
        value[x] = v;
        weight[x] = rand();
    } else {
        int t = size[children[x][0]] < k;
        if (t) {
            insert(children[x][1], k - (size[children[x][0]] + 1), v);
        } else {
            insert(children[x][0], k, v);
        }
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    }
    update(x);
}

int query(int &x, int a, int b) {
    if (!x) {
        return INT_MAX;
    }
    if (a == 1 && b == size[x]) {
        return minimum[x];
    }
    int ret = INT_MAX;
    if (a <= size[children[x][0]] + 1 && size[children[x][0]] + 1 <= b) {
        ret = min(ret, value[x]);
    }
    if (a <= size[children[x][0]]) {
        ret = min(ret, query(children[x][0], a, min(b, size[children[x][0]])));
    }
    int base = size[children[x][0]] + 1;
    if (base < b) {
        ret = min(ret, query(children[x][1], max(a - base, 1), b - base));
    }
    return ret;
}

int main() {
    size[0] = 0;
    weight[0] = INT_MAX;
    minimum[0] = INT_MAX;
    nodeCount = 0;
    memset(children, 0, sizeof(children));
    int root = 0;
    int m;
    scanf("%d", &m);
    while (m --) {
        char type[2];
        scanf("%s", type);
        if (*type == '?') {
            int i, j;
            scanf("%d%d", &i, &j);
            printf("%d\n", query(root, i, j));
        } else {
            int i, x;
            scanf("%d%d", &i, &x);
            insert(root, i, x);
        }
    }
    return 0;
}
