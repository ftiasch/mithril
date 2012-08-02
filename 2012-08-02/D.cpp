#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 19;

int n, m, preMask[N];
bool graph[N][N];
long long ways[1 << N];

int main() {
    scanf("%d%d", &n, &m);
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        graph[a][b] = true;
    }
    for (int k = 0; k < n; ++ k) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                graph[i][j] |= graph[i][k] && graph[k][j];
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        graph[i][i] = false;
    }
    for (int i = 0; i < n; ++ i) {
        preMask[i] = 0;
        for (int j = 0; j < n; ++ j) {
            if (graph[j][i]) {
                preMask[i] |= 1 << j;
            }
        }
    }
    memset(ways, 0, sizeof(ways));
    ways[0] = 1;
    for (int mask = 0; mask < 1 << n; ++ mask) {
        for (int i = 0; i < n; ++ i) {
            if (!(mask >> i & 1) && (mask & preMask[i]) == preMask[i]) {
                ways[mask | (1 << i)] += ways[mask];
            }
        }
    }
    cout << ways[(1 << n) - 1] << endl;
    return 0;
}
