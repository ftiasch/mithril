#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 1000;

int n, m;
char buffer[N], map[N][N];

int x_1, y_1, x_2, y_2;

int memory[N][N][3][3];
bool visit[N][N][3][3];

struct Node {
    int x_1, y_1, x_2, y_2;

    Node(int x_1, int y_1, int x_2, int y_2) : x_1(x_1), y_1(y_1), x_2(x_2), y_2(y_2) {}

    bool valid() {
        if (x_1 == x_2 && y_1 == y_2) {
            return false;
        }
        if (abs(x_1 - x_2) > 1 || abs(y_1 - y_2) > 1) {
            return false;
        }
        if (x_1 < 0 || x_1 >= n + 2 || y_1 < 0 || y_1 >= m + 2
                || x_2 < 0 || x_2 >= n + 2 || y_2 < 0 || y_2 >= m + 2) {
            return false;
        }
        return true;
    }

    Node move(int t, int dx, int dy) {
        if (t == 1) {
            return Node(x_1 + dx, y_1 + dy, x_2, y_2);
        } else {
            return Node(x_1, y_1, x_2 + dx, y_2 + dy);
        }
    }

    int &getd() {
        int dx = x_1 - x_2 + 1;
        int dy = y_1 - y_2 + 1;
        return memory[x_1][y_1][dx][dy];
    }

    bool &getv() {
        int dx = x_1 - x_2 + 1;
        int dy = y_1 - y_2 + 1;
        return visit[x_1][y_1][dx][dy];
    }
};

const int DELTA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int main() {
    scanf("%d%d", &n, &m);
    gets(buffer);
    for (int i = 0; i < (n << 1) + 1; ++ i) {
        gets(buffer);
        for (int j = 0; j < (m << 1) + 1; ++ j) {
            map[2 + i][2 + j] = buffer[j];
        }
    }
    for (int i = 1; i <= n ; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (isdigit(map[1 + (i << 1)][1 + (j << 1)])) {
                int t = map[1 + (i << 1)][1 + (j << 1)] - '0';
                if (t == 1) {
                    x_1 = i;
                    y_1 = j;
                } else {
                    x_2 = i;
                    y_2 = j;
                }
            }
        }
    }
    for (int i = 0; i < n + 2; ++ i) {
        for (int j = 0; j < m + 2; ++ j) {
            for (int x = -1; x <= 1; ++ x) {
                for (int y = -1; y <= 1; ++ y) {
                    visit[i][j][x + 1][y + 1] = false;
                    memory[i][j][x + 1][y + 1] = INT_MAX;
                }
            }
        }
    }
    if (Node(x_1, y_1, x_2, y_2).valid()) {
        Node(x_1, y_1, x_2, y_2).getd() = 0;
        Node(x_1, y_1, x_2, y_2).getv() = true;
        queue <Node> nodes;
        nodes.push(Node(x_1, y_1, x_2, y_2));
        while (!nodes.empty()) {
            Node ret = nodes.front();
            nodes.pop();
            ret.getv() = false;
            for (int t = 1; t <= 2; ++ t) {
                int x = 1 + ((t == 1 ? ret.x_1 : ret.x_2) << 1);
                int y = 1 + ((t == 1 ? ret.y_1 : ret.y_2) << 1);
                for (int k = 0; k < 4; ++ k) {
                    Node now = ret.move(t, DELTA[k][0], DELTA[k][1]);
                    if (now.valid()) {
                        char c = map[x + DELTA[k][0]][y + DELTA[k][1]];
                        if (c == '|' || c == '-') {
                            continue;
                        }
                        if (ret.getd() + (c == '.') < now.getd()) {
                            now.getd() = ret.getd() + (c == '.');
                            if (!now.getv()) {
                                now.getv() = true;
                                nodes.push(now);
                            }
                        }
                    }
                }
            }
        }
    }
    int answer = INT_MAX;
    for (int x_1 = 0; x_1 < n + 2; ++ x_1) {
        for (int y_1 = 0; y_1 < m + 2; ++ y_1) {
            for (int dx = -1; dx <= 1; ++ dx) {
                for (int dy = -1; dy <= 1; ++ dy) {
                    int x_2 = x_1 + dx;
                    int y_2 = y_1 + dy;
                    if (Node(x_1, y_1, x_2, y_2).valid()
                            && !(1 <= x_1 && x_1 < n + 1 && 1 <= y_1 && y_1 < m + 1) 
                            && !(1 <= x_2 && x_2 < n + 1 && 1 <= y_2 && y_2 < m + 1)) {
                        answer = min(answer, Node(x_1, y_1, x_2, y_2).getd());
                    }
                }
            }
        }
    }
    if (answer == INT_MAX) {
        puts("Death");
    } else {
        printf("%d\n", answer);
    }
    return 0;
}
