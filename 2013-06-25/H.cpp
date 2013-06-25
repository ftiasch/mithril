#include <cstdio>
#include <cstring>

int sqr(int x) {
    return x * x;
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        int n;
        scanf("%d", &n);
        int answer = 0;
        for (int i = 0; i < n; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            int p = 10;
            while (p >= 1 && sqr(20 * (11 - p)) < sqr(x) + sqr(y)) {
                p --;
            }
            answer += p;
        }
        printf("%d\n", answer);
    }
    return 0;
}
