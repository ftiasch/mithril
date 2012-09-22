#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100000;

int n, x[N], y[N], d[N], xorder[N], yorder[N];

bool by_x(int i, int j) {
    return x[i] < x[j] || x[i] == x[j] && i < j;
}

bool by_y(int i, int j) {
    return y[i] < y[j] || y[i] == y[j] && i < j;
}

vector <int> xvalues, yvalues;

vector <int> order[N << 1], next[N << 1];

#define INDEX ((l + r) | (l != r))

void build(int l, int r) {
    int low = 0;
    int high = n;
    while (low < high) {
        int middle = (low + high) >> 1;
        if (x[xorder[middle]] >= xvalues[l]) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }
    order[INDEX].clear();
    for (int i = high; i < n && x[xorder[i]] <= xvalues[r]; ++ i) {
        order[INDEX].push_back(xorder[i]);
    }
    sort(order[INDEX].begin(), order[INDEX].end(), by_y);
    next[INDEX].resize(order[INDEX].size());
    for (int i = 0; i < (int)next[INDEX].size(); ++ i) {
        next[INDEX][i] = i;
    }
    if (l != r) {
        int m = (l + r) >> 1;
        build(l, m);
        build(m + 1, r);
    }
}

int x_min, x_max, y_min, y_max;
bool visit[N];
int head, tail, queue[N];

int find(vector <int> &next, int i) {
    if (i >= (int)next.size()) {
        return (int)next.size();
    }
    if (next[i] != i) {
        next[i] = find(next, next[i]);
    }
    return next[i];
}

void query(int l, int r) {
    if (x_max < xvalues[l] || xvalues[r] < x_min) {
        return;
    }
    if (x_min <= xvalues[l] && xvalues[r] <= x_max) {
        int low = 0;
        int high = (int)order[INDEX].size();
        while (low < high) {
            int middle = (low + high) >> 1;
            if (y[order[INDEX][middle]] >= y_min) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }
        for (int i = find(next[INDEX], high);
                 i < (int)next[INDEX].size() && y[order[INDEX][i]] <= y_max;
                 i = find(next[INDEX], i)) {
            if (!visit[order[INDEX][i]]) {
                visit[order[INDEX][i]] = true;
                queue[tail ++] = order[INDEX][i];
            }
            next[INDEX][i] = i + 1;
        }
    } else {
        int m = (l + r) >> 1;
        query(l, m);
        query(m + 1, r);
    }
}

int main() {
    int test_count = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
        printf("Case #%d:\n", ++ test_count);
        xvalues.clear();
        yvalues.clear();
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d%d", x + i, y + i, d + i);
            x[i] -= y[i];
            y[i] *= 2;
            y[i] += x[i];
            xorder[i] = yorder[i] = i;
            xvalues.push_back(x[i]);
            yvalues.push_back(y[i]);
        }
        sort(xorder, xorder + n, by_x);
        sort(yorder, yorder + n, by_y);
        sort(xvalues.begin(), xvalues.end());
        xvalues.erase(unique(xvalues.begin(), xvalues.end()), xvalues.end());
        sort(yvalues.begin(), yvalues.end());
        yvalues.erase(unique(yvalues.begin(), yvalues.end()), yvalues.end());
        int m = (int)xvalues.size() - 1;
        build(0, m);
        int q;
        scanf("%d", &q);
        memset(visit, 0, sizeof(visit));
        while (q --) {
            int id;
            scanf("%d", &id);
            id --;
            if (!visit[id]) {
                head = tail = 0;
                visit[id] = true;
                queue[tail ++] = id;
                while (head != tail) {
                    int u = queue[head ++];
                    x_min = max((long long)x[u] - d[u], (long long)INT_MIN);
                    x_max = min((long long)x[u] + d[u], (long long)INT_MAX);
                    y_min = max((long long)y[u] - d[u], (long long)INT_MIN);
                    y_max = min((long long)y[u] + d[u], (long long)INT_MAX);
                    query(0, m);
                }
                printf("%d\n", tail);
            } else {
                puts("0");
            }
        }
    }
    return 0;
}
