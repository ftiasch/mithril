#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5555;

typedef long long LL;
typedef unsigned long long ULL;

const ULL MAGIC = 127;
const LL MOD = 1000000007;

int text[N];
char buffer[N];
ULL prefix[N], suffix[N], power[N];
LL prefix2[N], suffix2[N], power2[N];

int main() {
    scanf("%s", buffer);
    int n = strlen(buffer);
    for (int i = 1; i <= n; ++ i) {
        text[i] = buffer[i - 1] - 'A' + 1;
    }
    power[0] = 1;
    power2[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        power[i] = power[i - 1] * MAGIC;
        power2[i] = (power2[i - 1] * MAGIC) % MOD;
    }
    prefix[0] = 0;
    prefix2[0] = 0;
    for (int i = 1; i <= n; ++ i) {
        prefix[i] = prefix[i - 1] * MAGIC + text[i];
        prefix2[i] = (prefix2[i - 1] * MAGIC + text[i]) % MOD;
    }
    suffix[n + 1] = 0;
    suffix2[n + 1] = 0;
    for (int i = n; i >= 1; -- i) {
        suffix[i] = suffix[i + 1] * MAGIC + text[i];
        suffix2[i] = (suffix2[i + 1] * MAGIC + text[i]) % MOD;
    }
    int result = 0;
    for (int l = 1; l <= n; ++ l) {
        vector <pair <ULL, LL> > hashes;
        for (int i = 1; i + l - 1 <= n; ++ i) {
            int j = i + l - 1;
            ULL hash = prefix[j] - prefix[i - 1] * power[l];
            LL hash2 = (prefix2[j] - prefix2[i - 1] * power2[l]) % MOD;
            if (hash2 < 0) {
                hash2 += MOD;
            }
            if (hash == suffix[i] - suffix[j + 1] * power[l]
                    && (hash2 + suffix2[j + 1] * power2[l]) % MOD == suffix2[i]) {
                hashes.push_back(make_pair(hash, hash2));
            }
        }
        sort(hashes.begin(), hashes.end());
        result += unique(hashes.begin(), hashes.end()) - hashes.begin();
    }
    printf("%d\n", result);
    return 0;
}
