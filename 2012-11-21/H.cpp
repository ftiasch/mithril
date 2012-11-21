#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000;

int n, m, a[N], c[N], s[N + 1];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    sort(a, a + n);
    {
        int new_n = 0;
        for (int i = 0; i < n; ++ i) {
            if (new_n == 0 || a[new_n - 1] < a[i]) {
                c[new_n] = 0;
                a[new_n ++] = a[i];
            }
            c[new_n - 1] ++;
        }
        n = new_n;
    }
    s[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        s[i] = s[i + 1] + c[i];
    }
    int step = 0;
    int now = 0;
    while (now < n) {
        int i = now;
        while (i<n && (s[now] - s[i + 1]) * a[i] <= m) {
            i ++;
        }
        if (now == i) {
            break;
        }
        now = i;
        step ++;
    }
    printf("%d %d\n", s[0] - s[now], step);
    return 0;
}
