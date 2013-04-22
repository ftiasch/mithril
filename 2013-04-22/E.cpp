#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int N = 400000 + 1;

int treap_count, key[N], weight[N], count[N], size[N], children[N][2];

void update(int &x) {
    size[x] = size[children[x][0]] + count[x] + size[children[x][1]];
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, int k) {
    if (!x) {
        x = treap_count ++;
        key[x] = k;
        weight[x] = rand();
        count[x] = 1;
    } else if (key[x] == k) {
        count[x] ++;
    } else {
        int t = key[x] < k;
        insert(children[x][t], k);
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    }
    update(x);
}

int query(int &x, int k) {
    if (!x) {
        return 0;
    }
    if (key[x] >= k) {
        return query(children[x][0], k);
    }
    return size[children[x][0]] + count[x] + query(children[x][1], k);
}

int main() {
    treap_count = 1;
    weight[0] = INT_MAX;
    size[0] = 0;

    int m;
    scanf("%d", &m);
    int d = 0;
    int total = 0;
    int lefts = 0;
    int rights = 0;
    while (m --) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            total ++;
            int a, b;
            scanf("%d%d", &a, &b);
            a += d;
            b += d;
            insert(rights, b);
            insert(lefts, -a);
        } else {
            int x;
            scanf("%d", &x);
            d = total;
            d -= query(rights, x);
            d -= query(lefts, -x);
            printf("%d\n", d);
        }
    }
    return 0;
}
