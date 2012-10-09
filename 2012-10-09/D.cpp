#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;

const int N = 81;

const int dx[] = {0, -1, 0, 1};
const int dy[] = {1, 0, -1, 0};
const string moves = "RULD";

bool burned[N][N];

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) { }

    Point move(int dir, int steps = 1) const {
        return Point(x + dx[dir] * steps, y + dy[dir] * steps);
    }

    bool isBurned() const {
        return x >= 0 && x < N && y >= 0 && y < N && burned[x][y];
    }

    void burn() const {
        int x = this->x, y = this->y;
        while (x < 0 || x >= N || y < 0 || y >= N || burned[x][y]) {
            x = (unsigned)rand() % N;
            y = (unsigned)rand() % N;
        }
        printf("%d %d\n", x, y);
        fflush(stdout);
        burned[x][y] = true;
    }
};

int main()
{
    Point now(N / 2, N / 2);
    int lastDir = -1;
    while (true) {
//for (int i = 0; i < N; i++) {
//    for (int j = 0; j < N; j++) {
//        if (i == now.x && j == now.y) {
//            putchar('O');
//        } else if (burned[i][j]) {
//            putchar('X');
//        } else {
//            putchar('.');
//        }
//    }
//    puts("");
//}
        string direction;
        int steps;
        cin >> direction;
        if (direction == "E") {
            return 0;
        }
        cin >> steps;
        int dir = moves.find(direction[0]);
        int left = (dir + 1) & 3, right = (dir - 1) & 3;
        now = now.move(dir, steps);
        if (now.move(dir).isBurned() || now.move(dir, 2).isBurned()) {
            if (now.move(left).isBurned() || now.move(left, 2).isBurned()) {
                now.move(right).burn();
            } else if (now.move(right).isBurned() || now.move(right, 2).isBurned()) {
                now.move(left).burn();
            } else if (now.move(left).move(dir, -1).isBurned()) {
                now.move(left).burn();
            } else if (now.move(right).move(dir, -1).isBurned()) {
                now.move(right).burn();
            } else {
                now.move(right).burn();
            }
        } else if (now.move(left).isBurned() || now.move(right).isBurned()) {
            now.move(dir).burn();
        } else {
            if (lastDir == dir) {
                now.move(dir).burn();
            } else {
                now.move(dir, 2).move(right).burn();
            }
        }
        lastDir = dir;
    }
}
