#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000;

int n, a[N], s[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i + 2 < n; ++ i) {
        s[i] = a[i] + a[i + 1] + a[i + 2];
    }
    int i = max_element(s, s + (n - 2)) - s;
    printf("%d %d\n", s[i], i + 2);
    return 0;
}
