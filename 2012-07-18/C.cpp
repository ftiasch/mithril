#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPS = 1e-9;

int signum(double x) {
    return x < -EPS? -1: x > EPS;
}

bool doubleEqual(double x, double y) {
    return signum(x - y) == 0;
}

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    double norm() const {
        return sqrt(x * x + y * y);
    }

    Point normalize() const {
        return Point(x / norm(), y / norm());
    }

    Point rotate() const {
        return Point(y, -x);
    }
};

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y;
}

ostream &operator <<(ostream &out, Point &p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

bool operator <(const Point &a, const Point &b) {
    if (signum(a.x - b.x) == 0) {
        return signum(a.y - b.y) < 0;
    }
    return signum(a.x - b.x) < 0;
}

Point operator +(const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator *(const Point &a, double k) {
    return Point(a.x * k, a.y * k);
}

Point operator /(const Point &a, double k) {
    return Point(a.x / k, a.y / k);
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

Point intersect(Point n[2], Point m[2]) {
    double areaA = det(n[0] - m[0], m[1] - m[0]);
    double areaB = det(n[1] - m[0], m[1] - m[0]);
    return (n[0] * areaB - n[1] * areaA) / (areaB - areaA);
}

const int N = 10;
const int M = N * (N - 1) / 2;

int n, m;
double maxTime;
Point lineEnds[N][2], newLineEnds[N][2], points[M], velocity[M], currentPoints[M];
vector <double> events;

bool compare(int i, int j) {
    return currentPoints[i] < currentPoints[j];
}

bool check(int i, int j, int k) {
    return signum(det(currentPoints[j] - currentPoints[i], currentPoints[k] - currentPoints[j])) > 0;
}

double solve(double low, double high) {
    double t = (low + high) / 2.0;
    for (int i = 0; i < m; ++ i) {
        currentPoints[i] = points[i] + velocity[i] * t;
    }
    vector <int> order(m);
    for (int i = 0; i < m; ++ i) {
        order[i] = i;
    }
    sort(order.begin(), order.end(), compare);
    vector <int> hull;
    for (int i = 0; i < m; ++ i) {
        while ((int)hull.size() > 1 
                && !check(hull[(int)hull.size() - 2], hull.back(), order[i])) {
            hull.pop_back();
        }
        hull.push_back(order[i]);
    }
    int record = hull.size();
    for (int i = m - 1; i >= 0; -- i) {
        while ((int)hull.size() > record 
                && !check(hull[(int)hull.size() - 2], hull.back(), order[i])) {
            hull.pop_back();
        }
        hull.push_back(order[i]);
    }
    hull.pop_back();
    int h = hull.size();
//for (int i = 0; i < h; ++ i) {
//    cout << currentPoints[hull[i]] << endl;
//}
    double a = 0;
    double b = 0;
    double c = 0;
    for (int i = 0; i < h; ++ i) {
        a += det(velocity[hull[i]], velocity[hull[(i + 1) % h]]);
        b += det(velocity[hull[i]], points[hull[(i + 1) % h]]);
        b += det(points[hull[i]], velocity[hull[(i + 1) % h]]);
        c += det(points[hull[i]], points[hull[(i + 1) % h]]);
    }
    double result = 0;
    result += (high * high * high - low * low * low) * a / 3.0;
    result += (high * high - low * low) * b / 2.0;
    result += (high - low) * c;
    return result;
}

void addEvent(double time) {
    if (signum(0 - time) <= 0 && signum(time - maxTime) <= 0) {
        events.push_back(time);
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 2; ++ j) {
            cin >> lineEnds[i][j];
        }
        double velocity;
        cin >> velocity;
        Point normal = (lineEnds[i][1] - lineEnds[i][0]).normalize().rotate() * velocity;
        for (int j = 0; j < 2; ++ j) {
            newLineEnds[i][j] = lineEnds[i][j] + normal;
        }
    }
    scanf("%lf", &maxTime);
    m = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            if (signum(det(lineEnds[i][0] - lineEnds[i][1], 
                           lineEnds[j][0] - lineEnds[j][1])) != 0) {
                points[m] = intersect(lineEnds[i], lineEnds[j]);
                velocity[m] = intersect(newLineEnds[i], newLineEnds[j]) - points[m];
                m ++;
            }
        }
    }
//for (int i = 0; i < m; ++ i) {
//    cout << points[i] << " " << velocity[i] << endl;
//}
    addEvent(0);
    addEvent(maxTime);
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < i; ++ j) {
            Point pA = points[j] - points[i];
            Point vA = velocity[j] - velocity[i];
            for (int k = 0; k < j; ++ k) {
                Point pB = points[k] - points[i];
                Point vB = velocity[k] - velocity[i];
                double a = det(vA, vB);
                double b = det(vA, pB) + det(pA, vB);
                double c = det(pA, pB);
                if (signum(a) == 0) {
                    if (signum(b) != 0) {
                        double x = -c / b;
                        addEvent(x);
                    }
                } else {
                    double delta = b * b - 4 * a * c;
                    if (signum(delta) >= 0) {
                        if (signum(delta) == 0) {
                            delta = 0;
                        }
                        delta = sqrt(delta);
                        addEvent(-0.5 * (b - delta) / a);
                        addEvent(-0.5 * (b + delta) / a);
                    }
                }
            }
        }
    }
    sort(events.begin(), events.end());
    events.erase(unique(events.begin(), events.end(), doubleEqual), events.end());
//for (int i = 0; i < (int)events.size(); ++ i) {
//    printf("%.10f\n", events[i]);
//}
    double result = 0;
    for (int i = 1; i < (int)events.size(); ++ i) {
        result += solve(events[i - 1], events[i]);
    }
    printf("%.10f\n", 0.5 * result / maxTime);
    return 0;
}
