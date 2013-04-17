#include <iostream>
#include <cstring>

long long memory[20][200];

int digit[20];

long long count(bool less, int length, int sum) {
    if (length) {
        if (less && memory[length][sum] != -1) {
            return memory[length][sum];
        }
        long long ret = 0;
        for (int i = 0; i < 10; ++ i) {
            if (!less && digit[length - 1] < i) {
                continue;
            }
            ret += count(less || i < digit[length - 1], length - 1, sum + i);
        }
        if (less) {
            memory[length][sum] = ret;
        }
        return ret;
    }
    return less ? sum : 0;
}

long long solve(long long n) {
    int length = 0;
    while (n) {
        digit[length ++] = n % 10;
        n /= 10;
    }
    return count(false, length, 0);
}

int main() {
    memset(memory, -1, sizeof(memory));
    int test_count;
    std::cin >> test_count;
    while (test_count --) {
        long long a, b;
        std::cin >> a >> b;
        std::cout << solve(b + 1) - solve(a) << std::endl;
    }
    return 0;
}
