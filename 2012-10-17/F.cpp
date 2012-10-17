#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 500;
const int MAGIC = 527;
const int MOD = 1000000000 + 7;

int n, a[N];
bool exists[N];
long long power[N];
unsigned long long power2[N];

int main() {
    freopen("numbereater.in", "r", stdin);
    freopen("numbereater.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        a[i] --;
    }
    power[0] = 1;
    for (int i = 1; i < N; ++ i) {
        power[i] = power[i - 1] * MAGIC % MOD;
    }
    power2[0] = 1;
    for (int i = 1; i < N; ++ i) {
        power2[i] = power2[i - 1] * MAGIC;
    }
    vector <pair <long long, unsigned long long> > hashes;
    for (int i = 0; i < n; ++ i) {
        memset(exists, 0, sizeof(exists));
        long long hash = 0;
        unsigned long long hash2 = 0;
        for (int j = i; j < n; ++ j) {
            if (!exists[a[j]]) {
                exists[a[j]] = true;
                hash = (hash + power[a[j]]) % MOD;
                hash2 += power2[a[j]];
            }
            hashes.push_back(make_pair(hash, hash2));
        }
    }
    sort(hashes.begin(), hashes.end());
    printf("%d\n", unique(hashes.begin(), hashes.end()) - hashes.begin());
    return 0;
}
