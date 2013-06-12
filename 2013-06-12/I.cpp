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

const int maxn = 50000;

int n;
long long p[maxn], b[maxn], u[maxn], target[maxn];
long long bitrate;

bool check(long long buffer)
{
    vector<pair<long long, long long> > client;
    vector<pair<long long, long long> > server;
    for (int i = 0; i < n; i++) {
        target[i] = max(b[i], p[i] + buffer);
        if (target[i] > b[i]) {
            client.push_back(make_pair(b[i], -1));
            client.push_back(make_pair(target[i], 1));
        }
        if (u[i] > 0) {
            server.push_back(make_pair(b[i], u[i]));
        }
    }
    sort(client.rbegin(), client.rend());
    sort(server.begin(), server.end());
    long long psum = 0;
    for (int i = 0; i + 1 < client.size(); i++) {
        psum += client[i].second;
        if (client[i].first != client[i + 1].first) {
            long long left = psum * (client[i].first - client[i + 1].first);
            while (left > 0) {
                if (server.empty() || server.back().first < client[i].first) {
                    return false;
                }
                long long transmitted = min(server.back().second, left);
                left -= transmitted;
                server.back().second -= transmitted;
                if (server.back().second == 0) {
                    server.pop_back();
                }
            }
        }
    }
    return true;
}

int main()
{
    scanf("%d%lld", &n, &bitrate);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld%lld", p + i, b + i, u + i);
    }
    long long lo = 0, hi = 1LL << 32;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid + 1)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    cout << lo - bitrate << endl;
}
