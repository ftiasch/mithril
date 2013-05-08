#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 100 + 1;

int n, m, a[N], outDeg[N], inDeg[N];

bool by_height(int i, int j) {
    return a[i] < a[j];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
    }
    memset(outDeg, 0, sizeof(outDeg));
    memset(inDeg, 0, sizeof(inDeg));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        outDeg[a] ++;
        inDeg[b] ++;
    }
    std::vector <int> order;
    for (int i = 1; i <= n; ++ i) {
        if (!outDeg[i] || !inDeg[i]) {
            order.push_back(i);
        }
    }
    std::sort(order.begin(), order.end(), by_height);
    printf("%d\n%d\n", a[order.back()] - a[order.front()], (int)order.size() - 1);
    for (int i = 0; i + 1 < (int)order.size(); ++ i) {
        printf("%d %d\n", order[i], order[i + 1]);
    }
    return 0;
}
