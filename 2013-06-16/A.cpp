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

const long long inf = 1LL << 32;
long long a, m, sl, sr, tl, tr;

int n; // multiply times

vector<pair<bool,int> > normalize(const vector<pair<bool,int> > &a)
{
    vector<pair<bool,int> > ret;
    FOR (it, a) {
        if (it->second == 0) {
            continue;
        }
        if (!ret.empty() && ret.back().first == it->first) {
            ret.back().second += it->second;
        } else {
            ret.push_back(*it);
        }
    }
    return ret;
}

int main()
{
    int cas = 0;
    while (cin >> a >> m >> sl >> sr >> tl >> tr && a) {
        long long l = sl, r = sr;
        long long ansLen = inf;
        vector<pair<bool,int> > ans; // isA, run length
        n = 0;
        while (r <= tr) {
            long long lo = max(0LL, tl - l), hi = tr - r;
            if (lo <= hi) {
                lo = (lo + a - 1) / a;
                hi = hi / a;
                long long mul = 1;
                for (int it = 0; it <= n; it++, mul *= m) {
                    long long t = lo;
                    if (t % mul) {
                        t -= t % mul;
                        t += mul;
                    }
                    if (t < lo || t > hi) {
                        continue;
                    }
                    vector<pair<bool,int> > path;
                    for (int j = 0; j < n; j++) {
                        path.push_back(make_pair(true, t % m));
                        path.push_back(make_pair(false, -1));
                        t /= m;
                    }
                    path.push_back(make_pair(true, t));
                    long long now = 0;
                    FOR (it, path) {
                        now += abs(it->second);
                    }
                    reverse(path.begin(), path.end());
                    path = normalize(path);
                    if (now < ansLen) {
                        ansLen = now;
                        ans = path;
                    } else if (now == ansLen) {
                        ans = max(ans, path);
                    }
                }
            }
            if (m == 1) {
                break;
            }
            n ++;
            l *= m;
            r *= m;
        }
        printf("Case %d:", ++cas);
        if (ansLen == inf) {
            puts(" impossible");
        } else if (ans.empty()) {
            puts(" empty");
        } else {
            FOR (it, ans) {
                printf(" %d%c", abs(it->second), it->first ? 'A' : 'M');
            }
            puts("");
        }
    }
}
