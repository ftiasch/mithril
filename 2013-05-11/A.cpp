#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 100000;

int n, s, a[N];

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    std::sort(a, a + n);
    std::vector <int> order;
    int total = 0;
    int i, j;
    for (i = 0, j = n - 1; i < j; ) {
        if (a[i] + a[j] <= s) {
            total ++;
            order.push_back(a[i ++]);
            order.push_back(a[i ++]);
        } else {
            total ++;
            order.push_back(a[i ++]);
            total ++;
            order.push_back(a[j --]);
        }
    }
    if (i == j) {
        total ++;
        order.push_back(a[i]);
    }
    printf("%d\n", total);
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", order[i], " \n"[i == n - 1]);
    }
    return 0;
}
