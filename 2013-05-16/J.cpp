#include <cstdio>
#include <cstring>
#include <algorithm>

typedef unsigned long long Hash;

const int N = 222222;
const Hash MAGIC = 100003;

int n;
char text[N];

Hash prefix[N], suffix[N], power[N];

int get_lcp(int i, int j) {
    int low = 0;
    int high = std::min(i, 2 * n + 2 - j);
    while (low < high) {
        int middle = low + high + 1 >> 1;
        if (prefix[i] - power[middle] * prefix[i - middle] == suffix[j] - power[middle] * suffix[j + middle]) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return low;
}

int main() {
    power[0] = 1;
    for (int i = 1; i < N; ++ i) {
        power[i] = power[i - 1] * MAGIC;
    }
    scanf("%d%s", &n, text + 1);
    scanf("%s", text + 2 + n);
    prefix[0] = 0;
    for (int i = 1; i <= 2 * n + 1; ++ i) {
        prefix[i] = prefix[i - 1] * MAGIC + text[i];
    }
    suffix[2 * n + 2] = 0;
    for (int i = 2 * n + 1; i >= 1; -- i) {
        suffix[i] = suffix[i + 1] * MAGIC + text[i];
    }
    int maximum = 0;
    int best_i, best_j, best_k;
    for (int i = 1; i <= 2 * n + 1; ++ i) {
        if (i == n + 1) {
            continue;
        }
        int length = get_lcp(i, i);
        int extra = i <= n ? get_lcp(i - length, i + length + n) : get_lcp(i - length - n, i + length);
        if (2 * (length + extra) - 1 > maximum) {
            maximum = 2 * (length + extra) - 1;
            if (i <= n) {
                best_i = i - length - extra + 1;
                best_j = i + length - 1;
                best_k = i + length + extra - 2;
            } else {
                int ii = i - n - 1;
                best_i = ii - length - extra + 2;
                best_j = ii - length + 1;
                best_k = ii + length + extra - 1;
            }
        }
        //if (i == n || i == 2 * n + 1) {
        //    continue;
        //}
        length = get_lcp(i, i + 1);
        extra = i <= n ? get_lcp(i - length, i + 1 + length + n) : get_lcp(i - length - n, i + 1 + length);
        if (2 * (length + extra) > maximum) {
            maximum = 2 * (length + extra);
            if (i <= n) {
                best_i = i - length - extra + 1;
                best_j = i + length;
                best_k = i + length + extra - 1;
            } else {
                int ii = i - n - 1;
                best_i = ii - length - extra + 2;
                best_j = ii - length + 1;
                best_k = ii + length + extra;
            }
        }
    }
    printf("%d\n", maximum);
    for (int i = 1; i <= n; ++ i) {
        putchar(best_i <= i && i <= best_j ? text[i] : '.');
    }
    puts("");
    for (int i = 1; i <= n; ++ i) {
        putchar(best_j <= i && i <= best_k ? text[n + 1 + i] : '.');
    }
    puts("");
    return 0;
}
