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

const int maxn = 4001;

double prob[maxn][maxn];
bool seen[maxn][maxn];
#define memo prob

double expected[maxn];
double probability[maxn];

int n, m;

double go(int pos, int selected)
{
    double &ret = memo[pos][selected];
    if (seen[pos][selected]) {
        return ret;
    }
    seen[pos][selected] = true;
    if (pos == m) {
        return ret = expected[n - selected] + selected;
    }
    ret = go(pos + 1, selected);
    ret -= go(pos + 1, selected + 1) / (n - selected);
    return ret;
}

double goP(int pos, int selected)
{
    double &ret = memo[pos][selected];
    if (seen[pos][selected]) {
        return ret;
    }
    seen[pos][selected] = true;
    if (pos == m) {
        return ret = 1.0;
    }
    ret = goP(pos + 1, selected);
    ret -= goP(pos + 1, selected + 1) / (n - selected);
    return ret;
}

double solve(int n, int m)
{
    ::n = n, ::m = m;
    memset(seen, false, sizeof(seen));
    double sum = go(0, 0);
    memset(seen, false, sizeof(seen));
    double cnt = goP(0, 0);
//printf("%.10f %.10f\n", sum, cnt);
    return sum / cnt;
}

int parent[maxn];

int findRoot(int p)
{
    return parent[p] >= 0 ? parent[p] = findRoot(parent[p]) : p;
}

bool mergeComp(int a, int b)
{
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) {
        return false;
    }
    parent[a] = b;
    return true;
}

int main()
{
    prob[1][1] = 1;
    expected[1] = 1;
    for (int n = 2; n < maxn; n++) {
        double sum = 0;
        for (int k = 1; k <= n; k++) {
            prob[n][k] += prob[n-1][k-1];
            prob[n][k] += prob[n-1][k] * (n - 1);
            prob[n][k] /= n;
            sum += prob[n][k] * k;
        }
        expected[n] = sum;
    }
    int tests, n, c;
    scanf("%d", &tests);
    while (tests --) {
        scanf("%d%d", &n, &c);
        int cycles = 0, comps = n;
        memset(parent, -1, sizeof(parent));
        set<int> singles;
        for (int i = 0; i < n; i++) {
            singles.insert(i);
        }
        for (int i = 0; i < n; i++) {
            int ai;
            scanf("%d", &ai);
            ai --;
            if (ai >= 0) {
                singles.erase(ai);
                singles.erase(i);
                if (mergeComp(ai, i)) {
                    comps --;
                } else {
                    cycles ++;
                    comps --;
                }
            }
        }
        assert(singles.size() <= comps);
        printf("%.10f\n", (solve(comps, singles.size()) + cycles) * c);
    }
}
