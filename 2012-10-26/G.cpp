#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

const int maxn = 4000;
const int maxm = maxn / 32 + 10;

typedef unsigned matrix[maxn][maxm];
typedef unsigned row[maxm];

int n, m;

void mul(row a, matrix b, row c)
{
    static bool bits[maxn];
    for (int i = 0; i < n; i++) {
        int cntbits = 0;
        for (int j = 0; j < m; j++) {
            cntbits += __builtin_parity(b[i][j] & c[j]);
        }
        bits[i] = cntbits & 1;
    }
    memset(a, 0, sizeof(row));
    for (int i = 0; i < m * 32; i++) {
        a[i / 32] = a[i / 32] << 1 | bits[i];
    }
}

void readMatrix(matrix a)
{
    static char buf[maxn * 2];
    memset(a, 0, sizeof(matrix));
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        static bool bits[maxn];
        int ptr = 0;
        for (int j = 0; buf[j]; j++) {
            int ch = isdigit(buf[j]) ? buf[j] - '0' : buf[j] - 'A' + 10;
            for (int k = 3; k >= 0; k--) {
                bits[ptr++] = ch >> k & 1;
            }
        }
        for (int j = 0; j < m * 32; j++) {
            a[i][j / 32] = a[i][j / 32] << 1 | bits[j];
        }
    }
}

void randomRow(row a)
{
    for (int i = 0; i < m; i++) {
        a[i] = rand() ^ rand() << 16;
    }
}

matrix a, b, c;
row r, r1, r2;

int main()
{
    scanf("%d", &n);
    m = (n + 31) / 32;
    readMatrix(a);
    readMatrix(b);
    readMatrix(c);
    for (int it = 0; it < 30; ++it) {
        randomRow(r);
        mul(r1, b, r);
        mul(r1, a, r1);
        mul(r2, c, r);
        for (int i = 0; i < m; i++) {
            if (r1[i] != r2[i]) {
                puts("NO");
                return 0;
            }
        }
    }
    puts("YES");
}
