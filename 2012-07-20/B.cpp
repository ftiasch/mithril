// Problem B -- Minimal Matrix
// Author: Bin Jin
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

const int maxn = 1 << 9;

char grid[maxn][maxn + 1];
unsigned grid32[maxn][maxn];
int n, N;

#define GRID(G, A, I, J) \
    (G[(A).first + (I) & N - 1][(A).second + (J) & N - 1])

int compareRow(pair<int,int> a, pair<int,int> b)
{
    int i = 0, j = 0;
    for (; j + 6 <= N; j += 6) {
        if (GRID(grid32, a, i, j) != GRID(grid32, b, i, j)) {
            return GRID(grid32, a, i, j) < GRID(grid32, b, i, j) ? -1 : 1;
        }
    }
    for (; j < N; j++) {
        if (GRID(grid, a, i, j) != GRID(grid, b, i, j)) {
            return GRID(grid, a, i, j) < GRID(grid, b, i, j) ? -1 : 1;
        }
    }
    return 0;
}

int compare(pair<int,int> a, pair<int,int> b)
{
    for (int i = 0; i < N; i++) {
        int j = 0;
        for (; j + 6 <= N; j += 6) {
            if (GRID(grid32, a, i, j) != GRID(grid32, b, i, j)) {
                return GRID(grid32, a, i, j) < GRID(grid32, b, i, j) ? -1 : 1;
            }
        }
        for (; j < N; j++) {
            if (GRID(grid, a, i, j) != GRID(grid, b, i, j)) {
                return GRID(grid, a, i, j) < GRID(grid, b, i, j) ? -1 : 1;
            }
        }
    }
    return 0;
}

int col;

inline int cmp(int a, int b)
{
    if (a < 0)
        return -1;
    if (b < 0)
        return 1;
    return compareRow(make_pair(a, col), make_pair(b, col));
}

int findMinCycle(const vector<int> &a)
{
    int i = 1, j = 2, k = 0, t = 0;
    do {
        k = 0;
        while (cmp(a[i + k], a[j + k]) == 0) k ++;
        if (cmp(a[i + k], a[j + k]) > 0) {
            i = i + k + 1;
        } else {
            j = j + k + 1;
        }
        if (i == j)
            j++;
        if (i > j)
            swap(i, j);
    } while (j <= N);
    return i;
}

int main()
{
    scanf("%s", grid[0]);
    N = strlen(grid[0]);
    n = 0;
    while ((1 << n) < N)
        n ++;
    for (int i = 1; i < N; i++) {
        scanf("%s", grid + i);
    }
    memset(grid32, 0, sizeof(grid32));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 6; k++) {
                grid32[i][j] = grid32[i][j] << 5;
                grid32[i][j] += grid[i][j + k & N - 1] - 'a';
            }
        }
    }
    pair<int,int> ans(0, 0);
    for (col = 0; col < N; col++) {
        vector<int> a(N * 2 + 1);
        for (int i = 1; i <= N; i++) {
            a[i] = a[i + N] = i - 1;
        }
        a.push_back(-1);
        int pos = findMinCycle(a);
        pair<int,int> ansNow(a[pos], col);
        if (compare(ans, ansNow) > 0) {
            ans = ansNow;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            putchar(GRID(grid, ans, i, j));
        }
        puts("");
    }
}
