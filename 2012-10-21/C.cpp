#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000;

int n, a[N];

int main() {
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        sum += a[i];
    }
    int less = 0;
    int great = 0;
    for (int i = 0; i < n; ++ i) {
        int delta = a[i] * n - sum;
        if (delta > 0) {
            great ++;
        }
    }
    printf("%d\n", max(less, great));
    return 0;
}
