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

int main()
{
    int n, m, cas = 0;
    while (scanf("%d%d", &n, &m) == 2 && n) {
        vector<pair<int,int> > pts(n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pts[i].first, &pts[i].second);
        }
        while (true) {
            bool changed = false;
            for (int i = 0; i < n; i++) {
                int x1 = pts[(i + 1) % n].first - pts[i].first;
                int y1 = pts[(i + 1) % n].second - pts[i].second;
                int x2 = pts[(i + n - 1) % n].first - pts[i].first;
                int y2 = pts[(i + n - 1) % n].second - pts[i].second;
                if ((long long)x1 * y2 == (long long)x2 * y1) {
                    changed = true;
                    pts.erase(pts.begin() + i);
                    n --;
                    break;
                }
            }
            if (!changed) {
                break;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            pts[i].first -= pts[0].first;
            pts[i].second -= pts[0].second;
        }
        int g = 0;
        for (int i = 0; i < n; i++) {
            g = __gcd(g, abs(pts[i].first));
            g = __gcd(g, abs(pts[i].second));
        }
        for (int i = 0; i < n; i++) {
            pts[i].first /= g;
            pts[i].second /= g;
        }
        long long area = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += (long long)pts[i].first * pts[j].second - (long long)pts[i].second * pts[j].first;
        }
        area = abs(area);
        unsigned long long ans = area * ((unsigned long long)m * (m + 1) * (2 * m + 1) / 6) + 2 * m;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int g = __gcd(abs(pts[j].first - pts[i].first), abs(pts[j].second - pts[i].second));
            ans -= g * ((long long)m * (m + 1) / 2);
        }
        ans /= 2;
        cout << "Case " << ++cas << ": " << ans << endl;
    }
}
