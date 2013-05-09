#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 500;
const int M = 500 * 500;

int n, a[N], order[N];
bool can[N + 1][M + 1], mark[N];

bool by_a(int i, int j) {
    return a[i] < a[j];
}

int main() {
    freopen("equal-power.in", "r", stdin);
    freopen("equal-power.out", "w", stdout);
    scanf("%d", &n);
    int total = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        total += a[i];
        order[i] = i;
    }
    std::sort(order, order + n, by_a);
    memset(can, 0, sizeof(can));
    can[0][0] = true;
    for (int i = 0; i < n - 1; ++ i) {
        for (int j = 0; j <= M; ++ j) {
            if (can[i][j] && j + 2 * a[order[i]] == (total - j - a[order[i]]) + a[order[n - 1]]) {
                printf("%d\n", j + 2 * a[order[i]]);
                vector <int> choices;
                choices.push_back(order[i]);
                for (; i; -- i) {
                    if (!can[i - 1][j]) {
                        choices.push_back(order[i - 1]);
                        j -= a[order[i - 1]];
                    }
                }
                memset(mark, 0, sizeof(mark));
                printf("%d\n", (int)choices.size());
                for (int i = 0; i < (int)choices.size(); ++ i) {
                    mark[choices[i]] = true;
                    printf("%d%c", choices[i] + 1, " \n"[i == (int)choices.size() - 1]);
                }
                printf("%d\n", n - (int)choices.size());
                choices.clear();
                for (int i = 0; i < n; ++ i) {
                    if (!mark[i]) {
                        choices.push_back(i);
                    }
                }
                for (int i = 0; i < (int)choices.size(); ++ i) {
                    printf("%d%c", choices[i] + 1, " \n"[i == (int)choices.size() - 1]);
                }
                return 0;
            }
        }
        for (int j = 0; j <= M; ++ j) {
            if (can[i][j]) {
                can[i + 1][j] = true;
                if (j + a[order[i]] <= M) {
                    can[i + 1][j + a[order[i]]] = true;
                }
            }
        }
    }
    puts("-1");
    return 0;
}
