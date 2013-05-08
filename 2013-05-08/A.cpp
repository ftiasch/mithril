#include <cstdio>

const int N = 100;

int n, a[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    int count = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = i; j < n; ++ j) {
            count += a[i] < a[j];
        }
    }
    puts(count & 1 ? "First" : "Second");
    return 0;
}
