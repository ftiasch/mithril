#include <cstdio>
#include <iostream>

typedef unsigned long long ULL;

ULL pow(ULL a, ULL n, ULL m) {
    ULL ret = 1 % m;
    while (n) {
        if (n & 1) {
            ret = ret * a % m;
        }
        a = a * a % m;
        n >>= 1;
    }
    return ret;
}

int main() {
    int test_count;
    std::cin >> test_count;
    while (test_count --) {
        unsigned long long a, p;
        std::cin >> a >> p;
        if (p == 2) {
            puts("Yes");
        } else {
            if (pow(a, p / 2, p) == 1) {
                puts("Yes");
            } else {
                puts("No");
            }
        }
    }
    return 0;
}
