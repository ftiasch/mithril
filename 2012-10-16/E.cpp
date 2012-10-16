#include <cstdio>
#include <cstring>
using namespace std;

int n, a, b;

int main() {
    scanf("%d%d%d", &n, &a, &b);
    int best = -1, best_i, best_j;
    for (int i = 1; i <= n; ++ i) {
        for (int j = i; j > 0; j = (j - 1) & i) {
            int ret = (a * i + b * j) ^ (a * j + b * i);
            if (ret > best) {
                best = ret;
                best_i = i;
                best_j = j;
            }
        }
    }
    printf("%d %d\n", best_i, best_j);
    return 0;
}
