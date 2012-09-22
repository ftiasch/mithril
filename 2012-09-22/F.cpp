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

const int maxn = 100011;

int n, m;
int next[maxn];
double prob[maxn];

int main()
{
    while (scanf("%d%d", &n, &m) == 2 && n) {
        memset(next, -1, sizeof(next));
        memset(prob, 0, sizeof(prob));
        for (int i = 0; i < m; i++) {
            int xi, yi;
            scanf("%d%d", &xi, &yi);
            next[xi] = yi;
        }
        for (int i = n - 1; i >= 0; i--) {
            if (next[i] >= 0) {
                prob[i] = prob[next[i]];
            } else {
                for (int j = 1; j <= 6; j++) {
                    prob[i] += prob[i + j];
                }
                prob[i] /= 6;
                prob[i] += 1.0;
            }
        }
        printf("%.4f\n", prob[0] + 1e-11);
    }
}
