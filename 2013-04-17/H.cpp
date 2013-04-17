#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 1000;
const int DELTA[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int n, w, h, dist[N][N];
std::vector <std::pair <int, int> > points[N + N];

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d%d%d", &n, &w, &h);
        for (int i = 0; i < w; ++ i) {
            for (int j = 0; j < h; ++ j) {
                dist[i][j] = INT_MAX;
            }
        }
        std::queue <std::pair <int, int> > queue;
        for (int i = 0; i < n; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            dist[x][y] = 0;
            queue.push(std::make_pair(x, y));
        }
        while (!queue.empty()) {
            int i = queue.front().first;
            int j = queue.front().second;
            queue.pop();
            for (int k = 0; k < 4; ++ k) {
                int x = i + DELTA[k][0];
                int y = j + DELTA[k][1];
                if (0 <= x && x < w && 0 <= y && y < h && dist[x][y] == INT_MAX) {
                    dist[x][y] = dist[i][j] + 1;
                    queue.push(std::make_pair(x, y));
                }
            }
        }
        for (int i = 0; i <= w + h - 2; ++ i) {
            points[i].clear();
        }
        for (int i = 0; i < w; ++ i) {
            for (int j = 0; j < h; ++ j) {
                points[std::min(dist[i][j], w + h - 2)].push_back(std::make_pair(i, j));
            }
        }
        int sum_min = INT_MAX;
        int sub_min = INT_MAX;
        int sum_max = INT_MIN;
        int sub_max = INT_MIN;
        int total = 0;
        int answer = 0;
        for (int i = w + h - 2; i >= 0; -- i) {
            foreach (iter, points[i]) {
                total ++;
                sum_min = std::min(sum_min, iter->first + iter->second);
                sum_max = std::max(sum_max, iter->first + iter->second);
                sub_min = std::min(sub_min, iter->first - iter->second);
                sub_max = std::max(sub_max, iter->first - iter->second);
            }
            if (total) {
                int tmp = std::min(i, std::max(sum_max - sum_min, sub_max - sub_min));
                answer = std::max(answer, tmp);
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}
