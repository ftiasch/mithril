#include <cstdio>
#include <cstring>
using namespace std;

const int N = 300;

int n, x[N], y[N], count[N][N], sameX[N];

void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

bool checkBelow(int k, int i, int j) {
    if (x[i] == x[j]) {
        return false;
    }
    if ((x[k] - x[i]) * (x[k] - x[j]) > 0) {
        return false;
    }
    if (x[i] > x[j]) {
        swap(i, j);
    }
    return (y[j] - y[i]) * (x[k] - x[i]) >= (y[k] - y[i]) * (x[j] - x[i]);
}

int sign(int i, int j) {
    if (x[i] == x[j]) {
        return 0;
    }
    return x[i] < x[j]? 1: -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", x + i, y + i);
    }
    memset(sameX, 0, sizeof(sameX));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j && x[i] == x[j] && y[j] < y[i]) {
                sameX[i] ++;
            }
        }
    }
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j) {
                for (int k = 0; k < n; ++ k) {
                    if (k != i && k != j && checkBelow(k, i, j)) {
                        count[i][j] ++;
                    }
                }
                count[i][j] *= sign(i, j);
            }
        }
    }
//for (int i = 0; i < n; ++ i) {
//    for (int j = 0; j < n; ++ j) {
//        printf("%d -> %d: %d\n", i, j, count[i][j]);
//    }
//}
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j) {
                for (int k = 0; k < n; ++ k) {
                    if (i != k && j != k) {
                        int area = count[i][j] + count[j][k] + count[k][i];
                        if (checkBelow(k, i, j)) {
                            area -= sign(i, j);
                        }
                        if (checkBelow(i, j, k)) {
                            area -= sign(j, k);
                        }
                        if (checkBelow(j, k, i)) {
                            area -= sign(k, i);
                        }
                        if (sign(i, j) == sign(j, k)) {
                            area -= sameX[j] * sign(i, j);
                        }
                        if (sign(j, k) == sign(k, i)) {
                            area -= sameX[k] * sign(j, k);
                        }
                        if (sign(k, i) == sign(i, j)) {
                            area -= sameX[i] * sign(k, i);
                        }
//printf("%d -> %d -> %d: %d\n", i, j, k, area);
                        if (area == 0) {
                            result ++;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", result / 6);
//printf("-- %d\n", result % 6);
    return 0;
}
