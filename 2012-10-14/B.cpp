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

const int maxn = 512;

#define TRUE(a) ((a) << 1 | 1)
#define FALSE(a) ((a) << 1)

#define FOR(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)

int n;
int ma[maxn][maxn];

vector<int> adj[maxn * 4];
vector<int> rev[maxn * 4];

int N;

void imply(int a, int b)
{
    adj[a].push_back(b);
    rev[b].push_back(a);
}

void setTruth(int a)
{
    imply(a ^ 1, a);
}

void imply2(int a, int b)
{
    imply(a, b);
    imply(b, a);
}

int color[maxn * 4], colors;
vector<int> order;

void dfs1(int p)
{
    color[p] = 1;
    FOR (q, adj[p]) {
        if (!color[*q]) {
            dfs1(*q);
        }
    }
    order.push_back(p);
}

void dfs2(int p)
{
    color[p] = colors;
    FOR (q, rev[p]) {
        if (color[*q] < 0) {
            dfs2(*q);
        }
    }
}

int main()
{
    while (scanf("%d", &n) == 1) {
        int maxv = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &ma[i][j]);
                maxv = max(maxv, ma[i][j]);
            }
        }
        bool valid = true;
        for (int bits = 0; bits < 31 && valid && maxv; bits++) {
            N = n * 4;
            maxv >>= 1;
            for (int i = 0; i < N; i++) {
                adj[i].clear();
                rev[i].clear();
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    bool bit = ma[i][j] & 1;
                    ma[i][j] >>= 1;
                    if (i == j) {
                        if (bit) {
                            valid = false;
                        }
                    } else if (i & 1 && j & 1) {
                        // or
                        if (bit) {
                            imply(FALSE(j + n), TRUE(i));
                            imply(FALSE(i), TRUE(j + n));
                        } else {
                            setTruth(FALSE(i));
                            setTruth(FALSE(j + n));
                        }
                    } else if (~i & 1 && ~j & 1) {
                        // and
                        if (bit) {
                            setTruth(TRUE(i));
                            setTruth(TRUE(j + n));
                        } else {
                            imply(TRUE(j + n), FALSE(i));
                            imply(TRUE(i), FALSE(j + n));
                        }
                    } else {
                        // xor
                        if (bit) {
                            imply2(TRUE(i), FALSE(j + n));
                            imply2(FALSE(i), TRUE(j + n));
                        } else {
                            imply2(TRUE(i), TRUE(j + n));
                            imply2(FALSE(i), FALSE(j + n));
                        }
                    }
                }
            }
            if (!valid) {
                break;
            }
            memset(color, 0, sizeof(color));
            for (int i = 0; i < N; i++) {
                if (!color[i]) {
                    dfs1(i);
                }
            }
            reverse(order.begin(), order.end());
            memset(color, -1, sizeof(color));
            colors = 0;
            FOR (p, order) {
                if (color[*p] < 0) {
                    dfs2(*p);
                    colors ++;
                }
            }
            for (int i = 0; i < N; i += 2) {
                if (color[i] == color[i ^ 1]) {
                    valid = false;
                    break;
                }
            }
        }
        puts(valid ? "YES" : "NO");
    }
}
