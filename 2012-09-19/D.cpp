#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}

    bool isValid() {
        return 0 <= x && x < 8 && 0 <= y && y < 8;
    }

    Point move(Point step) {
        return Point(x + step.x, y + step.y);
    }

    void mark(bool visit[8][8]) {
        if (isValid()) {
            visit[x][y] = true;
        }
    }
};

bool operator ==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

istream &operator >>(istream &in, Point &p) {
    string buffer;
    in >> buffer;
    p.x = buffer[0] - 'a';
    p.y = buffer[1] - '1';
    return in;
}

ostream &operator <<(ostream &out, Point &p) {
    printf("%c%c", 'a' + p.x, '1' + p.y);
    return out;
}

Point king, bishop, knight, target;

bool visit[8][8];

const Point KING_MOVE[8] = {Point(-1, -1), Point(-1, 0), Point(-1, 1),
                            Point( 0, -1),               Point( 0, 1),
                            Point( 1, -1), Point( 1, 0), Point( 1, 1)};
const Point BISHOP_MOVE[4] = {Point(-1, -1), Point(-1, 1),
                              Point( 1, -1), Point( 1, 1)};
const Point KNIGHT_MOVE[8] = {Point(-2, -1), Point(-2, 1),
                              Point(-1, -2), Point(-1, 2),
                              Point(1, -2), Point(1, 2),
                              Point(2, -1), Point(2, 1)};

bool isCheckmate(Point king, Point bishop, Point knight, Point target) {
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < 8; ++ i) {
        king.move(KING_MOVE[i]).mark(visit);
    }
    for (int i = 0; i < 4; ++ i) {
        Point p = bishop.move(BISHOP_MOVE[i]);
        while (true) {
            p.mark(visit);
            if (!p.isValid() || p == king || p == knight) {
                break;
            }
            p = p.move(BISHOP_MOVE[i]);
        }
    }
    for (int i = 0; i < 8; ++ i) {
        knight.move(KNIGHT_MOVE[i]).mark(visit);
    }
    if (!visit[target.x][target.y]) {
        return false;
    }
    for (int i = 0; i < 8; ++ i) {
        Point k = target.move(KING_MOVE[i]);
        if (k.isValid() && !visit[k.x][k.y]) {
            return false;
        }
    }
    return true;
}

int main() {
    freopen("chess2.in", "r", stdin);
    freopen("chess2.out", "w", stdout);
    cin >> king >> bishop >> knight >> target;
    for (int i = 0; i < 8; ++ i) {
        Point k = king.move(KING_MOVE[i]);
        if (!k.isValid() || k == bishop || k == knight) {
            continue;
        }
        if (isCheckmate(k, bishop, knight, target) && max(abs(k.x - target.x), abs(k.y - target.y)) > 1) {
            cout << "K" << k << endl;
            return 0;
        }
    }
    for (int i = 0; i < 4; ++ i) {
        Point b = bishop.move(BISHOP_MOVE[i]);
        while (true) {
            if (!b.isValid() || b == king || b == knight) {
                break;
            }
            if (isCheckmate(king, b, knight, target)) {
                cout << "B" << b << endl;
                return 0;
            }
            b = b.move(BISHOP_MOVE[i]);
        }
    }
    for (int i = 0; i < 8; ++ i) {
        Point n = knight.move(KNIGHT_MOVE[i]);
        if (!n.isValid() || n == king || n == bishop) {
            continue;
        }
        if (isCheckmate(king, bishop, n, target)) {
            cout << "N" << n << endl;
            return 0;
        }
    }
    cout << "impossible" << endl;
    return 0;
}
