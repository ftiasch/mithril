#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; ++ i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

const int N = 150;

int primeID[N], mask[N];
long long result[N + 1];
vector <int> primes;
map <int, long long> ways[N + 1][N + 1];

int main() {
    for (int i = 2; i * 2 <= N; ++ i) {
        if (isPrime(i)) {
            primeID[i] = primes.size();
            primes.push_back(i);
        }
    }
    for (int i = 1; i <= N; ++ i) {
        mask[i] = 0;
        for (int j = 0; j < (int)primes.size(); ++ j) {
            if (i % primes[j] == 0) {
                mask[i] |= 1 << j;
            }
        }
    }
    //printf("%d\n", primes.size());
    ways[N][N][0] = 1;
    memset(result, 0, sizeof(result));
    for (int i = N; i >= 0; -- i) {
        for (int j = N; j >= 0; -- j) {
            for (map <int, long long> :: iterator iter = ways[i][j].begin(); iter != ways[i][j].end(); ++ iter) {
                if (j == 0) {
                    result[N - i] += iter->second;
                } else {
                    ways[i][j - 1][iter->first] += iter->second;
                    if (i >= j && !(iter->first & mask[j])) {
                        ways[i - j][j][iter->first | mask[j]] += iter->second;
                    }
                }
            }
        }
    }
    int n;
    scanf("%d", &n);
    cout << result[n] << endl;
    return 0;
}
