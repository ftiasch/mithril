#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

int n, x;

int myLog(int n) {
    int k = 0;
    while (1 << k + 1 <= n) {
        k ++;
    }
    return k;
}

const int N = 100000;
const int INF = 1000000000;

int need[N + 1], answer[N + 1];

int main() {
    freopen("complexity.in", "r", stdin);
    freopen("complexity.out", "w", stdout);
    scanf("%d%d", &n, &x);
    vector <int> factors(1, n);
    while (factors.back() > 1) {
        factors.push_back(myLog(factors.back()));
    }
    for (int i = 1; i <= x; ++ i) {
        need[i] = INF;
    }
    queue <int> q;
    for (int i = 0; i < (int)factors.size(); ++ i) {
        q.push(factors[i]);
        need[factors[i]] = 1;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)factors.size(); ++ i) {
            if ((long long)u * factors[i] <= x && need[u * factors[i]] == INF) {
                need[u * factors[i]] = need[u] + 1;
                q.push(u * factors[i]);
            }
        }
    }
    vector <int> terms;
    for (int i = 1; i <= x; ++ i) {
        if (need[i] != INF) {
            terms.push_back(i);
        }
    }
    answer[0] = 0;
    for (int i = 1; i <= x; ++ i) {
        answer[i] = INF;
        for (vector <int> :: iterator iter = terms.begin(); iter != terms.end(); ++ iter) {
            if (*iter <= i) {
                answer[i] = min(answer[i], answer[i - *iter] + need[*iter]);
            }
        }
    }
    printf("%d\n", answer[x]);
    return 0;
}
