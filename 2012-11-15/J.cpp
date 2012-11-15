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

struct Result
{
    int houseByPower[101];

    void clear() {
        memset(houseByPower, 0, sizeof(houseByPower));
    }

    void setCapacity(int cap) {
        for (int i = cap + 1; i <= 100; i++) {
            houseByPower[i] = houseByPower[cap];
        }
    }

    void normalize() {
        for (int i = 1; i <= 100; i++) {
            houseByPower[i] = max(houseByPower[i], houseByPower[i - 1]);
        }
    }

    Result operator*(const Result &o) const {
        Result res;
        res.clear();
        for (int i = 0; i <= 100; i++) {
            for (int j = 0; i + j <= 100; j++) {
                res.houseByPower[i + j] = max(res.houseByPower[i + j], houseByPower[i] + o.houseByPower[j]);
            }
        }
        return res;
    }
};

const int maxn = 1024;

int n;
vector<int> children[maxn];
int demand[maxn], capacity[maxn];

Result opt[maxn];

void dfs(int p)
{
    Result now;
    now.clear();
    FOR(it, children[p]) {
        dfs(*it);
        now = now * opt[*it];
    }
    for (int i = 100; i >= demand[p]; i--) {
        now.houseByPower[i] = max(now.houseByPower[i], now.houseByPower[i - demand[p]] + 1);
    }
    now.setCapacity(capacity[p]);
    now.normalize();
    opt[p] = now;
}

int main()
{
    scanf("%d", &n);
    n ++;
    for (int i = 1; i < n; i++) {
        int parent;
        scanf("%d%d%d", &parent, demand + i, capacity + i);
        children[parent].push_back(i);
    }
    dfs(0);
    int ret = 0;
    FOR(it, children[0]) {
        ret += opt[*it].houseByPower[100];
    }
    printf("%d\n", ret);
}
