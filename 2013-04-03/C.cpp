#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <deque>
#include <map>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const double INF = 1e100;

char dir_name[256];

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    double norm2() const {
        return x * x + y * y;
    }

    double norm() const {
        return sqrt(norm2());
    }

    Point normalize() const {
        double d = norm();
        return Point(x / d, y / d);
    }

    Point operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
};

Point operator -(Point a, const Point &b) {
    return a -= b;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

const int N = 100000;
const Point DIRS[4] = {Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1)};

int n, dir[N], order[N];
Point points[N];
std::vector <int> groups[4];

double answer, answer_time;
std::pair <int, int> answer_pair;

bool by_x(int i, int j) {
    return points[i].x < points[j].x;
}

bool by_y(int i, int j) {
    return points[i].y < points[j].y;
}

void divide(int l, int r) {
    if (r - l <= 1) {
        return;
    }
    int m = l + r >> 1;
    double x_0 = points[order[m]].x;
    divide(l, m);
    divide(m, r);
    std::sort(order + l, order + r, by_y);
    std::deque <int> choices;
    for (int i = l; i < r; ++ i) {
        if (std::abs(points[order[i]].x - x_0) <= answer) { 
            while (!choices.empty() && points[order[i]].y - points[choices.front()].y >= answer) {
                choices.pop_front();
            }
            for (int j = 0; j < (int)choices.size(); ++ j) {
                double d = (points[order[i]] - points[choices[j]]).norm();
                if (d < answer) {
                    answer = d;
                    answer_pair = std::make_pair(order[i], choices[j]);
                    answer_time = 0.0;
                }
            }
            choices.push_back(order[i]);
        }
    }
}

struct Event {
    bool type; // query or insert
    int id;
    Point p;

    Event(bool type, int id, Point p): type(type), id(id), p(p) {}
};

bool operator <(const Event &a, const Event &b) {
    return a.p.x < b.p.x;
}

void solve(const std::vector <int> &stay, const std::vector <int> &move, Point axis_x, double speed) {
    Point axis_y(-axis_x.y, axis_x.x);
    std::vector <Event> events;
    foreach (iter, move) {
        events.push_back(Event(false, *iter, Point(dot(axis_x, points[*iter]), dot(axis_y, points[*iter]))));
    }
    foreach (iter, stay) {
        events.push_back(Event(true, *iter, Point(dot(axis_x, points[*iter]), dot(axis_y, points[*iter]))));
    }
    std::sort(events.begin(), events.end());
    std::map <double, int> map;
    foreach (iter, events) {
        if (iter->type) {
            std::map <double, int> :: iterator it = map.lower_bound(iter->p.y);
            if (it != map.end()) {
                if (std::abs(it->first - iter->p.y) < answer) {
                    answer = std::abs(it->first - iter->p.y);
                    answer_pair = std::make_pair(it->second, iter->id);
                    answer_time = (iter->p.x - dot(axis_x, points[it->second])) / speed;
                }
            } 
            if (it != map.begin()) {
                it --;
                if (std::abs(it->first - iter->p.y) < answer) {
                    answer = std::abs(it->first - iter->p.y);
                    answer_pair = std::make_pair(it->second, iter->id);
                    answer_time = (iter->p.x - dot(axis_x, points[it->second])) / speed;
                }
            }
        } else {
            map[iter->p.y] = iter->id;
        }
    }
}

int main() {
    dir_name['E'] = 0;
    dir_name['N'] = 1;
    dir_name['W'] = 2;
    dir_name['S'] = 3;
    bool first = true;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < 4; ++ i) {
            groups[i].clear();
        }
        for (int i = 0; i < n; ++ i) {
            char buffer[2];
            scanf("%lf%lf%s", &points[i].x, &points[i].y, buffer);
            groups[dir[i] = dir_name[(int)*buffer]].push_back(i);
        }
        answer = INF;

        for (int i = 0; i < n; ++ i) {
            order[i] = i;
        }
        std::sort(order, order + n, by_x);
        divide(0, n);

        for (int i = 0; i < 4; ++ i) {
            for (int d = 1; d <= 2; ++ d) {
                int j = (i + d) % 4;
                Point p = DIRS[j] - DIRS[i];
                solve(groups[i], groups[j], p.normalize(), p.norm());
            }
        }

        if (first) {
            first = false;
        } else {
            puts("");
        }
        printf("%.8f\n%d %d\n%.8f\n", answer, answer_pair.first + 1, answer_pair.second + 1, answer_time);
    }
    return 0;
}
