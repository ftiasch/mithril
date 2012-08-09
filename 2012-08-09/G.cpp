#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 111111;

int n, lower, uppers[N], value[N], next[N];
pair <int, int> data[N << 2];

void build(int t, int l, int r) {
    data[t] = make_pair(INT_MAX, -1);
    if (l < r) {
        int m = (l + r) >> 1;
        build(t << 1, l, m);
        build((t << 1) + 1, m + 1, r);
    }
}

void insert(int t, int l, int r, int k, int v) {
    if (k < l || r < k) {
        return;
    }
    if (l == k && k == r) {
        data[t] = make_pair(v, k);
    } else {
        int m = (l + r) >> 1;
        insert(t << 1, l, m, k, v);
        insert((t << 1) + 1, m + 1, r, k, v);
        data[t] = min(data[t << 1], data[(t << 1) + 1]);
    }
}

pair <int, int> query(int t, int l, int r, int a, int b) {
    if (b < l || r < a) {
        return make_pair(INT_MAX, -1);
    }
    if (a <= l && r <= b) {
        return data[t];
    }
    int m = (l + r) >> 1;
    return min(query(t << 1, l, m, a, b), query((t << 1) + 1, m + 1, r, a, b));
}

int main() {
    scanf("%d%d", &n, &lower);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", uppers + i);
    }
    for (int i = 1; i <= n; ++ i) {
        value[i] = INT_MAX;
    }
    build(1, 1, n);
    value[n] = 0;
    insert(1, 1, n, n, 0);
    for (int i = n - 1; i >= 1; -- i) {
        if (lower <= uppers[i]) {
            pair <int, int> ret = query(1, 1, n, i + lower, i + uppers[i]);
            if (ret.first != INT_MAX) {
                value[i] = ret.first + 1;
                next[i] = ret.second;
                insert(1, 1, n, i, value[i]);
            }
        }
    }
    if (value[1] == INT_MAX) {
        puts("IMPOSSIBLE");
    } else {
        puts("POSSIBLE");
        printf("%d\n", value[1]);
        for (int i = 1; i != n; i = next[i]) {
            printf("%d %d\n", i, next[i] - i);
        }
    }
    return 0;
}
