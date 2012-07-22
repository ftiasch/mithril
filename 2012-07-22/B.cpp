#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;

const int N = 15;
const int M = 40;

int n, m, switches[M], minimum[1 << N], queue[1 << N];
char buffer[N + 1];

int main() {
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        printf("Case %d:\n", t);
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++ i) {
            switches[i] = 0;
            int k;
            scanf("%d", &k);
            while (k > 0) {
                k --;
                int x;
                scanf("%d", &x);
                switches[i] ^= 1 << x;
            }
        }
        for (int i = 0; i < (1 << n); ++ i) {
            minimum[i] = INT_MAX;
        }
        minimum[0] = 0;
        int tail = 0;
        queue[tail ++] = 0;
        int head = 0;
        while (head != tail) {
            int current = queue[head ++];
            for (int i = 0; i < m; ++ i) {
                if (minimum[current] + 1 < minimum[current ^ switches[i]]) {
                    minimum[current ^ switches[i]] = minimum[current] + 1;
                    queue[tail ++] = current ^ switches[i];
                }
            }
        }
        int queryCount;
        scanf("%d", &queryCount);
        while (queryCount > 0) {
            queryCount --;
            scanf("%s", buffer);
            int mask = 0;
            for (int i = 0; i < n; ++ i) {
                mask = (mask << 1) | (buffer[i] - '0');
            }
            if (minimum[mask] == INT_MAX) {
                puts("-1");
            } else {
                printf("%d\n", minimum[mask]);
            }
        }
        puts("");
    }
    return 0;
}
