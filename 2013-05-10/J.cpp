#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int N = 100000;

int n, a[N], pre[N], hash[N + 1], maximum[N << 1], expand[N];

int get_id(int l, int r) {
    return l + r | l != r;
}

void build(int l, int r) {
    if (l < r) {
        int m = l + r >> 1;
        build(l, m);
        build(m + 1, r);
        maximum[get_id(l, r)] = std::max(maximum[get_id(l, m)], maximum[get_id(m + 1, r)]);
    } else {
        maximum[get_id(l, r)] = pre[l];
    }
}

int query(int l, int r, int a, int b) {
    if (b < l || r < a) {
        return INT_MIN;
    }
    if (a <= l && r <= b) {
        return maximum[get_id(l, r)];
    }
    int m = l + r >> 1;
    return std::max(query(l, m, a, b), query(m + 1, r, a, b));
}

bool solve(int l, int r) {
    if (query(0, n - 1, l, r) < l) {
        return true;
    }
    int p = r - pre[r];
    if (query(0, n - 1, l, l + p - 1) < l && r - expand[r] <= l + p - 1) {
        return true;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        a[i] --;
    }
    memset(hash, -1, sizeof(hash));
    for (int i = 0; i < n; ++ i) {
        pre[i] = hash[a[i]];
        if (i && i - pre[i] == i - 1 - pre[i - 1]) {
            expand[i] = expand[i - 1] + 1;
        } else {
            expand[i] = true;
        }
        hash[a[i]] = i;
    }
    build(0, n - 1);
    int q;
    scanf("%d", &q);
    while (q --) {
        int l, r;
        scanf("%d%d", &l, &r);
        l --;
        r --;
        printf("%d", solve(l, r));
    }
    puts("");
    return 0;
}
