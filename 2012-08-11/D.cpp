#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 333;
const int MAGIC = 3;

typedef unsigned long long Hash;

int n, m, matrix[N][N];
char buffer[N];
Hash power[N * N], rowHash[N][N], allHash[N][N], preHash[N][N];

bool check(int l) {
    if (l > n || l > m) {
        return false;
    }
    for (int j = 1; j <= m; ++ j) {
        allHash[0][j] = 0;
    }
    for (int i = 1; i <= n; ++ i) {
        rowHash[i][0] = 0;
        for (int j = 1; j <= m; ++ j) {
            rowHash[i][j] = rowHash[i][j - 1] * MAGIC + matrix[i][j];
            if (j > l) {
                rowHash[i][j] -= matrix[i][j - l] * power[l];
            }
        }
        for (int j = l; j <= m; ++ j) {
            allHash[i][j] = allHash[i - 1][j] * power[l] + rowHash[i][j];
            if (i > l) {
                allHash[i][j] -= rowHash[i - l][j] * power[l * l];
            }
        }
    }
    for (int i = l; i <= n; ++ i) {
        for (int j = l; j <= m; ++ j) {
            preHash[i][j] = allHash[i][j];
        }
    }
    for (int j = 1; j <= m; ++ j) {
        allHash[n + 1][j] = 0;
    }
    for (int i = n; i >= 1; -- i) {
        rowHash[i][m + 1] = 0;
        for (int j = m; j >= 1; -- j) {
            rowHash[i][j] = rowHash[i][j + 1] * MAGIC + matrix[i][j];
            if (j + l <= m) {
                rowHash[i][j] -= matrix[i][j + l] * power[l];
            }
        }
        for (int j = m - l + 1; j >= 1; -- j) {
            allHash[i][j] = allHash[i + 1][j] * power[l] + rowHash[i][j];
            if (i + l <= n) {
                allHash[i][j] -= rowHash[i + l][j] * power[l * l];
            }
            if (i + l - 1 <= n && allHash[i][j] == preHash[i + l - 1][j + l - 1]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", buffer + 1);
        for (int j = 1; j <= m; ++ j) {
            matrix[i][j] = buffer[j] - '0';
        }
    }
    power[0] = 1;
    for (int i = 1; i <= n * m; ++ i) {
        power[i] = power[i - 1] * MAGIC;
    }
    int low, high;
    low = 0, high = min(n, m);
    while (low < high) {
        int middle = (low + high + 1) >> 1;
        if (check(middle * 2)) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    int result = 2 * low;
    low = 0, high = min(n, m);
    while (low < high) {
        int middle = (low + high + 1) >> 1;
        if (check(middle * 2 + 1)) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    result = max(result, 2 * low + 1);
    printf("%d\n", result == 1? -1: result);
    return 0;
}
