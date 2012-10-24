#include <cstdio>
#include <cstring>
using namespace std;

const int N = 200000 + 1;

int n, m, k, weight[N], value[N];
int weightSum[N], valueSum[N];

int find(int i) {
    int low = -1;
    int high = i;
    while (low < high) {
        int middle = (low + high + 1) >> 1;
        if (k * (weightSum[middle] - weightSum[i]) >= weightSum[i] - weightSum[i + m]) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return low;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    weightSum[n] = valueSum[n] = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", weight + i, value + i);
    }
    for (int i = n - 1; i >= 0; -- i) {
        weightSum[i] = weightSum[i + 1] + weight[i];
        valueSum[i] = valueSum[i + 1] + value[i];
    }
    int result = 0;
    int best = -1;
    for (int i = n - m; i >= 0; -- i) {
        int low = find(i);
        if (low < 0) {
            break;
        }
        if (valueSum[0] - (valueSum[low] - valueSum[i + m]) > result) {
            best = i;
            result = valueSum[0] - (valueSum[low] - valueSum[i + m]);
        }
    }
    if (best == -1) {
        puts("0 0");
    } else {
        int low = find(best);
        printf("%d %d\n", n - ((best + m) - low), result);
        for (int i = n - 1; i >= best + m; -- i) {
            putchar('H');
        }
        for (int i = 0; i < low; ++ i) {
            putchar('T');
        }
        puts("");
    }
    return 0;
}
