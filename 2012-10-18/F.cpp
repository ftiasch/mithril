#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int N = 1000;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

int n, m;
char shape[N][N + 1];

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}
};

vector <Point> parse(char token, int &minimum_x, int &minimum_y) {
    vector <Point> result;
    minimum_x = minimum_y = INT_MAX;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (shape[i][j] == token) {
                minimum_x = min(minimum_x, i);
                minimum_y = min(minimum_y, j);
                result.push_back(Point(i, j));
            }
        }
    }
    foreach (iter, result) {
        iter->x -= minimum_x;
        iter->y -= minimum_y;
    }
    return result;
}

void work(vector <Point> &shape, int &width, int &height) {
    width = height = 0;
    foreach (iter, shape) {
        width = max(width, iter->y + 1);
        height = max(height, iter->x + 1);
    }
}

struct Mask {
    unsigned long long mask[4];

    void clear() {
        memset(mask, 0, sizeof(mask));
    }

    unsigned long long operator[](int i) const {
        return mask[i];
    }

    void set(int k) {
        mask[k >> 6] |= 1ULL << (k & 63);
    }
};

bool operator & (const Mask &a, const Mask &b) {
    for (int i = 0; i < 4; ++ i) {
        if (a[i] & b[i]) {
            return true;
        }
    }
    return false;
}

Mask maskA[N], maskB[N];

void construct(vector <Point> &shape, int width, int height, Mask mask[], int delta) {
    for (int i = 0; i < height; ++ i) {
        mask[i].clear();
    }
    foreach (iter, shape) {
        int y = iter->y + delta;
        if (0 <= y && y < m) {
            mask[iter->x].set(y);
        }
    }
}

bool validMap[N][N], reachable[N][N];

const int LIMIT = 450;
const int DELTA[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", shape[i]);
    }
    int widthA, heightA, widthB, heightB, x_a, y_a, x_b, y_b;
    vector <Point> shapeA = parse('A', x_a, y_a);
    work(shapeA, widthA, heightA);
    vector <Point> shapeB = parse('B', x_b, y_b);
    work(shapeB, widthB, heightB);
    construct(shapeA, widthA, heightA, maskA, 0);
    memset(validMap, 0, sizeof(validMap));
    for (int dy = -widthB; dy <= widthA; ++ dy) {
        construct(shapeB, widthB, heightB, maskB, dy);
        for (int dx = -heightB; dx <= heightA; ++ dx) {
            bool valid = true;
            for (int i = 0; i < heightB && valid; ++ i) {
                int x = i + dx;
                if (0 <= x && x < heightA) {
                    if (maskA[x] & maskB[i]) {
                        valid = false;
                    }
                }
            }
            validMap[dx + heightB][dy + widthB] = valid;
            //if (valid) {
            //}
        }
    }
    memset(reachable, 0, sizeof(reachable));
//printf("%d %d\n%d %d\n", x_a, y_a, x_b, y_b);
    int x_0 = x_b - x_a;
    int y_0 = y_b - y_a;
    reachable[x_0 + LIMIT][y_0 + LIMIT] = true;
    queue <pair <int, int> > opened;
    opened.push(make_pair(x_0, y_0));
    int result = INT_MAX;
    while (!opened.empty()) {
        pair <int, int> ret = opened.front();
        int x = ret.first;
        int y = ret.second;
        int area = (max(heightA, heightB + x) - min(0, x)) * (max(widthA, widthB + y) - min(0, y));
        result = min(result, area);
        opened.pop();
        for (int k = 0; k < 4; ++ k) {
            int xx = x + DELTA[k][0];
            int yy = y + DELTA[k][1];
            if (-LIMIT <= xx && xx <= LIMIT && -LIMIT <= yy && yy <= LIMIT) {
                if (-heightB <= xx && xx <= heightA && -widthB <= yy && yy <= widthA && !validMap[xx + heightB][yy + widthB]) {
                    continue;
                }
                if (!reachable[xx + LIMIT][yy + LIMIT]) {
                    reachable[xx + LIMIT][yy + LIMIT] = true;
                    opened.push(make_pair(xx, yy));
                }
            }
        }
    }
    printf("%d\n", result);
    return 0;
}
