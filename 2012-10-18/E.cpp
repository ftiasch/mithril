#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;


const int N = 200000;

int n, mod, a[N], b[N], f[N];

int nodeCount, key[N], weight[N], counter[N], size[N], children[N][2];

void update(int &x) {
    size[x] = ((size[children[x][0]] + counter[x]) % mod + size[children[x][1]]) % mod;
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
        key[x] = k;
        counter[x] = v;
        children[x][0] = children[x][1] = 0;
        weight[x] = rand();
    } else if (key[x] == k) {
        counter[x] = (counter[x] + v) % mod;
    } else {
        int t = key[x] < k;
        insert(children[x][t], k, v);
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    }
    update(x);
}

int query(int &x, int k) {
    if (x) {
        if (key[x] > k) {
            return query(children[x][0], k);
        }
        return ((size[children[x][0]] + counter[x]) % mod + query(children[x][1], k)) % mod;
    }
    return 0;
}

int ways[N], root[N];

int main() {
    scanf("%d%d", &n, &mod);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        a[i] --;
    }
    memset(b, 0, sizeof(b));
    memset(f, 0, sizeof(f));
    for (int i = 0; i < n; ++ i) {
        for (int k = a[i]; k >= 0; k -= ~k & k + 1) {
            f[i] = max(f[i], b[k]);
        }
        f[i] ++;
        for (int k = a[i]; k < n; k += ~k & k + 1) {
            b[k] = max(b[k], f[i]);
        }
    }
    weight[0] = INT_MAX;
    size[0] = 0;
    nodeCount = 0;
    memset(root, 0, sizeof(root));
    int length = *max_element(f, f + n);
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        if (f[i] == 1) {
            ways[i] = 1 % mod;
        } else {
            ways[i] = query(root[f[i] - 1], a[i]);
        }
        insert(root[f[i]], a[i], ways[i]);
        if (f[i] == length) {
            result = (result + ways[i]) % mod;
        }
    }
    printf("%d\n", result);
    return 0;
}
