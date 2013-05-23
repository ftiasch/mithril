#include <cstdio>
#include <cstring>
#include <algorithm>
 
const int K = 1000000;
const int M = 200000;
 
struct Pair {
    int a, b;
 
    Pair(int a = 0, int b = 0) : a(a), b(b) {}
};
 
bool operator < (const Pair &p, const Pair &q) {
    if (p.a != q.a) {
        return p.a < q.a;
    }
    return p.b > q.b;
}
 
int n, m, k, mod;
Pair pairs[K];
 
int count[M + 1];
 
void add(int k, int v) {
    for (int i = k; i <= m; i += ~i & i + 1) {
        (count[i] += v) %= mod;
    }
}
 
int ask(int k) {
    int ret = 0;
    for (int i = k; i >= 0; i -= ~i & i + 1) {
        (ret += count[i]) %= mod;
    }
    return ret;
}
 
int main() {
    freopen("electricity.in", "r", stdin);
    freopen("electricity.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &k, &mod);
    for (int i = 0; i < k; ++ i) {
        scanf("%d%d", &pairs[i].a, &pairs[i].b);
    }
    std::sort(pairs, pairs + k);
    memset(count, 0, sizeof(count));
    int answer = 1;
    add(0, 1);
    for (int i = 0; i < k; ++ i) {
        int now = ask(pairs[i].b - 1);
        add(pairs[i].b, now);
        (answer += now) %= mod;
    }
    printf("%d\n", answer);
    return 0;
}
