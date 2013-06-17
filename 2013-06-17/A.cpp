#include <cstdio>
#include <cstring>

const int K = 9;
const int N = 10;

int n, m, k, a[K], map[N][N];

int main() {
    freopen("addictive.in", "r", stdin);
    freopen("addictive.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < k; ++ i) {
        scanf("%d", a + i);
    }
    int p = 0;
    for (int i = 0; i < n; ++ i) {
        int d = i & 1 ? -1 : 1;
        for (int j = i & 1 ? m - 1 : 0; 0 <= j && j < m; j += d) {
            while (a[p] == 0) {
                p ++;
            }
            map[i][j] = p;
            a[p] --;
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            printf("%d", 1 + map[i][j]);
        }
        puts("");
    }
    return 0;
}
