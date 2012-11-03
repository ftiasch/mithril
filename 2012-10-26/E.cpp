#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int L = 10000 + 2;

int length;
char exp[L];

int n;
int varCnt, varID[26];

const int N = 8;

char varName[N];

int getVarID(char var) {
    if (varID[var - 'a'] == -1) {
        varName[varID[var - 'a'] = varCnt ++] = var;
    }
    return varID[var - 'a'];
}

double constant, linear[N], quadratic[N][N];

double coefficient[N][N + 1], solution[N];

const double EPS = 1e-9;
const double INF = 1e100;

int sign(double x) {
    return x < -EPS ? -1 : x > EPS;
}

double value[N];

double evaluate() {
    double result = constant;
    for (int i = 0; i < n; ++ i) {
        result += value[i] * linear[i];
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = i; j < n; ++ j) {
            result += value[i] * value[j] * quadratic[i][j];
        }
    }
    return result;
}

double best, bestSolution[N];


int main() {
    exp[0] = '+';
    scanf("%s", exp + 1);
    length = strlen(exp);

    n = 0;
    memset(varID, -1, sizeof(varID));

    constant = 0;
    memset(linear, 0, sizeof(linear));
    memset(quadratic, 0, sizeof(quadratic));

    for (int end = length - 1; end > 0; -- end) {
        int begin = end;
        while (exp[begin] != '+' && exp[begin] != '-') {
            begin --;
        }
        int start = begin + 1;
        while (start <= end && !isalpha(exp[start])) {
            start ++;
        }
        double *memory = NULL;
        if (start > end) {
            memory = &constant;
        } else {
            int length = end - start + 1;
            if (length == 1) {
                memory = linear + getVarID(exp[start]);
            } else if (length == 2) {
                int i = getVarID(exp[start]);
                int j = getVarID(exp[start + 1]);
                if (i > j) {
                    swap(i, j);
                }
                memory = &quadratic[i][j];
            } else {
                int i = getVarID(exp[start]);
                memory = &quadratic[i][i];
            }
        }
        exp[start] = '\0';
        double coef = 1;
        if (begin + 1 < start) {
            sscanf(exp + begin + 1, "%lf", &coef);
        }
        if (exp[begin] == '-') {
            coef *= -1;
        }
        *memory += coef;
        end = begin;
    }

    n = varCnt;
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            quadratic[j][i] = quadratic[i][j];
        }
    }

    best = -INF;
    for (int mask = 0; mask < 1 << n; ++ mask) {
        int valueMask = mask;
        while (true) {
            memset(coefficient, 0, sizeof(coefficient));
            for (int i = 0; i < n; ++ i) {
                if (mask >> i & 1) {
                    coefficient[i][i] = 1;
                    coefficient[i][n] = -(valueMask >> i & 1);
                } else {
                    coefficient[i][n] += linear[i];
                    for (int j = 0; j < n; ++ j) {
                        if (i == j) {
                            coefficient[i][j] += 2 * quadratic[j][j];
                        } else {
                            coefficient[i][j] += quadratic[i][j];
                        }
                    }
                }
            }

            int rank = 0;
            for (int i = 0; i < n; ++ i) {
                int j = rank;
                while (j < n && sign(coefficient[j][i]) == 0) {
                    j ++;
                }
                if (j == n) {
                    continue;
                }
                for (int k = 0; k <= n; ++ k) {
                    swap(coefficient[rank][k], coefficient[j][k]);
                }
                for (int j = 0; j < n; ++ j) {
                    if (rank != j && sign(coefficient[j][i]) != 0) {
                        double times = coefficient[j][i] / coefficient[rank][i];
                        for (int k = 0; k <= n; ++ k) {
                            coefficient[j][k] -= coefficient[rank][k] * times;
                        }
                    }
                }
                rank ++;
            }

            bool valid = true;
            for (int i = rank; i < n; ++ i) {
                for (int j = 0; j <= n; ++ j) {
                    valid &= sign(coefficient[i][j]) == 0;
                }
            }

            if (valid) {
                memset(solution, 0, sizeof(solution));
                for (int i = 0; i < rank; ++ i) {
                    int j = 0;
                    while (sign(coefficient[i][j]) == 0) {
                        j ++;
                    }
                    solution[j] = -coefficient[i][n] / coefficient[i][j];
                }
                for (int i = 0; i < n; ++ i) {
                    value[i] = solution[i];
                    valid &= sign(value[i] - 0) >= 0 && sign(value[i] - 1) <= 0;
                }
                if (valid) {
                    double ret = evaluate();
                    if (ret > best) {
                        best = ret;
                        for (int i = 0; i < n; ++ i) {
                            bestSolution[i] = value[i];
                        }
                    }
                }
            }

            if (valueMask == 0) {
                break;
            }
            valueMask = (valueMask - 1) & mask;
        }
    }

    printf("%.8f\n", best);
    for (int i = 0; i < n; ++ i) {
        printf("%c=%.8f\n", varName[i], bestSolution[i]);
    }
    return 0;
}
