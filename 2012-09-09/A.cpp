#include <cstdio>
#include <cstring>
using namespace std;

int mapping[10] = {0, 1, 2, -1, 3, 4, 5, 6, -1, 7};

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n > 0) {
        int backup = n;
        int base = 1;
        int result = 0;
        while (n > 0) {
            result += base * mapping[n % 10];
            n /= 10;
            base *= 8;
        }
        printf("%d: %d\n", backup, result);
    }
    return 0;
}
