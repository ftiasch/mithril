#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100000;
const int MAGIC = 217;

typedef unsigned long long Hash;

char string[N + 1];
Hash hash[N + 1], power[N + 1];

int main() {
    power[0] = 1;
    for (int i = 0; i < N; ++ i) {
        power[i + 1] = power[i] * MAGIC;
    }
    while (scanf("%s", string) == 1) {
        if (*string == '*') {
            break;
        }
        int n = strlen(string);
        hash[n] = 0;
        for (int i = n - 1; i >= 0; -- i) {
            hash[i] = hash[i + 1] * MAGIC + string[i];
        }
        int q;
        scanf("%d", &q);
        while (q --) {
            int i, j;
            scanf("%d%d", &i, &j);
            int low = 0;
            int high = n - std::max(i, j);
            while (low < high) {
                int middle = low + high + 1 >> 1;
                if (hash[i] - hash[i + middle] * power[middle] == hash[j] - hash[j + middle] * power[middle]) {
                    low = middle;
                } else {
                    high = middle - 1;
                }
            }
            printf("%d\n", low);
        }
    }
    return 0;
}
