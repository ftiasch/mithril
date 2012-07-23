#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 17;

int n, up[N], down[N], previous[N];
long long ways[1 << N];
bool graph[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", up + i);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", down + i);
    }
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < n; ++ i) {
        for (int j = 1; j < up[i]; ++ j) {
            graph[i + j][i] = true;
        }
        if (i + up[i] < n) {
            graph[i][i + up[i]] = true;
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 1; j < down[i]; ++ j) {
            graph[i][i + j] = true;
        }
        if (i + down[i] < n) {
            graph[i + down[i]][i] = true;
        }
    }
    for (int k = 0; k < n; ++ k) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                graph[i][j] |= graph[i][k] && graph[k][j];
            }
        }
    }
    memset(previous, 0, sizeof(previous));
    for (int j = 0; j < n; ++ j) {
        for (int i = 0; i < n; ++ i) {
            if (i != j && graph[i][j]) {
                previous[j] |= 1 << i;
            }
        }
    }
    memset(ways, 0, sizeof(ways));
    ways[0] = 1;
    for (int mask = 0; mask < (1 << n); ++ mask) {
        for (int i = 0; i < n; ++ i) {
            if (!(mask >> i & 1) && (previous[i] & mask) == previous[i]) {
                ways[mask | (1 << i)] += ways[mask];
            }
        }
    }
    cout << ways[(1 << n) - 1] << endl;
    return 0;
}
