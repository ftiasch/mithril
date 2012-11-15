#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000;
const int K = 50;

const int MOD = 1000000000 + 7;

int factorial[N + 1];

int inverse(int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

int invFacSqr[N + 1];


int ways[K + 1][N + 1];
int sum[N + 1];

int main() {
    factorial[0] = 1;
    for (int i = 1; i <= N; ++ i) {
        factorial[i] = (long long)factorial[i - 1] * i % MOD;
    }
    for (int i = 0; i <= N; ++ i) {
        int ret = inverse(factorial[i]);
        invFacSqr[i] = (long long)ret * ret % MOD;
    }
    memset(ways, 0, sizeof(ways));
    ways[0][0] = 1;
    for (int k = 1; k <= K; ++ k) {
        for (int i = 0; i <= N; ++ i) {
            sum[i] = ((i ? sum[i - 1] : 0) + (long long)ways[k - 1][i] * invFacSqr[i]) % MOD;
        }
        for (int i = 2; i <= N; ++ i) {
            ways[k][i] = (long long)sum[i - 2] * factorial[i] % MOD * factorial[i - 1] % MOD * inverse(2) % MOD;
        }
    }
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("Case %d: %d", t, ways[k][n]);
        cout << endl;
    }
    return 0;
}
