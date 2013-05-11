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

int k;
int a[10];

bool cmp(const pair<int,int> &a, const pair<int,int> &b)
{
    return a.second < b.second || a.second == b.second && a.first < b.first;
}

int main()
{
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", a + i);
    }
    vector<pair<int,int> > S;
    for (int msk = 0; msk < 1 << k; msk++) {
        int now0 = 0, now1 = 1;
        for (int i = k - 1; i >= 0; i--) {
            if (msk >> i & 1) {
                now0 = a[i] + now0;
                now1 = a[i] + now1;
            } else {
                now0 = a[i] - now0;
                now1 = a[i] - now1;
            }
            if (now0 > now1) {
                swap(now0, now1);
            }
            if (i != 0) {
                now0 = max(now0, 0);
                if (now0 > now1) {
                    break;
                }
            }
        }
        if (now0 <= now1) {
            S.push_back(make_pair(now0, now1));
        }
    }
    sort(S.begin(), S.end());
    vector<pair<int,int> > ans;
    FOR (it, S) {
        if (ans.size() > 0 && ans.back().second >= it->first) {
            ans.back().second = max(ans.back().second, it->second);
        } else {
            ans.push_back(*it);
        }
    }
    printf("%d\n", (int)ans.size());
    FOR (it, ans) {
        printf("%d %d\n", it->first, it->second);
    }
}
