#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 300000 << 1;
const int MAGIC = 3;

typedef unsigned long long ULL;

int n, a[N], b[N], pos[N], str[N];
ULL hash[N], power[N];

ULL get_hash(int i, int j) {
    return hash[i] - hash[j] * power[j - i];
}

bool compare(int i, int j) {
    int low = 0;
    int high = n;
    while (low < high) {
        int middle = low + high + 1 >> 1;
        if (i + middle <= n + 1 && j + middle <= n + 1 && get_hash(i, i + middle) == get_hash(j, j + middle)) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return str[i + low] < str[j + low];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
        pos[a[i]] = i;
    }
    memset(str, 0, sizeof(str));
    for (int len = n; len >= 1; -- len) {
        if (pos[len] != n - len + 1) {
            for (int i = pos[len]; i <= n; ++ i) {
                str[a[i]] = 1;
            }
            break;
        }
    }
    str[n + 1] = -1;
    power[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        power[i] = power[i - 1] * MAGIC;
    }
    hash[n + 1] = 0;
    for (int i = n; i >= 1; -- i) {
        hash[i] = hash[i + 1] * MAGIC + str[i];
    }
    for (int i = 2; i <= n; ++ i) {
        if (!compare(a[i - 1], a[i])) {
            puts("Error");
            return 0;
        }
    }
    for (int i = 1; i <= n; ++ i) {
        printf("%d", str[i]);
    }
    puts("");
    return 0;
}
