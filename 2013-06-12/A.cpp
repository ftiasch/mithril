#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 100000000;

int n, t, m, sum[91];

struct Result {
    int a, b;

    Result() : a(-INF), b(INF) {}

    Result(int a, int b) : a(a), b(b) {
    }

    Result &operator +=(int v) {
        if (v > 0) {
            a += v;
        }
        if (v < 0) {
            b -= v;
        }
        return *this;
    }

    int difference() const {
        return a - b;
    }
};

Result operator +(Result r, int v) {
    return r += v;
}

bool operator < (const Result &x, const Result &y) {
    if (x.difference() != y.difference()) {
        return x.difference() < y.difference();
    }
    return x.a < y.a;
}

Result maximum[2][1801][9];

void update(Result &x, Result a) {
    x = std::max(x, a);
}

int main() {
    scanf("%d%d%d", &n, &t, &m);
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        sum[a] ++;
        sum[b] --;
    }
    for (int i = 1; i <= 90; ++ i) {
        sum[i] += sum[i - 1];
    }
    maximum[0][0][4] = Result(0, 0);
    for (int i = 0; i < 90; ++ i) {
        for (int j = 0; j <= n * t; ++ j) {
            for (int k = 0; k < 9; ++ k) {
                maximum[i + 1 & 1][j][k] = Result();
            }
        }
        int cheer = sum[i];
        for (int j = 0; j <= n * t; ++ j) {
            for (int k = 0; k < 9; ++ k) {
                int new_k = i == 45 ? 4 : k;
                if (cheer > 0) {
                    // lose
                    int kk = std::min(new_k, 4) - 1;
                    if (kk >= 0) {
                        update(maximum[i + 1 & 1][j][kk], maximum[i & 1][j][k]);
                    } else {
                        update(maximum[i + 1 & 1][j][4], maximum[i & 1][j][k] + (-1));
                    }
                }
                // draw
                if (cheer <= n && j + cheer <= n * t) {
                    update(maximum[i + 1 & 1][j + cheer][4], maximum[i & 1][j][k]);
                }
                if (cheer < n && j + cheer + 1 <= n * t) {
                    // win
                    int kk = std::max(new_k, 4) + 1;
                    if (kk < 9) {
                        update(maximum[i + 1 & 1][j + cheer + 1][kk], maximum[i & 1][j][k]);
                    } else {
                        update(maximum[i + 1 & 1][j + cheer + 1][4], maximum[i & 1][j][k] + 1);
                    }
                }
            }
        }
    }
    Result answer;
    for (int i = 0; i <= n * t; ++ i) {
        for (int j = 0; j < 9; ++ j) {
            update(answer, maximum[0][i][j]);
        }
    }
    printf("%d %d\n", answer.a, answer.b);
    return 0;
}
