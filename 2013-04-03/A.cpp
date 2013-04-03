#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}

    Point negate() const {
        return Point(-x, -y);
    }

    Point operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
};

std::istream &operator >>(std::istream &in, Point &p) {
    return in >> p.x >> p.y;
}

bool operator <(const Point &a, const Point &b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

Point operator -(Point a, const Point &b) {
    return a -= b;
}

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

bool is_convex(const Point &a, const Point &b, const Point &c) {
    return det(b - a, c - b) > 0;
}

std::vector <Point> get_hull(std::vector <Point> points) {
    std::vector <Point> hull;
    for (int i = 0; i < (int)points.size(); ++ i) {
        while ((int)hull.size() >= 2 && !is_convex(hull[(int)hull.size() - 2], hull.back(), points[i])) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    return hull;
}

int n, total;
std::vector <Point> points;

long long answer;

void solve() {
    std::sort(points.begin(), points.end());
    for (int k = 0; k < 2; ++ k) {
        std::vector <Point> new_points;
        for (int i = 0; i < n; ++ i) {
            if ((k == 0 && i == 0) || (k == 1 && i == n - 1)) {
                continue;
            }
            new_points.push_back(points[i]);
        }
        answer += (int)get_hull(new_points).size();
    }
    std::vector <Point> hull = get_hull(points);
    std::vector <Point> now_hull;
    for (int k = 0; k < (int)hull.size(); ++ k) {
        if (0 < k && k < (int)hull.size() - 1) {
            Point p = hull[k]; // deleted point
            int left = (int)now_hull.size();
            int now_size = total - 1;
            std::vector <Point> backup;
            int delete_id = std::lower_bound(points.begin(), points.end(), p) - points.begin();
            int begin = std::lower_bound(points.begin(), points.end(), hull[k - 1]) - points.begin() + 1;
            int end = std::lower_bound(points.begin(), points.end(), hull[k + 1]) - points.begin();
            for (int i = begin; i <= end; ++ i) {
                if (i == delete_id) {
                    continue;
                }
                while ((int)now_hull.size() >= 2 && !is_convex(now_hull[(int)now_hull.size() - 2], now_hull.back(), points[i])) {
                    now_size --;
                    if ((int)now_hull.size() == left) {
                        left --;
                        backup.push_back(now_hull.back());
                    }
                    now_hull.pop_back();
                }
                now_size ++;
                now_hull.push_back(points[i]);
            }
            now_size --;
            answer += now_size;
            while ((int)now_hull.size() > left) {
                now_hull.pop_back();
            }
            while (!backup.empty()) {
                now_hull.push_back(backup.back());
                backup.pop_back();
            }
        }
        now_hull.push_back(hull[k]);
    }
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++ i) {
        Point p;
        std::cin >> p;
        points.push_back(p);
    }
#define FLIP for (int i = 0; i < n; ++ i) points[i] = points[i].negate() 
    std::sort(points.begin(), points.end());
    total = get_hull(points).size();
    FLIP;
    std::sort(points.begin(), points.end());
    total += get_hull(points).size() - 2;
    FLIP;

    answer = (long long)(n - total) * total - 4;
    solve();
    FLIP;
    solve();
    long long d = n;
    long long g = std::__gcd(answer, d);
    answer /= g;
    d /= g;
    std::cout << answer << "/" << d << std::endl;
    return 0;
}
