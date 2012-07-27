#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;

int signum(double x) { return x < -EPS? -1: x > EPS; }

const int N = 8;

int n, a[N][N];
double coefficient[N + 1][N + 2], solution[N + 1], result[N + 1];
bool hasSolution[1 << N + N], visit[1 << N + N];

double debug(double x) { return signum(fabs(x)) == 0? 0.0: x; }

int construct(int mask) {
    int equationCount = 0;
    for (int j = 0; j < n; ++ j) {
        if (mask >> j & 1) {
            for (int i = 0; i < n; ++ i) {
                coefficient[equationCount][i] = a[i][j];
            }
            coefficient[equationCount][n] = -1.0;
            coefficient[equationCount][n + 1] = 0.0;
            equationCount ++;
        }
    }
    for (int i = 0; i < n; ++ i) {
        coefficient[equationCount][i] = 1;
    }
    coefficient[equationCount][n] = 0.0;
    coefficient[equationCount][n + 1] = 1.0;
    equationCount ++;
    for (int i = 0; i < n; ++ i) {
        if (mask >> n + i & 1) {
            for (int k = 0; k < equationCount; ++ k) {
                coefficient[k][i] = 0.0;
            }
        }
    }
    return equationCount;
}

bool eliminate(int m, int n, bool need) {
    int pivotCount = 0;
    for (int j = 0; j < n; ++ j) {
        int p = pivotCount;
        while (p < m && signum(coefficient[p][j]) == 0) {
            p ++;
        }
        if (p == m) {
            continue;
        }
        for (int k = 0; k <= n; ++ k) {
            swap(coefficient[p][k], coefficient[pivotCount][k]);
        }
        for (int i = 0; i < m; ++ i) {
            if (i != pivotCount && signum(coefficient[i][j]) != 0) {
                double times = coefficient[i][j] / coefficient[pivotCount][j];
                for (int k = 0; k <= n; ++ k) {
                    coefficient[i][k] -= coefficient[pivotCount][k] * times;
                }
            }
        }
        pivotCount ++;
    }
    for (int i = pivotCount; i < m; ++ i) {
        if (signum(coefficient[i][n]) != 0) {
            return false;
        }
    }
    if (!need) {
        return true;
    }
    for (int j = 0; j < n; ++ j) {
        solution[j] = 0;
    }
    for (int i = 0; i < pivotCount; ++ i) {
        int j = 0;
        while (signum(coefficient[i][j]) == 0) {
            j ++;
        }
        solution[j] = coefficient[i][n] / coefficient[i][j];
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%d", &a[i][j]);
        }
    }
    memset(hasSolution, 0, sizeof(hasSolution));
    for (int mask = 0; mask < 1 << n + n; ++ mask) {
        int equationCount = construct(mask);
        hasSolution[mask] = eliminate(equationCount, n + 1, false);
    }
    memset(visit, 0, sizeof(visit));
    for (int mask = (1 << n + n) - 1; mask >= 0; -- mask) {
        if (hasSolution[mask] || visit[mask]) {
            for (int i = 0; i < n + n; ++ i) {
                if (mask >> i & 1) {
                    visit[mask ^ (1 << i)] = true;
                }
            }
        }
    }
    result[n] = -1e9;
    for (int mask = 0; mask < 1 << n + n; ++ mask) {
        if (hasSolution[mask] && !visit[mask]) {
            int equationCount = construct(mask);
            eliminate(equationCount, n + 1, true);
            bool valid = true;
            for (int k = 0; k < n; ++ k) {
                valid &= signum(solution[k]) >= 0;
            }
            for (int k = 0; k < n; ++ k) {
                double value = -solution[n];
                for (int i = 0; i < n; ++ i) {
                    value += solution[i] * a[i][k];
                }
                valid &= signum(value) >= 0;
            }
            if (valid && signum(solution[n] - result[n]) > 0) {
                for (int i = 0; i <= n; ++ i) {
                    result[i] = solution[i];
                }
            }
        }
    }
    printf("%.8f\n", debug(result[n]));
    for (int i = 0; i < n; ++ i) {
        printf("%.8f%c", debug(result[i]), i == n - 1? '\n': ' ');
    }
    return 0;
}
