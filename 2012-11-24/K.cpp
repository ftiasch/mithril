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

const int maxn = 55555;
const double INF = 1e100;
const double EPS = 1e-11;
const double PI = acos(-1.);

double len[maxn], ang[maxn];
int n, k;

double angK, ratio;

double get(double a)
{
    a -= (int)a;
    while (a < 0) {
        a += 1.0;
    }
    return a;
}

bool check(double r)
{
    vector<pair<double,int> > events;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (len[i] <= r * ratio) {
            continue;
        } else if (len[i] >= r) {
            return false;
        } else {
            cnt ++;
            double ang2 = acos(r * ratio / len[i]);
            double delta1 = get((+ang2 - ang[i]) / angK);
            double delta2 = get((-ang2 - ang[i]) / angK);
            events.push_back(make_pair(delta1, +1));
            events.push_back(make_pair(delta2, -1));
            if (delta1 > delta2) {
                events.push_back(make_pair(1.0, -1));
                events.push_back(make_pair(0.0, +1));
            }
        }
    }
    sort(events.begin(), events.end());
    int dep = 0;
    FOR (it, events) {
        dep += it->second;
        if (cnt == dep) {
            return true;
        }
    }
    return false;
}

int main()
{
    freopen("tower.in", "r", stdin);
    freopen("tower.out", "w", stdout);
    scanf("%d%d", &n, &k);
    double maxR = 0, minR = INF;
    for (int i = 0; i < n; i++) {
        double xi, yi;
        scanf("%lf%lf", &xi, &yi);
        len[i] = hypot(xi, yi);
        ang[i] = atan2(xi, yi);
        maxR = max(maxR, len[i]);
        minR = min(minR, len[i]);
    }
    angK = 2 * PI / k;
    ratio = cos(angK / 2);
    double lo = minR, hi = maxR / ratio;
    for (int it = 0; it < 50; ++it) {
        double mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    printf("%.10f\n", (lo + hi) / 2.0);
}
