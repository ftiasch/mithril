// Problem A -- Graph Theory
// Author: Xiaoxu Guo
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int d, r;
    scanf("%d%d", &d, &r);
    puts("YES");
    if (r == 1) {
        printf("%d %d\n", d + 1, d);
        for (int i = 1; i <= d; ++ i) {
            printf("%d %d\n", i, i + 1);
        }
    } else {
        printf("%d %d\n", d + r, d + r);
        for (int i = 0; i < r + r; ++ i) {
            printf("%d %d\n", i + 1, (i + 1) % (r + r) + 1);
        }
        for (int i = 1; i <= d - r; ++ i) {
            printf("%d %d\n", r + r + i, r + r + i - 1);
        }
    }
    return 0;
}
