#include <cstdio>
#include <cstring>

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        for (int j = i + 1; j <= n; ++ j) {
            printf("%d %d %d\n", i, j, (i - j) * (i - j));
            if (!(-- m)) {
                return 0;
            }
        }
    }
    return 0;
}
