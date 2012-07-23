#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 222;

int n, value[N], maximum[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", value + i);
        value[n + i] = value[i];
    }
    memset(maximum, 0, sizeof(maximum));
    for (int i = n + n - 1; i >= 0; -- i) {
        for (int j = i; j < n + n; ++ j) {
            for (int k = i; k < j; ++ k) {
                maximum[i][j] = max(maximum[i][j], maximum[i][k] + maximum[k + 1][j] + abs(value[i] - value[k + 1]));
            }
        }
    }
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        result = max(result, maximum[i][i + n - 1]);
    }
    printf("%d\n", result);
    return 0;
}
