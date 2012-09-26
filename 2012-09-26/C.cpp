#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

int sign(double x) {
    return x < -EPS? -1: x > EPS;
}

double sqrtFix(double x) {
    return x < 0? 0: sqrt(x);
}

struct Point {
    double x, y, z;

    Point(double x = 0.0, double y = 0.0, double z = 0.0): x(x), y(y), z(z) {}

    double norm() const;
    double length() const;
};

bool operator <(const Point &a, const Point &b) {
    if (sign(a.x - b.x) != 0) {
        return sign(a.x - b.x) < 0;
    }
    if (sign(a.y - b.y) != 0) {
        return sign(a.y - b.y) < 0;
    }
    return sign(a.z - b.z) < 0;
}

bool operator ==(const Point &a, const Point &b) {
    return sign(a.x - b.x) == 0 && sign(a.y - b.y) == 0 && sign(a.z - b.z) == 0;
}

Point operator +(const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y, a.z + a.z);
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point operator *(const Point &a, double k) {
    return Point(a.x * k, a.y * k, a.z * k);
}

Point operator /(const Point &a, double k) {
    return Point(a.x / k, a.y / k, a.z / k);
}

Point det(const Point &a, const Point &b) {
    return Point(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double Point::norm() const {
    return dot(*this, *this);
}

double Point::length() const {
    return sqrtFix(norm());
}

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y >> p.z;
}

const int N = 500;

int mark[N][N];
Point info[N];
int n, cnt;

double mix(const Point &a, const Point &b, const Point &c) {
    return dot(a, det(b, c));
}

double area(int a, int b, int c) {
    return det(info[b] - info[a], info[c] - info[a]).length();
}

double volume(int a, int b, int c, int d) {
    return mix(info[b] - info[a], info[c] - info[a], info[d] - info[a]);
}

struct Face {
    int a, b, c;

    Face(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {}

    int &operator[](int i) {
        if (i == 0) {
            return a;
        }
        if (i == 1) {
            return b;
        }
        return c;
    }
};

vector <Face> faces;

void insert(int a, int b, int c) {
    faces.push_back(Face(a, b, c));
}

void add(int v) {
    vector <Face> tmp;
    cnt ++;
    for (int i = 0; i < (int)faces.size(); ++ i) {
        int a = faces[i][0];
        int b = faces[i][1];
        int c = faces[i][2];
        if (sign(volume(v, a, b, c)) < 0) {
            mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b] = mark[c][a] = mark[a][c] = cnt;
        } else {
            tmp.push_back(faces[i]);
        }
    }
    faces = tmp;
    for (int i = 0; i < (int)tmp.size(); ++ i) {
        int a = faces[i][0];
        int b = faces[i][1];
        int c = faces[i][2];
        if (mark[a][b] == cnt) {
            insert(b, a, v);
        }
        if (mark[b][c] == cnt) {
            insert(c, b, v);
        }
        if (mark[c][a] == cnt) {
            insert(a, c, v);
        }
    }
}

bool find() {
    for (int i = 2; i < n; ++ i) {
        Point ndir = det(info[0] - info[i], info[1] - info[i]);
        if (ndir.norm() == 0) {
            continue;
        }
        swap(info[i], info[2]);
        for (int j = i + 1; j < n; ++ j) {
            if (sign(volume(0, 1, 2, j)) != 0) {
                swap(info[j], info[3]);
                insert(0, 1, 2);
                insert(0, 2, 1);
                return true;
            }
        }
    }
    return false;
}


int main() {
    while (cin >> n) {
        for (int i = 0; i < n; ++ i) {
            cin >> info[i];
        }
        sort(info, info + n);
        n = unique(info, info + n) - info;
        faces.clear();
        random_shuffle(info, info + n);
        if (find()) {
            memset(mark, 0, sizeof(mark));
            cnt = 0;
            for (int i = 3; i < n; ++ i) {
                add(i);
            }
            int m = (int)faces.size();
            vector <bool> visit(m, false);
            int result = 0;
            for (int i = 0; i < m; ++ i) {
                if (!visit[i]) {
                    result ++;
                    int a = faces[i][0];
                    int b = faces[i][1];
                    int c = faces[i][2];
                    for (int j = 0; j < m; ++ j) {
                        int x = faces[j][0];
                        int y = faces[j][1];
                        int z = faces[j][2];
                        if (!visit[j] && sign(volume(a, b, c, x)) == 0 && sign(volume(a, b, c, y)) == 0 && sign(volume(a, b, c, z)) == 0) {
                            visit[j] = true;
                        }
                    }
                }
            }
            printf("%d\n", result);
        }
    }
    return 0;
}
