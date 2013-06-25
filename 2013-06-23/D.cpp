#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;

const int N = 111;
const int M = 111111;

const int MAGIC = 137;
const int MOD = (int)1e9 + 9;

string words[2];
int power[M];

struct Hash {
    int n;
    string s;
    vector <int> hash;

    Hash() {}

    Hash(string s) {
        n = s.size();
        hash.resize(n + 1);
        hash[n] = 0;
        for (int i = n - 1; i >= 0; -- i) {
            hash[i] = ((long long)hash[i + 1] * MAGIC + s[i]) % MOD;
        }
    }

    int suffix(int k) {
        return hash[n - k];
    }

    int prefix(int k) {
        return (hash[0] + MOD - (long long)hash[k] * power[k] % MOD) % MOD;
    }
};

int n;
char buffer[M];
Hash hashes[2];

long long count[N], length[N];

int main() {
    power[0] = 1;
    for (int i = 1; i < M; ++ i) {
        power[i] = (long long)power[i - 1] * MAGIC % MOD;
    }
    words[0] = "0";
    words[1] = "1";
    for (int i = 2; i < 30; ++ i) {
        words[i & 1] = words[i + 1 & 1] + words[i & 1];
    }
    for (int t = 0; t < 2; ++ t) {
        hashes[t] = Hash(words[t]);
    }
    int test_count = 0;
    while (scanf("%d", &n) == 1) {
        scanf("%s", buffer);
        int m = strlen(buffer);
        Hash pattern(buffer);
        length[0] = length[1] = 1;
        length[2] = 2;
        count[0] = strcmp(buffer, "0") == 0;
        count[1] = strcmp(buffer, "1") == 0;
        count[2] = count[0] + count[1] + (strcmp(buffer, "10") == 0);
        std::cout << "Case " << (++ test_count) << ": ";
        if (n >= 3) {
            for (int i = 3; i <= n; ++ i) {
                count[i] = count[i - 1] + count[i - 2];
                length[i] = std::min(length[i - 1] + length[i - 2], (long long)M);
                for (int k = 1; k < m; ++ k) {
                    if (length[i - 1] >= k && length[i - 2] >= m - k) {
                        if (pattern.prefix(k) == hashes[i + 1& 1].suffix(k)) {
                            if (pattern.suffix(m - k) == hashes[i & 1].prefix(m - k)) {
                                count[i] ++;
                            }
                        }
                    }
                }
            }
        }
        std::cout << count[n] << std::endl;
    }
    return 0;
}
