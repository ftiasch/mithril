#include <cstdio>
#include <cstring>

int n, t, s;

int main() {
    scanf("%d%d%d", &n, &t, &s);
    while (n --) {
        int si;
        scanf("%d", &si);
        printf("%.6f\n", (s + si + t) / 2.0);
    }
    return 0;
}
