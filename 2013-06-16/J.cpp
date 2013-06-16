#include <cstdio>
#include <cstring>
#include <utility>
#include <climits>
#include <vector>
#include <algorithm>

const int M = 1000000;
const int INF = 1000000000;

std::vector <std::pair <int, int> > widgets;
char minimum[324][M + 1];

void update(char &x, char a) {
    x = std::min(x, a);
}

int main() {
    for (int i = 2, sum = 1; sum + i * i <= M; ++ i) {
        sum += i * i;
        widgets.push_back(std::make_pair(sum, M + i));
    }
    for (int i = 3, sum = 1; sum + i * i <= M; i += 2) {
        sum += i * i;
        widgets.push_back(std::make_pair(sum, i));
    }
    for (int i = 4, sum = 4; sum + i * i <= M; i += 2) {
        sum += i * i;
        widgets.push_back(std::make_pair(sum, i));
    }
    std::sort(widgets.begin(), widgets.end());
    int n = widgets.size();
    for (int i = 0; i <= n; ++ i) {
        std::fill(minimum[i], minimum[i] + M + 1, 100);
    }
    minimum[0][0] = 0;
    for (int i = 0; i < n; ++ i) {
        int w = widgets[i].first;
        for (int j = 0; j <= M; ++ j) {
            update(minimum[i + 1][j], minimum[i][j]);
            if (j + w <= M) {
                update(minimum[i + 1][j + w], minimum[i][j] + 1);
            }
        }
    }
    int m;
    int test_count = 0;
    while (scanf("%d", &m) == 1 && m) {
        printf("Case %d:", ++ test_count);
        if (minimum[n][m] == 100) {
            puts(" impossible");
        } else {
            for (int i = n, j = m; i; -- i) {
                int w = widgets[i - 1].first;
                if (j >= w && minimum[i - 1][j - w] + 1 == minimum[i][j]) {
                    printf(" %d%c", widgets[i - 1].second % M, widgets[i - 1].second >= M ? 'H' : 'L');
                    j -= w;
                }
            }
            puts("");
        }
    }
    return 0;
}
