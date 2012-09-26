#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 500000;

int n, low, high;
int edgeCount, firstEdge[N], to[N << 1], length[N << 1], nextEdge[N << 1];
int queue[N], level[N], depth[N], dp[N];
bool valid[N];

inline void addEdge(int a, int b, int c) {
    to[edgeCount] = b;
    length[edgeCount] = c;
    nextEdge[edgeCount] = firstEdge[a];
    firstEdge[a] = edgeCount ++;
}

inline int nextInt() {
    int result = 0;
    char ch = getchar();
    while (!isdigit(ch)) {
        ch = getchar();
    }
    while (isdigit(ch)) {
        result = result * 10 + ch - '0';
        ch = getchar();
    }
    return result;
}

int main() {
    while (scanf("%d%d%d", &n, &low, &high) == 3) {
        edgeCount = 0;
        for (int i = 0; i < n; ++ i) {
            firstEdge[i] = -1;
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a = nextInt();
            int b = nextInt();
            int c = nextInt();
            addEdge(a, b, c);
        }
        level[0] = 0;
        depth[0] = 0;
        int tail = 0;
        queue[tail ++] = 0;
        int head = 0;
        while (head != tail) {
            int u = queue[head ++];
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                level[to[iter]] = level[u] ^ 1;
                depth[to[iter]] = depth[u] + length[iter];
                queue[tail ++] = to[iter];
            }
        }
//for (int i = 0; i < n; ++ i) {
//    printf("%d, %d, %d\n", i, level[i], depth[i]);
//}
        //memset(valid, 0, sizeof(valid));
        for (int i = n - 1; i >= 0; -- i) {
            int u = queue[i];
            valid[u] = false;
            dp[u] = level[u] == 0? INT_MIN: INT_MAX;
            for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                valid[u] |= valid[to[iter]];
                if (valid[to[iter]]) {
                    if (level[u] == 0) {
                        dp[u] = max(dp[u], dp[to[iter]]);
                    } else {
                        dp[u] = min(dp[u], dp[to[iter]]);
                    }
                }
            }
            if (!valid[u] && low <= depth[u] && depth[u] <= high) {
                valid[u] = true;
                if (level[u] == 0) {
                    dp[u] = max(dp[u], depth[u]);
                } else {
                    dp[u] = min(dp[u], depth[u]);
                }
            }
        }
        if (!valid[0]) {
            puts("Oh, my god!");
        } else {
            printf("%d\n", dp[0]);
        }
    }
    return 0;
}
