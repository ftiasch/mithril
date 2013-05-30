#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point &operator +=(const Point &o) {
        x += o.x;
        y += o.y;
        return *this;
    }
};

int dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

const Point DELTA[4] = {Point(-1, 0), Point(0, -1), Point(0, 1), Point(1, 0)};

const int N = 4;
const int M = 8;

int n, m, w;
int hole[N][N], count[N][N];
bool block[N][N][4];

struct State {
    Point marbles[M];

    bool move(int d) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                count[i][j] = hole[i][j] == -1 ? 0 : -1;
            }
        }
        std::vector <std::pair <int, int> > orders;
        for (int i = 0; i < m; ++ i) {
            if (hole[marbles[i].x][marbles[i].y] == i) {
                count[marbles[i].x][marbles[i].y] ++;
            } else {
                orders.push_back(std::make_pair(dot(marbles[i], DELTA[d]), i));
            }
        }
        std::sort(orders.begin(), orders.end());
        for (int _ = (int)orders.size() - 1; _ >= 0; -- _) {
            int i = orders[_].second;
            Point &p = marbles[i];
            while (true) {
                if (count[p.x][p.y] < 0) {
                    if (hole[p.x][p.y] == i) {
                        break;
                    }
                    return false;
                } else {
                    if (!block[p.x][p.y][d] && count[p.x + DELTA[d].x][p.y + DELTA[d].y] <= 0) {
                        p.x += DELTA[d].x;
                        p.y += DELTA[d].y;
                    } else {
                        break;
                    }
                }
            }
            count[p.x][p.y] ++;
        }
        return true;
    }

    unsigned long long hash() const {
        unsigned long long ret = 0;
        for (int i = 0; i < m; ++ i) {
            ret <<= 3;
            ret |= marbles[i].x;
            ret <<= 3;
            ret |= marbles[i].y;
        }
        return ret;
    }
};

int main() {
    int test_count = 0;
    while (scanf("%d%d%d", &n, &m, &w) == 3 && m) {
        State start, target;
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &start.marbles[i].x, &start.marbles[i].y);
        }
        memset(hole, -1, sizeof(hole));
        for (int i = 0; i < m; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            hole[x][y] = i;
            target.marbles[i] = Point(x, y);
        }
        memset(block, 0, sizeof(block));
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                for (int k = 0; k < 4; ++ k) {
                    int x = i + DELTA[k].x;
                    int y = j + DELTA[k].y;
                    if (x < 0 || x >= n || y < 0 || y >= n) {
                        block[i][j][k] = true;
                    }
                }
            }
        }
        while (w --) {
            int x_1, y_1, x_2, y_2;
            scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
            for (int k = 0; k < 4; ++ k) {
                if (x_1 + DELTA[k].x == x_2 && y_1 + DELTA[k].y == y_2) {
                    block[x_1][y_1][k] = true;
                }
                if (x_2 + DELTA[k].x == x_1 && y_2 + DELTA[k].y == y_1) {
                    block[x_2][y_2][k] = true;
                }
            }
        }
        std::map <unsigned long long, int> states;
        std::queue <State> queue;
        queue.push(start);
        states[start.hash()] = 0;
        while (!queue.empty()) {
            State s = queue.front();
            queue.pop();
            for (int k = 0; k < 4; ++ k) {
                State t = s;
                if (t.move(k)) {
                    if (!states.count(t.hash())) {
                        states[t.hash()] = states[s.hash()] + 1;
                        queue.push(t);
                    }
                }
            }
        }
        printf("Case %d: ", ++ test_count);
        if (states.count(target.hash())) {
            printf("%d moves\n", states[target.hash()]);
        } else {
            puts("impossible");
        }
        puts("");
    }
    return 0;
}
