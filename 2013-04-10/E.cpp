#include <cstdio>
#include <cstring>
#include <algorithm>

bool swaped;

void print(int x, int y) {
    if (swaped) {
        std::swap(x, y);
    }
    printf("First %d %d\n", x, y);
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        int n, m;
        scanf("%d%d", &n, &m);
        swaped = n > m;
        if (swaped) {
            std::swap(n, m);
        }
        if (n == 1) {
            print(1, 1);
        } else if (n == 2) {
            if (m % 4 == 0) {
                puts("Second");
            } else {
                print(1, m % 4 == 3 ? 2 : 1);
            }
        } else if (n == 3 && m == 3) {
            print(2, 2);
        } else if (n * m % 2 == 0) {
            puts("Second");
        } else {
            print(1, 1);
        }
    }
    return 0;
}
