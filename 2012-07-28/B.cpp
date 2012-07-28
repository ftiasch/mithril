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

const int maxn = 1400;
const int maxm = maxn / 32 + 1;

bool conn[maxn][maxn];
int conn2[maxn][maxn];
long long conn2x[maxn], conn2y[maxn];
unsigned inMask[maxn][maxm];
unsigned outMask[maxn][maxm];
int outdegree[maxn];
int indegree[maxn];

char buf[maxn * maxn / 2 / 4 + 10];
int ptr;
int n, m;

inline int getCode(char ch)
{
    return ch >= '0' && ch <= '9' ? ch - '0' : ch - 'A' + 10;
}

bool nextBit()
{
    bool ret = getCode(buf[ptr >> 2]) >> (3 - (ptr & 3)) & 1;
    ptr ++;
    return ret;
}

void readInput()
{
    ptr = 0;
    scanf("%d%d", &n, &m);
    scanf("%s", buf);
    memset(conn, false, sizeof(conn));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nextBit()) {
                conn[i][j] = true;
            } else {
                conn[j][i] = true;
            }
        }
    }
    memset(inMask, 0, sizeof(inMask));
    memset(outMask, 0, sizeof(outMask));
    memset(outdegree, 0, sizeof(outdegree));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (conn[i][j]) {
                inMask[j][i >> 5] |= 1U << (i & 31);
                outMask[i][j >> 5] |= 1U << (j & 31);
                outdegree[i] ++;
                indegree[j] ++;
            }
        }
    }
}

int main()
{
    readInput();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int cnt = 0;
            for (int k = 0; k < maxm; k++) {
                cnt += __builtin_popcount(outMask[i][k] & inMask[j][k]);
            }
            conn2[i][j] = cnt;
        }
    }
    if (m > n) {
        cout << 0 << endl;
    } else if (m == 3) {
        long long ans3 = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (conn[i][j]) {
                    ans3 += conn2[j][i];
                }
            }
        }
        assert(ans3 % 3 == 0);
        cout << ans3 / 3 << endl;
    } else {
        assert(m == 4 || m == 5);
        long long ans4 = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans4 += (long long)conn2[i][j] * conn2[j][i];
            }
        }
        if (m == 4) {
            assert(ans4 % 4 == 0);
            cout << ans4 / 4 << endl;
        } else {
            long long big = 0;
            memset(conn2x, 0, sizeof(conn2x));
            memset(conn2y, 0, sizeof(conn2y));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    conn2x[i] += conn2[i][j];
                    conn2y[j] += conn2[i][j];
                }
            }
            for (int i = 0; i < n; i++) {
                big += conn2y[i] * conn2x[i];
            }
            big -= ans4;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (conn[i][j]) {
                        big -= (outdegree[i] + indegree[j] - 1) * conn2[j][i];
                    }
                }
            }
            // big = ans * 5 + rev
            long long rev = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    rev += conn2[i][j];
                }
            }
            rev *= (n - 3) * (n - 4) / 2;
            long long small = 0;
            for (int i = 0; i < n; i++) {
                long long wys = conn2x[i] * conn2x[i];
                for (int j = 0; j < n; j++) {
                    wys -= conn2[i][j] * conn2[i][j];
                }
                small += wys;
            }
            small /= 2;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (conn[i][j]) {
                        small -= conn2[i][j] * outdegree[j];
                        small -= outdegree[j] * (outdegree[j] - 1) / 2;
                    }
                }
            }
            rev = rev - small * 3;
            long long ans5 = big - rev;
            assert(ans5 % 5 == 0);
            cout << ans5 / 5 << endl;
        }
    }
}
