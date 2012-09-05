#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 100000;
const int D = 18;

typedef pair <int, int> Pair;

int n, m, go[N][D];
Pair intervals[N];

bool compare(const Pair &a, const Pair &b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

int solve(int a, int b) {
    int i = lower_bound(intervals, intervals + n, make_pair(a, INT_MIN)) - intervals;
    if (i == n || intervals[i].second > b) {
        return 0;
    }
    int result = 0;
    for (int k = D - 1; k >= 0; -- k) {
        if (go[i][k] < n && intervals[go[i][k]].second <= b) {
            i = go[i][k];
            result += 1 << k;
        }
    }
    return result + 1;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &intervals[i].first, &intervals[i].second);
        }
        sort(intervals, intervals + n, compare);
        int newN = 0;
        for (int i = 0; i < n; ++ i) {
            while (newN > 0 && intervals[newN - 1].second >= intervals[i].second) {
                newN --;
            }
            intervals[newN ++] = intervals[i];
        }
        n = newN;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < D; ++ j) {
                go[i][j] = n;
            }
        }
        for (int i = n - 1, j = n; i >= 0; -- i) {
            while (j > 0 && intervals[i].second <= intervals[j - 1].first) {
                j --;
            }
            go[i][0] = j;
            for (int k = 0; go[i][k] < n; ++ k) {
                go[i][k + 1] = go[go[i][k]][k];
            }
        }
        for (int i = 0; i < m; ++ i) {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%d\n", solve(a, b));
        }
    }
    return 0;
}
