#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()

const int MOD = (int)1e9 + 9;

const int N = 100;
const int M = 50000;

int n, m, a[N], b[N], c[N], x[M], y[M];

bool visit[N];

bool para(int i, int j) {
    return (long long)a[i] * b[j] == (long long)a[j] * b[i];
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d%d", a + i, b + i, c + i);
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", x + i, y + i);
        }
        memset(visit, 0, sizeof(visit));
        std::vector <int> groups;
        for (int i = 0; i < n; ++ i) {
            if (!visit[i]) {
                int size = 0;
                for (int j = 0; j < n; ++ j) {
                    if (para(i, j)) {
                        size ++;
                        visit[j] = true;
                    }
                }
                groups.push_back(size);
            }
        }
        int total = 1;
        for (int i = 0; i < SIZE(groups); ++ i) {
            total += groups[i];
            for (int j = 0; j < i; ++ j) {
                total += groups[i] * groups[j];
            }
        }
        std::vector <int> masks;
        for (int i = 0; i < m; ++ i) {
            int mask = 0;
            for (int j = 0; j < n; ++ j) {
                mask = (mask * 2 + ((long long)a[j] * x[i] + (long long)b[j] * y[i] + c[j] > 0)) % MOD;
            }
            masks.push_back(mask);
        }
        std::sort(ALL(masks));
        masks.erase(std::unique(ALL(masks)), masks.end());
        puts(SIZE(masks) == total ? "PROTECTED" : "VULNERABLE");
    }
    return 0;
}
