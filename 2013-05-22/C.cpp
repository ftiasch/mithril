#include <cstdio>
#include <cstring>
 
int main() {
    freopen("computation.in", "r", stdin);
    freopen("computation.out", "w", stdout);
    int n, d;
    scanf("%d%d", &n, &d);
    if (d == 0) {
        puts("NONE");
    } else if (d == 1) {
        if (n == 2) {
            puts("1 2");
        } else {
            puts("NONE");
        }
    } else {
        for (int i = 1; i <= d; ++ i) {
            printf("%d %d\n", i, i + 1);
        }
        for (int i = d + 2; i <= n; ++ i) {
            printf("%d %d\n", i, 2);
        }
    }
    return 0;
}
