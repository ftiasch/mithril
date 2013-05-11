#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

const int N = 500;

int n, k, cross[N][N], suffix[N][N], count[N], maximum[N][N], pre[N][N];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            scanf("%d", &cross[i][j]);
        }
    }
    memset(count, 0, sizeof(count));
    for (int i = n - 1; i >= 0; -- i) {
        for (int j = 0; j < i; ++ j) {
            count[j] += cross[j][i];
        }
        suffix[n - 1][i] = count[n - 1];
        for (int j = n - 2; j >= 0; -- j) {
            suffix[j][i] = suffix[j + 1][i] + count[j];
        }
    }
    for (int i = 1; i <= k; ++ i) {
        for (int j = 0; j < n - 1; ++ j) {
            maximum[i][j] = i == 1 ? suffix[0][j + 1] - suffix[j + 1][j + 1] : INT_MIN;
        }
    }
    for (int i = 1; i + 1 <= k; ++ i) {
        for (int j = 0; j < n - 1; ++ j) {
            if (maximum[i][j] == INT_MIN) {
                continue;
            }
            for (int p = j + 1; p < n - 1; ++ p) {
                int tmp = maximum[i][j] + suffix[j + 1][p + 1] - suffix[p + 1][p + 1];
                if (tmp > maximum[i + 1][p]) {
                    maximum[i + 1][p] = tmp;
                    pre[i + 1][p] = j;
                }
            }
        }
    }
    int j = std::max_element(maximum[k], maximum[k] + (n - 1)) - maximum[k];
    printf("%d\n", maximum[k][j]);
    std::vector <int> ways;
    for (int i = k; i >= 1; -- i) {
        ways.push_back(j);
        j = pre[i][j];
    }
    for (int i = (int)ways.size() - 1; i >= 0; -- i) {
        printf("%d%c", ways[i] + 1, " \n"[i == 0]);
    }
    return 0;
}
