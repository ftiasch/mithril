#include <cstdio>
#include <cstring>
#include <climits>
#include <functional>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 501;

typedef pair <int, pair <int, int> > Pair;

int n, m, weight[N][N];
Pair longest[N][N], cnt[N][N];
vector <Pair> order;

Pair query(int x, int y) {
    Pair result = make_pair(0, make_pair(0, 0));
    for (int i = x; i >= 1; i -= i & -i) {
        for (int j = y; j >= 1; j -= j & -j) {
            result = max(result, cnt[i][j]);
        }
    }
    return result;
}

void insert(int x, int y, int v) {
    Pair tmp = make_pair(v, make_pair(x, y));
    for (int i = x; i <= n; i += i & -i) {
        for (int j = y; j <= m; j += j & -j) {
            cnt[i][j] = max(cnt[i][j], tmp);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            scanf("%d", &weight[i][j]);
            order.push_back(make_pair(weight[i][j], make_pair(i, j)));
        }
    }
    sort(order.begin(), order.end());
    memset(longest, 0, sizeof(longest));
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            cnt[i][j] = make_pair(INT_MIN, make_pair(i, j));
        }
    }
    for (int low = 0; low < (int)order.size(); ++ low) {
        int high = low;
        while (high < (int)order.size() && order[low].first == order[high].first) {
            high ++;
        }
        for (int i = low; i < high; ++ i) {
            int x = order[i].second.first;
            int y = order[i].second.second;
            longest[x][y] = query(x - 1, y - 1);
            longest[x][y].first ++;
        }
        for (int i = low; i < high; ++ i) {
            int x = order[i].second.first;
            int y = order[i].second.second;
            insert(x, y, longest[x][y].first);
        }
        low = high - 1;
    }
    Pair result = make_pair(0, make_pair(0, 0));
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            result = max(result, make_pair(longest[i][j].first, make_pair(i, j)));
        }
    }
    printf("%d\n", result.first);
    vector <pair <int, int> > ways;
    for (int i = result.second.first, j = result.second.second; i > 0 && j > 0; ) {
        ways.push_back(make_pair(i, j));
        Pair tmp = longest[i][j];
        i = tmp.second.first;
        j = tmp.second.second;
    }
    for (int i = (int)ways.size() - 1; i >= 0; -- i) {
        printf("%d%c", ways[i].first, i == 0? '\n': ' ');
    }
    for (int i = (int)ways.size() - 1; i >= 0; -- i) {
        printf("%d%c", ways[i].second, i == 0? '\n': ' ');
    }
    return 0;
}
