#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 1000;

int maximum[N];
char container[N + 1];

int main() {
    int test_count = 0;
    while (true) {
        scanf("%s", container);
        if (strcmp(container, "end") == 0) {
            break;
        }
        int n = strlen(container);
        for (int i = 0; i < n; ++ i) {
            maximum[i] = 1;
            for (int j = 0; j < i; j ++) {
                if (container[j] < container[i]) {
                    maximum[i] = std::max(maximum[i], maximum[j] + 1);
                }
            }
        }
        printf("Case %d: %d\n", ++ test_count, *std::max_element(maximum, maximum + n));
    }
    return 0;
}
