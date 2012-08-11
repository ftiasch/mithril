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

const int maxn = 11111;

int opt[maxn][2][2];

int n;
char s[2][maxn];

int main()
{
    scanf("%d", &n);
    scanf("%s%s", s[0], s[1]);
    memset(opt, -1, sizeof(opt));
    opt[0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int r = 0; r < 4; r++) {
            int r0 = r >> 1 & 1;
            int r1 = r & 1;
            if (opt[i][r0][r1] < 0) {
                continue;
            }
            for (int j = 0; j < 8; j++) {
                int num0 = s[0][i] == '1';
                int num1 = s[1][i] == '1';
                if (j & 4) {
                    num0 ^= 1;
                }
                if (j & 2) {
                    num1 ^= 1;
                }
                if (j & 1) {
                    num0 ^= 1;
                    num1 ^= 1;
                }
                int cost = opt[i][r0][r1];
                if (j & 4 && !r0) {
                    cost ++;
                }
                if (j & 2 && !r1) {
                    cost ++;
                }
                if (j & 1) {
                    cost ++;
                }
                if (num0) {
                    cost ++;
                }
                if (num1) {
                    cost ++;
                }
                int nr0 = j >> 2 & 1;
                int nr1 = j >> 1 & 1;
                if (opt[i + 1][nr0][nr1] < 0 || opt[i + 1][nr0][nr1] > cost) {
                    opt[i + 1][nr0][nr1] = cost;
                }
            }
        }
    }
    int ret = -1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (opt[n][i][j] < 0) {
                continue;
            }
            if (ret < 0 || ret > opt[n][i][j]) {
                ret = opt[n][i][j];
            }
        }
    }
    printf("%d\n", ret);
}
