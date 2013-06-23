#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <iostream>
#include <algorithm>

const int N = 100000;

int n, p[N << 1];
char string[N + 1];

void manacher() {
    for (int i = 0; i < n; ++ i) {
        printf("%4c%4c", string[i], ' ');
    }
    puts("");
    for (int i = 0; i <= n - 1 << 1; ++ i) {
        printf("%4d", p[i]);
    }
    puts("");
}

typedef long long LL;

const LL MAGIC1 = 137;
const LL MAGIC2 = 179;


const int MOD1 = (int)1e9 + 7;
const int MOD2 = (int)1e9 + 9;

LL sum[N + 1];
LL hash1[N + 1], power1[N + 1], hash2[N + 1], power2[N + 1];

std::pair <LL, LL> get_hash(int l, int r) {
    int a = r - l;
    return std::make_pair(((hash1[l] - power1[a] * hash1[r]) % MOD1 + MOD1) % MOD1,
                          ((hash2[l] - power2[a] * hash2[r]) % MOD2 + MOD2) % MOD2);
}

int main() {
//freopen("J.in", "r", stdin);
    scanf("%s", string);
    n = strlen(string);
    hash1[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        hash1[i] = (hash1[i + 1] * MAGIC1 + string[i]) % MOD1;
    }
    hash2[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        hash2[i] = (hash2[i + 1] * MAGIC2 + string[i]) % MOD2;
    }
    power1[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        power1[i] = (power1[i - 1] * MAGIC1) % MOD1;
    }
    power2[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        power2[i] = (power2[i - 1] * MAGIC2) % MOD2;
    }
    sum[0] ++;
    p[0] = 1;
    std::set <std::pair <LL, LL> > set;
    set.insert(get_hash(0, 1));
    for (int i = 1, j = 0; i <= n - 1 << 1; ++ i) {
        int rightmost = (j + 1 >> 1) + p[j] - 1;
        int l = i >> 1;
        int r = i + 1 >> 1;
        p[i] = rightmost < r ? 0 : std::min(p[(j << 1) - i], rightmost - r + 1);
        while (l - p[i] >= 0 && r + p[i] < n && string[l - p[i]] == string[r + p[i]]) {
            p[i] ++;
            std::pair <LL, LL> h = get_hash(l - p[i] + 1, r + p[i]);
            if (!set.count(h)) {
                set.insert(h);
                sum[r + p[i] - 1] ++;
            }
        }
        if ((i + 1 >> 1) + p[i] - 1 > rightmost) {
            j = i;
        }
    }
    LL partial = 0;
    for (int i = 0; i < n; ++ i) {
        partial += sum[i];
        std::cout << partial << " \n"[i == n - 1];
    }
    return 0;
}
