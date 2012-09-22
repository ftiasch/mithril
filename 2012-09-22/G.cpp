#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
#include <climits>
using namespace std;

const int N = 40;
const int M = 20;
const int V = N + M + 1;

int n, limit, m, weight[M], current[M];
int capacity[V][V];

double p[101], w[M];

double sqr(double x) {
    return x * x;
}

int level[V], queue[V], next[V];

void bfs(int target) {
    memset(level, -1, sizeof(level));
    level[target] = 0;
    int tail = 0;
    queue[tail ++] = target;
    int head = 0;
    while (head != tail) {
        int u = queue[head ++];
        for (int i = 0; i <= target; ++ i) {
            if (capacity[i][u] > 0 && level[i] == -1) {
                next[i] = u;
                level[i] = level[u] + 1;
                queue[tail ++] = i;
            }
        }
    }
}

void argument(int i, int target) {
    while (i != target) {
        capacity[i][next[i]] --;
        capacity[next[i]][i] ++;
        i = next[i];
    }
}

int main() {
    for (int i = 60; i <= 100; ++ i) {
        p[i] = 4 - (3 * sqr(100 - i)) / 1600.0;
    }
    while (scanf("%d%d%d", &n, &limit, &m) == 3 && n + limit + m > 0) {
        int weightSum = 0;
        for (int i = 0; i < m; ++ i) {
            scanf("%d", weight + i);
            weightSum += weight[i];
        }
        for (int i = 0; i < m; ++ i) {
            w[i] = (double)weight[i];
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d", current + i);
        }
        memset(capacity, 0, sizeof(capacity));
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf("%d", &capacity[j][m + i]);
                if (capacity[j][m + i] > 0) {
                    capacity[j][m + i] = INT_MAX;
                }
            }
        }
        int target = n + m;
        for (int i = 0; i < n; ++ i) {
            capacity[m + i][target] = limit;
        }
        bool valid = true;
        for (int i = 0; i < m && valid; ++ i) {
            while (current[i] < 60) {
                bfs(target);
                if (level[i] == -1) {
                    valid = false;
                    break;
                }
                current[i] ++;
                argument(i, target);
            }
        }
        vector <pair <double, int> > events;
        for (int i = 0; i < m; ++ i) {
            for (int j = current[i] + 1; j <= 100; ++ j) {
                events.push_back(make_pair((p[j] - p[j - 1]) * w[i], i));
            }
        }
        sort(events.begin(), events.end(), greater <pair <double, int> >());
        bfs(target);
        for (int k = 0; k < (int)events.size(); ++ k) {
            int u = events[k].second;
            if (level[u] != -1) {
                current[u] ++;
                argument(u, target);
                bfs(target);
            }
        }
        double result = 0;
        if (valid) {
            for (int i = 0; i < m; ++ i) {
                result += p[current[i]] * w[i];
            }
            result /= weightSum;
        }
        printf("%.6f\n", result + 1e-8);
    }
    return 0;
}
