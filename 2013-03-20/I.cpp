#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100000 << 1;

int n, a[N], b[N], order[N];

bool by_a(int i, int j) {
    return a[i] > a[j];
}

int main() {
    scanf("%d", &n);
    n <<= 1;
    n --;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    long long sum_b = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", b + i);
        sum_b -= b[i];
    }
    for (int i = 0; i < n; ++ i) {
        order[i] = i;
    }
    std::sort(order, order + n, by_a);
    for (int i = 0; i < n; ++ i) {
        if (~i & 1) {
            sum_b += b[order[i]];
            sum_b += b[order[i]];
        }
    }
    if (sum_b > 0) {
        for (int i = 0; i < n; ++ i) {
            if (~i & 1) {
                printf("%d ", order[i] + 1);
            }
        }
        puts("");
    } else {
        printf("%d", order[0] + 1);
        for (int i = 1; i < n; ++ i) {
            if (i & 1) {
                printf(" %d", order[i] + 1);
            }
        }
    }
    return 0;
}
