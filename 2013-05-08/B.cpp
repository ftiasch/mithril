#include <cassert>
#include <cstdio>
#include <algorithm>

const int N = 100000;

int n, a[N], b[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    int conflict = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", b + i);
        conflict += a[i] == b[i];
    }
    if (n == 1) {
        puts("-1");
        return 0;
    }
    if (!conflict) {
        puts("0");
    } else {
        puts("1");
        for (int i = 0; i < n; ++ i) {
            if (a[i] == b[i]) {
                int j = i;
                while (j < n && a[j] == b[j]) {
                    j ++;
                }
                if (j - i > 1) {
                    for (int k = i + 1; k < j; ++ k) {
                        b[k] = a[k - 1];
                    }
                    b[i] = a[j - 1];
                } else if (i == n - 1) {
                    std::swap(b[n - 2], b[n - 1]);
                } else {
                    std::swap(b[i], b[i + 1]);
                }
                i = j - 1;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", b[i], " \n"[i == n - 1]);
    }
    return 0;
}
