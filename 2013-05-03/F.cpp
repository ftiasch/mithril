#include <cstdio>
#include <cstring>
#include <climits>
#include <deque>
#include <algorithm>

const int N = 1000;
const int INF = 1000000000;

int n, m, height[N][N], dist[N];
char map[N][N + 1];

int a[N], b[N], answer[N][N];

bool check(int i, int j, int k) {
    return (long long)(b[j] - b[i]) * (a[j] - a[k]) < (long long)(b[k] - b[j]) * (a[i] - a[j]);
}

int get_value(int i, int x) {
    return a[i] * x + b[i];
}

void solve(int* answer, int n) {
    std::deque <int> queue;
    for (int i = 0; i < n; ++ i) {
        if (b[i] == -1) {
            continue;
        }
        while ((int)queue.size() >= 2 && !check(queue[(int)queue.size() - 2], queue.back(), i)) {
            queue.pop_back();
        }
        queue.push_back(i);
    }
    for (int i = 0; i < n; ++ i) {
        while ((int)queue.size() >= 2 && get_value(queue[0], i) > get_value(queue[1], i)) {
            queue.pop_front();
        }
        answer[i] = get_value(queue[0], i) + i * i;
    }
}

int main() {
    scanf("%d%d", &n,  &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", map[i]);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            height[i][j] = INF;
        }
    }
    for (int j = 0; j < m; ++ j) {
        dist[j] = INF;
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            dist[j] = map[i][j] == '1' ? 0 : dist[j] + 1;
            height[i][j] = std::min(height[i][j], dist[j]);
        }
    }
    for (int j = 0; j < m; ++ j) {
        dist[j] = INF;
    }
    for (int i = n - 1; i >= 0; -- i) {
        for (int j = 0; j < m; ++ j) {
            dist[j] = map[i][j] == '1' ? 0 : dist[j] + 1;
            height[i][j] = std::min(height[i][j], dist[j]);
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            a[j] = - 2 * j;
            b[j] = height[i][j] == INF ? -1 : j * j + height[i][j] * height[i][j];
            answer[i][j] = INF;
        }
        solve(answer[i], m);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            printf("%d%c", answer[i][j], " \n"[j == m - 1]);
        }
    }
    return 0;
}
