#include <cstdio>
#include <cstring>

const int N = 10000;
const int K = 1000;

int n, k, a[N], b[N], count[N + 1][K + 2];

int main() {
    scanf("%d%d", &n, &k);
    k += 2;
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", a + i, b + i);
        a[i] ++;
        b[i] ++;
    }
    memset(count, 0, sizeof(count));
    for (int i = n - 1; i >= 0; -- i) {
        for (int j = 0; j < k; ++ j) {
            count[i][j] = count[i + 1][j];
            if (a[i] <= j && j < b[i]) {
                count[i][j] ++;
            }
        }
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        int l, r;
        scanf("%d%d", &l, &r);
        l --;
        int answer = 0;
        for (int i = 1; i < k; ++ i) {
            answer += (count[l][i - 1] - count[r][i - 1] > 0) ^ (count[l][i] - count[r][i] > 0);
        }
        printf("%d\n", answer);
    }
    return 0;
}
