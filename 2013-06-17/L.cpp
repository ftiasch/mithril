#include <cstdio>
#include <cstring>
#include <queue>
#include <climits>
#include <algorithm>

static const int DELTA_X[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
static const int DELTA_Y[8] = {-1,  0,  1, -1, 1, -1, 0, 1};


const int N = 1500 + 3;

int n, m, type[N][N], sum[3][N][N];
char map[N][N];
bool visit[N][N];

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

int get_sum(int t, int x_1, int y_1, int x_2, int y_2) {
    return sum[t][x_1][y_1] - sum[t][x_1][y_2] - sum[t][x_2][y_1] + sum[t][x_2][y_2];
}

bool check(int i, int j, int x) {
    bool found = true;
    found &= i == 1 || j + x - 1 == m || get_sum(1, i - 1, j - 1, i + x + 1, j + x + 1) > 0;
    found &= i + x - 1 == n || j == 1 || get_sum(2, i - 1, j - 1, i + x + 1, j + x + 1) > 0;
    return found;
}

int get_empty(int i, int j) {
    int low = 0;
    int high = std::min(n - i + 1, m - j + 1);
    while (low < high) {
        int middle = low + high + 1 >> 1;
        if (get_sum(0, i, j, i + middle, j + middle) == middle * middle) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }
    return low;
}

int main() {
    freopen("labyrinth.in", "r", stdin);
    freopen("labyrinth.out", "w", stdout);
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", map[i] + 1);
    }
    memset(type, 0, sizeof(type));
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (map[i][j] == '#') {
                type[i][j] = 3;
            }
        }
    }

    memset(visit, 0, sizeof(visit));
    std::queue <Point> queue;
    for (int j = 1; j <= m; ++ j) {
        if (!visit[1][j] && map[1][j] == '#') {
            //type[0][j] = 1;
            visit[1][j] = true;
            queue.push(Point(1, j));
        }
    }
    for (int i = 1; i <= n; ++ i) {
        if (!visit[i][m] && map[i][m] == '#') {
            //type[i][m + 1] = 1;
            visit[i][m] = true;
            queue.push(Point(i, m));
        }
    }
    while (!queue.empty()) {
        int x = queue.front().x;
        int y = queue.front().y;
        queue.pop();
        type[x][y] = 1;
        for (int k = 0; k < 8; ++ k) {
            int xx = x + DELTA_X[k];
            int yy = y + DELTA_Y[k];
            if (1 <= xx && xx <= n && 1 <= yy && yy <= m && !visit[xx][yy] && map[xx][yy] == '#') {
                visit[xx][yy] = true;
                queue.push(Point(xx, yy));
            }
        }
    }

    for (int j = 1; j <= m; ++ j) {
        if (!visit[n][j] && map[n][j] == '#') {
            visit[n][j] = true;
            //type[n + 1][j] = 2;
            queue.push(Point(n, j));
        }
    }
    for (int i = 1; i <= n; ++ i) {
        if (!visit[i][1] && map[i][1] == '#') {
            visit[i][1] = true;
            //type[i][0] = 2;
            queue.push(Point(i, 1));
        }
    }
    while (!queue.empty()) {
        int x = queue.front().x;
        int y = queue.front().y;
        queue.pop();
        type[x][y] = 2;
        for (int k = 0; k < 8; ++ k) {
            int xx = x + DELTA_X[k];
            int yy = y + DELTA_Y[k];
            if (1 <= xx && xx <= n && 1 <= yy && yy <= m && !visit[xx][yy] && map[xx][yy] == '#') {
                visit[xx][yy] = true;
                queue.push(Point(xx, yy));
            }
        }
    }

    memset(sum, 0, sizeof(sum));
    for (int t = 0; t < 3; ++ t) {
        for (int i = n + 1; i >= 0; -- i) {
            for (int j = m + 1; j >= 0; -- j) {
                sum[t][i][j] = sum[t][i + 1][j] + sum[t][i][j + 1] - sum[t][i + 1][j + 1] + (type[i][j] == t);
            }
        }
    }

    int answer = INT_MAX, answer_x, answer_y;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (i + j == 2) {
                continue;
            }
            int low = 0;
            int high = get_empty(i, j);
            if (i + high - 1 == n && j + high - 1 == m) {
                high --;
            }
            if (!check(i, j, high)) {
                continue;
            }
            while (low < high) {
                int middle = low + high >> 1;
                if (check(i, j, middle)) {
                    high = middle;
                } else {
                    low = middle + 1;
                }
            }
            answer = std::min(answer, high);
            if (answer == high) {
                answer_x = i;
                answer_y = j;
            }
        }
    }
    if (answer == INT_MAX) {
        puts("Impossible");
    } else {
        printf("%d %d %d\n", answer, answer_y, answer_x);
    }
    return 0;
}
