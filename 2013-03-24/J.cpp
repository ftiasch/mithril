#include <cstdio>
#include <cstring>
#include <deque>
#include <utility>
#include <algorithm>

const int N = 100000;

int n, init[N], inc[N], order[N], m;
std::pair <int, int> queries[N];
int answer[N];

bool compare(int i, int j) {
    if (inc[i] != inc[j]) {
        return inc[i] < inc[j];
    }
    if (init[i] != init[j]) {
        return init[i] < init[j];
    }
    return i > j;
}

long double over(int u, int v) {
    return ((long double)init[u] - init[v]) / (inc[v] - inc[u]);
}

long long get_value(int i, int x) {
    return init[i] + (long long)inc[i] * x;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", init + i, inc + i);
        order[i] = i;
    }
    std::sort(order, order + n, compare);
    std::deque <int> queue;
    for (int p = 0; p < n; ++ p) {
        int id = order[p];
        if (!queue.empty()) {
            if (inc[queue.back()] == inc[id]) {
                queue.pop_back();
            }
            while ((int)queue.size() >= 2) {
                int u = queue[queue.size() - 2];
                int v = queue[queue.size() - 1];
                long long d = (long long)(init[u] - init[id]) * (inc[v] - inc[u]) - (long long)(init[u] - init[v]) * (inc[id] - inc[u]);
                if (d < 0 || d == 0 && id < v) {
                    queue.pop_back();
                } else {
                    break;
                }
            }
        }
        queue.push_back(id);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d", &queries[i].first);
        queries[i].second = i;
    }
    std::sort(queries, queries + m);
    for (int i = 0; i < m; ++ i) {
        int x = queries[i].first;
        while ((int)queue.size() >= 2) {
            if (get_value(queue[0], x) < get_value(queue[1], x)) {
                queue.pop_front();
            } else if (get_value(queue[0], x) == get_value(queue[1], x) && queue[0] > queue[1]) {
                queue.pop_front();
            } else {
                break;
            }
        }
        answer[queries[i].second] = queue.front() + 1;
    }
    for (int i = 0; i < m; ++ i) {
        printf("%d\n", answer[i]);
    }
    return 0;
}
