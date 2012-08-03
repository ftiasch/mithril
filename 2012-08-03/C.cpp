#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    return b == 0? a: gcd(b, a % b);
}

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}

    Point reduce() const {
        int d = gcd(x, y);
        int xx = x / d;
        int yy = y / d;
        if (yy < 0) {
            xx *= -1;
            yy *= -1;
        } else if (yy == 0 && xx < 0) {
            xx *= -1;
        }
        return Point(xx, yy);
    }

    Point slope() const {
        return Point(x, y).reduce();
    }

    Point rotate() const {
        return Point(-y, x);
    }

    double norm() const {
        return sqrt(x * x + y * y);
    }
};

int dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

bool operator ==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

bool operator <(const Point &a, const Point &b) {
    return a.x * b.y < b.x * a.y;
}


const int N = 100000;

int n;
vector <pair <Point, Point> > segments;
vector <pair <pair <Point, int>, int> > order;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        Point a, b;
        scanf("%d%d%d%d", &a.x, &a.y, &b.x, &b.y);
        if (a == b) {
            continue;
        }
        segments.push_back(make_pair(a, b));
    }
    n = segments.size();
    for (int i = 0; i < n; ++ i) {
        Point normal = (segments[i].second - segments[i].first).slope();
        order.push_back(make_pair(make_pair(normal, dot(segments[i].first, normal.rotate())), i));
    }
    sort(order.begin(), order.end());
//for (int i = 0; i < n; ++ i) {
//    printf("<(%d, %d), %d>, %d\n", order[i].first.first.x, order[i].first.first.y, order[i].first.second, order[i].second);
//}
    double result = 0.0;
    for (int low = 0; low < (int)order.size(); ++ low) {
        int high = low;
        while (high < (int)order.size() && order[low].first == order[high].first) {
            high ++;
        }
        Point normal = order[low].first.first;
        //printf(">> %d, %d\n", normal.x, normal.y);
        vector <pair <int, int> > intervals;
        for (int i = low; i < high; ++ i) {
            int id = order[i].second;
            int a = dot(segments[id].first, normal);
            int b = dot(segments[id].second, normal);
            if (a > b) {
                swap(a, b);
            }
            intervals.push_back(make_pair(a, b));
        }
        sort(intervals.begin(), intervals.end());
        //for (int i = 0; i < (int)intervals.size(); ++ i) {
        //    printf("%d, %d\n", intervals[i].first, intervals[i].second);
        //}
        //puts("");
        int begin = INT_MIN;
        int end = INT_MIN;
        double norm = normal.norm();
        for (int i = 0; i < (int)intervals.size(); ++ i) {
            if (intervals[i].first > end) {
                result = max(result, (end - begin) / norm);
                begin = intervals[i].first;
                end = intervals[i].second;
            } else {
                end = max(end, intervals[i].second);
            }
        }
        result = max(result, (end - begin) / norm);
        low = high - 1;
    }
    printf("%.6f\n", result);
    return 0;
}
