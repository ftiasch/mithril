#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1000;

int n, p, powSum[N], symSum[N], coefficient[N], backup[N];

int inverse(int a, int p) {
    return a == 1? 1: (p - p / a) * inverse(p % a, p) % p;
}

int evaluate(int x) {
    int result = 0;
    for (int i = n; i >= 0; -- i) {
        result = (result * x + coefficient[i]) % p;
    }
    return result;
}

int main() {
    freopen("system.in", "r", stdin);
    freopen("system.out", "w", stdout);
    scanf("%d%d", &n, &p);
    powSum[0] = n;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", powSum + i);
    }
    symSum[0] = 1;
    for (int k = 1; k <= n; ++ k) {
        symSum[k] = 0;
        for (int i = 1, sign = 1; i <= k; ++ i, sign = p - sign) {
            symSum[k] = (symSum[k] + sign * symSum[k - i] % p * powSum[i]) % p;
        }
        symSum[k] = (symSum[k] * inverse(k, p)) % p;
    }
    coefficient[n] = 1;
    for (int i = 1, sign = p - 1; i <= n; ++ i, sign = p - sign) {
        coefficient[n - i] = sign * symSum[i] % p;
    }
    vector <int> roots;
    for (int x = 0; x < p; ++ x) {
        while (evaluate(x) == 0) {
            roots.push_back(x);
            for (int i = 0; i <= n; ++ i) {
                backup[i] = coefficient[i];
            }
            n --;
            for (int i = n; i >= 0; -- i) {
                coefficient[i] = backup[i + 1];
                backup[i] = (backup[i] + coefficient[i] * x % p) % p;
            }
        }
    }
    if (n) {
        puts("NO");
    } else {
        puts("YES");
        for (int i = 0; i < (int)roots.size(); ++ i) {
            printf("%d%c", roots[i], i == (int)roots.size() - 1? '\n': ' ');
        }
    }
    return 0;
}
