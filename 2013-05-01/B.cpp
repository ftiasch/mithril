#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 300000;
const int M = 600000 + 1;

char string[N + 1];
int n, sum[N + 1], maximum[N + 1], array[M];

void update(int k, int v) {
    for (; k < M; k += ~k & k + 1) {
        array[k] = std::max(array[k], v);
    }
}

int main() {
    scanf("%s", string);
    n = strlen(string);
    sum[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        sum[i] = sum[i + 1] + (string[i] == 'W' ? 1 : -1);
    }
    maximum[n] = 0;
    memset(array, 0, sizeof(array));
    update(sum[n] + N, n);
    for (int i = n - 1; i >= 0; -- i) {
        maximum[i] = maximum[i + 1];
        for (int j = sum[i] + N - 1; j >= 0; j -= ~j & j + 1) {
            maximum[i] = std::max(maximum[i], array[j] - i);
        }
        update(sum[i] + N, maximum[i] + i);
    }
    printf("%d\n", maximum[0]);
    return 0;
}
