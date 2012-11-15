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

const int maxn = 1024;
const int maxm = maxn * maxn * 10;
const double eps = 1e-11;

int n, L;
double x[maxn];

pair<double,int> event[maxm];
int events;

bool inRange(double a)
{
    return a >= 0.1 - eps && a <= 10 + eps;
}

int main()
{
    scanf("%d%d", &n, &L);
    for (int i = 0; i < n; i++) {
        scanf("%lf", x + i);
    }
    if (n == 1) {
        printf("10.0");
        return 0;
    } else if (n == 2 && L == 2) {
        bool found = false;
        double ans = 0;
        for (int k = -11111; k <= 11111; k += 2) {
            double s = fabs(x[1] - x[0]) / k;
            if (inRange(s)) {
                found = true;
                ans = max(ans, s);
            }
        }
        if (!found) {
            puts("no fika");
        } else {
            printf("%.10f\n", ans);
        }
        return 0;
    }
    events = 0;
    int conflicts = n * (n - 1) / 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double dist = fabs(x[i] - x[j]);
            double limit = dist * 10.0001;
            for (int delta = -1; delta <= 1; delta += 2) {
                int now = delta == -1 ? 1 : L - 1;
                while (now <= limit) {
                    double s = dist / now;
                    if (s >= 0.1 - eps) {
                        if (inRange(s)) {
                            assert(events < maxm);
                            event[events].first = s;
                            event[events].second = delta;
                            events ++;
                        } else {
                            conflicts += delta;
                        }
                    }
                    now += L;
                }
            }
        }
    }
    sort(event, event + events);
    for (int i = events - 1; i >= 0; i --) {
        conflicts += event[i].second;
        if (conflicts == 0) {
            printf("%.10f\n", event[i].first);
            return 0;
        }
    }
    puts("no fika");
}
