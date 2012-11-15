#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 16;

int A, B, C, D;

bool valid[N][N][N][N][5][5];
double expected[N][N][N][N][5][5];

int total[4], maxA, maxB, maxC, maxD;

double min4(double a, double b, double c, double d) {
    return min(min(a, b), min(c, d));
}

double solve(int a, int b, int c, int d, int e, int f) {
    if (e == 0) {
        a ++;
    }
    if (e == 1) {
        b ++;
    }
    if (e == 2) {
        c ++;
    }
    if (e == 3) {
        d ++;
    }
    if (f == 0) {
        a ++;
    }
    if (f == 1) {
        b ++;
    }
    if (f == 2) {
        c ++;
    }
    if (f == 3) {
        d ++;
    }
    if (a >= A && b >= B && c >= C && d >= D) {
        return 0.0;
    }
    if (e == 0) {
        a --;
    }
    if (e == 1) {
        b --;
    }
    if (e == 2) {
        c --;
    }
    if (e == 3) {
        d --;
    }
    if (f == 0) {
        a --;
    }
    if (f == 1) {
        b --;
    }
    if (f == 2) {
        c --;
    }
    if (f == 3) {
        d --;
    }
    if (!valid[a][b][c][d][e][f]) {
        valid[a][b][c][d][e][f] = true;
        double &ret = expected[a][b][c][d][e][f];
        ret = 0;
        int left = maxA - a + maxB - b + maxC - c + maxD - d + (e == 4) + (f == 4);
        if (left==0){
            return 1e100;
        }
        if (a < maxA) {
            ret += (solve(a + 1, b, c, d, e, f) + 1) * (maxA - a) / left;
        }
        if (b < maxB) {
            ret += (solve(a, b + 1, c, d, e, f) + 1) * (maxB - b) / left;
        }
        if (c < maxC) {
            ret += (solve(a, b, c + 1, d, e, f) + 1) * (maxC - c) / left;
        }
        if (d < maxD) {
            ret += (solve(a, b, c, d + 1, e, f) + 1) * (maxD - d) / left;
        }
        if (e == 4) {
            ret += (min4(solve(a, b, c, d, 0, f), 
                         solve(a, b, c, d, 1, f),
                         solve(a, b, c, d, 2, f),
                         solve(a, b, c, d, 3, f)) + 1) * 2 / left;
        } else if (f == 4) {
            ret += (min4(solve(a, b, c, d, e, 0), 
                         solve(a, b, c, d, e, 1),
                         solve(a, b, c, d, e, 2),
                         solve(a, b, c, d, e, 3)) + 1) * 1 / left;
        }
    }
    return expected[a][b][c][d][e][f];
}

int main() {
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        scanf("%d%d%d%d", &A, &B, &C, &D);
        bool found = false;
        for (int x = 0; x < 4; ++ x) {
            for (int y = 0; y < 4; ++ y) {
                total[0] = total[1] = total[2] = total[3] = 13, total[x] ++, total[y] ++;
                maxA = total[0], maxB = total[1], maxC = total[2], maxD = total[3];
                if (maxA >= A && maxB >= B && maxC >= C && maxD >= D) {
                    found = true;
                }
            }
        }
        maxA = maxB = maxC = maxD = 13;
        double result;
        if (found) {
            memset(valid, 0, sizeof(valid));
            result = solve(0, 0, 0, 0, 4, 4);
        } else {
            result = -1.0;
        }
        printf("Case %d: %.3f", t, result);
        cout << endl;
    }
    return 0;
}
