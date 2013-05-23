#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
 
const int N = 200000;
 
int n, m, a[N], b[N], delta[N << 1], maximum[N << 1];
 
int get_id(int l, int r) {
    return l + r | (l != r);
}
 
void add(int l, int r, int a, int b, int c) {
    if (b < l || r < a) {
        return;
    }
    int id = get_id(l, r);
    int m = l + r >> 1;
    if (a <= l && r <= b) {
        delta[id] += c;
        maximum[id] += c;
    } else {
        add(l, m, a, b, c);
        add(m + 1, r, a, b, c);
        maximum[id] = std::max(maximum[get_id(l, m)], maximum[get_id(m + 1, r)]) + delta[id];
    }
}
 
int find(int l, int r, int v) {
    if (l == r) {
        return l;
    }
    int m = l + r >> 1;
    v -= delta[get_id(l, r)];
    if (maximum[get_id(m + 1, r)] >= v) {
        return find(m + 1, r, v);
    }
    return find(l, m, v);
}
 
int get(int l, int r, int k) {
    int id = get_id(l, r);
    int m = l + r >> 1;
    if (l == r) {
        return delta[id];
    }
    return (k <= m ? get(l, m, k) : get(m + 1, r, k)) + delta[id];
}
 
int main() {
    freopen("balloons.in", "r", stdin);
    freopen("balloons.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    std::sort(a, a + n, std::greater <int>());
    for (int i = 0; i < m; ++ i) {
        scanf("%d", b + i);
    }
    std::sort(b, b + m, std::greater <int>());
    memset(delta, 0, sizeof(delta));
    memset(maximum, 0, sizeof(maximum));
    for (int i = 0; i < n; ++ i) {
        add(0, n - 1, i, i, a[i]);
    }
    if (b[0] > n) {
        puts("NO");
        return 0;
    }
    for (int i = 0; i < m; ++ i) {
        int v = get(0, n - 1, b[i] - 1);
        int x = maximum[get_id(0, n - 1)] > v ? find(0, n - 1, v + 1) : -1;
        int y = find(0, n - 1, v);
        if (x >= 0) {
            add(0, n - 1, 0, x, -1);
        }
        int left = b[i] - (x + 1);
        add(0, n - 1, y - left + 1, y, -1);
    }
    puts(get(0, n - 1, n - 1) >= 0 ? "YES" : "NO");
    return 0;
}
