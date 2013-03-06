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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const int maxn = 888;
const double pi = acos(-1.0);
const double eps = 1e-16;

#define SQR(a) ((a) * (a))

struct Point
{
    int x, y;

    int dist2(const Point &o) const {
        return SQR(x - o.x) + SQR(y - o.y);
    }
};

int n;

Point pts[maxn];

int dist2[maxn][maxn];
double dist[maxn][maxn];

double ang[maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &pts[i].x, &pts[i].y);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist2[i][j] = pts[i].dist2(pts[j]);
            dist[i][j] = sqrt(dist2[i][j]);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j ++) {
            if (j == i) {
                continue;
            }
            ang[j] = atan2((double)pts[j].y - pts[i].y, (double)pts[j].x - pts[i].x);
            for (int k = 0; k < j; k++) {
                if (k == i) {
                    continue;
                }
                int c2 = dist2[j][k];
                int a2 = dist2[i][j], b2 = dist2[i][k];
                int d = a2 + b2 - c2;
                if (d > 0) {
                    double angle = abs(ang[k] - ang[j]);
                    if (angle > pi) {
                        angle = 2 * pi - angle;
                    }
                    if (angle < 1e-5) {
                        continue;
                    }
                    //assert(angle < pi / 2);
                    int integerPart = (int)(pi / (2 * angle) + eps);
                    if (integerPart >= 10) {
                        continue;
                    }
                    double cosA = d / (2 * dist[i][j] * dist[i][k]);
                    if ((int)(cosA * 1000 + eps) % 10 == integerPart) {
                        ans ++;
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
}
