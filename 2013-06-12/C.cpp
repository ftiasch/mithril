#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int MOD = 1000003;
const int N = 1000;

int n, m, factorial[N + 1];
char switches[N][N + 1], lights[N][N + 1];

std::map <std::string, int> size, diff;

int main() {
    factorial[0] = 1;
    for (int i = 1; i <= N; ++ i) {
        factorial[i] = (long long)factorial[i - 1] * i % MOD;
    }
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%s%s", switches[i], lights[i]);
    }
    for (int i = 0; i < n; ++ i) {
        std::string s;
        for (int j = 0; j < m; ++ j) {
            s += switches[j][i];
        }
        size[s] ++;
        diff[s] ++;
    }
    for (int i = 0; i < n; ++ i) {
        std::string s;
        for (int j = 0; j < m; ++ j) {
            s += lights[j][i];
        }
        diff[s] --;
    }
    int answer = 1;
    foreach (iter, size) {
        answer = (long long)answer * factorial[iter->second] % MOD;
    }
    foreach (iter, diff) {
        if (iter->second != 0) {
            answer = 0;
        }
    }
    printf("%d\n", answer);
    return 0;
}
