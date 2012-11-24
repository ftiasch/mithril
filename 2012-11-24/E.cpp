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

int n, limit;

map<vector<int>, bool> M;

bool go(vector<int> a)
{
    sort(a.begin(), a.end());
    if (M.count(a)) {
        return M[a];
    }
    bool &ret = M[a];
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            if (a[i] + a[j] <= limit) {
                vector<int> b = a;
                b.erase(b.begin() + j);
                b.erase(b.begin() + i);
                b.push_back(a[i] + a[j]);
                if (!go(b)) {
                    return ret = true;
                }
            }
        }
    }
    return ret = false;
}

bool solve(int n, int limit)
{
    while (n > 2 * limit) {
        n -= 2 * limit;
    }
    if (n <= limit) {
        return n % 2 == 0;
    } else {
        return (2 * limit + 1 - n) % 2 == 0;
    }
}

int main()
{
    freopen("pour.in", "r", stdin);
    freopen("pour.out", "w", stdout);
    int n, a, b;
    while (cin >> n >> a >> b) {
        cout << (solve(n, b / a) ? 1 : 2) << endl;
    }
}
