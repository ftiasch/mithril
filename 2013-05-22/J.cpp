#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <iostream>
#include <algorithm>
 
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)
 
const int M = 1000000;
 
int n, m, next[M + 1], start[M];
char str[M + 1];
 
std::vector <int> events[M];
 
int main() {
    freopen("safe.in", "r", stdin);
    freopen("safe.out", "w", stdout);
    scanf("%d%d%s", &n, &m, str);
    memset(next, -1, sizeof(next));
    for (int i = 0; i + 1 < m; ++ i) {
        int j = i;
        while (j != -1) {
            j = next[j];
            if (str[j + 1] == str[i + 1]) {
                next[i + 1] = j + 1;
                break;
            }
        }
    }
    if (m % (m - 1 - next[m - 1]) == 0) {
        m = m - 1 - next[m - 1];
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &start[i]);
        events[start[i] %= m].push_back(i);
        if (start[i] > m / 2) {
            start[i] -= m;
        }
    }
    long long answer = 1000000000000000000LL;
    long long now = 0;
    long long delta = 0;
    for (int i = 0; i < n; ++ i) {
        now += std::abs(start[i]);
        if (start[i] < 0) {
            delta --;
        } else {
            delta ++;
        }
    }
    for (int d = 0; d < m; ++ d) {
        if (d) {
            now += delta;
            foreach (iter, events[(m / 2 + 1 + m - d) % m]) {
                if (m % 2 == 0) {
                    now -= 2;
                } else {
                    now -= 1;
                }
                delta -= 2;
            }
            foreach (iter, events[(m - d) % m]) {
                delta += 2;
            }
        }
        answer = std::min(answer, now);
    }
    std::cout << answer << std::endl;
    return 0;
}
