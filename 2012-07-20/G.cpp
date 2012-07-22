#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 111111;

int n, m, a[N], b[N], v[N], order[N], left[N << 2], result[N];

bool compare(int i, int j) {
    return v[i] > v[j];
}

void build(int t, int l, int r) {
    left[t] = r - l + 1;
    if (l < r) {
        int m = (l + r) >> 1;
        build(t << 1, l, m);
        build((t << 1) + 1, m + 1, r);
    }
}

int query(int t, int l, int r, int a, int b) {
    if (b < l || r < a) {
        return 0;
    }
    if (a <= l && r <= b) {
        return left[t];
    }
    int m = (l + r) >> 1;
    return query(t << 1, l, m, a, b) + query((t << 1) + 1, m + 1, r, a, b);
}

void cover(int t, int l, int r, int a, int b, int v) {
    if (b < l || r < a) {
        return;
    }
    if (left[t] == 0) {
        return;
    }
    if (l == r) {
        left[t] --;
        result[l] = v;
    } else {
        int m = (l + r) >> 1;
        cover(t << 1, l, m, a, b, v);
        cover((t << 1) + 1, m + 1, r, a, b, v);
        left[t] = left[t << 1] + left[(t << 1) + 1];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d%d", a + i, b + i, v + i);
    }
    for (int i = 0; i < m; ++ i) {
        order[i] = i;
    }
    sort(order, order + m, compare);
    build(1, 1, n);
    bool valid = true;
    for (int lower = 0; lower < m; ++ lower) {
        int upper = lower;
        while (upper < m && v[order[upper]] == v[order[lower]]) {
            upper ++;
        }
        for (int i = lower; i < upper; ++ i) {
            valid &= query(1, 1, n, a[order[i]], b[order[i]]) > 0;
        }
        for (int i = lower; i < upper; ++ i) {
            cover(1, 1, n, a[order[i]], b[order[i]], v[order[i]]);
        }
        lower = upper - 1;
    }
    if (valid) {
        puts("consistent");
        for (int i = 1; i <= n; ++ i) {
            printf("%d%c", result[i], i == n? '\n': ' ');
        }
    } else {
        puts("inconsistent");
    }
    return 0;
}
