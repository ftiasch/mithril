#include <cstdio>
#include <cstring>
#include <iostream>

long long memory[100][100];

long long solve(int length, bool less, int n, int k) {
    if (length == 0) {
        return k == 0 && less;
    }
    if (less && memory[length][k] != -1) {
        return memory[length][k];
    }
    long long ret = 0;
    for (int i = 0; i < 2; ++ i) {
        if (i > (n >> length - 1 & 1) && !less) {
            continue;
        }
        if (i > k) {
            continue;
        }
        ret += solve(length - 1, less || i < (n >> length - 1 & 1), n, k - i);
    }
    if (less) {
        memory[length][k] = ret;
    }
    return ret;
}

long long count(int n, int k) {
    return solve(31, false, n, k);
}

int main() {
    memset(memory, -1, sizeof(memory));
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        int a, b, k;
        scanf("%d%d%d", &k, &a, &b);
        a --, b --;
        long long answer = 0;
        for (int i = 0; i <= k; ++ i) {
            long long size = count(b + 1, i) - count(a, i);
            answer += size * (1L << k - i);
        }
        std::cout << "Case " << t << ": " << answer << std::endl;
    }
    return 0;
}
