#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

const double EPSILON = 1e-9;

int signum(double x) {
    return x < -EPSILON? -1: x > EPSILON;
}

bool equality(double x, double y) {
    return signum(x - y) == 0;
}

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    double norm() const {
        return sqrt(x * x + y * y);
    }

    bool onLine(const Point &a, const Point &b) const;
    Point project(const Point &a, const Point &b) const;
    Point reflect(const Point &a, const Point &b) const;
};

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y;
}

ostream &operator <<(ostream &out, Point &p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

Point operator +(const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator *(const Point &a, double scale) {
    return Point(a.x * scale, a.y * scale);
}

Point operator /(const Point &a, double scale) {
    return Point(a.x / scale, a.y / scale);
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

bool Point::onLine(const Point &a, const Point &b) const {
    if (signum(det(a - *this, b - *this)) != 0) {
        return false;
    }
    return signum(dot(a - *this, b - *this)) <= 0;
}

Point Point::project(const Point &a, const Point &b) const {
    return a + (b - a) * (dot(*this - a, b - a) / dot(b - a, b - a));
}

Point Point::reflect(const Point &a, const Point &b) const {
    Point p = this->project(a, b);
    return p * 2 - *this;
}

Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    double areaABC = det(b - a, c - a);
    double areaABD = det(b - a, d - a);
    return (c * areaABD - d * areaABC) / (areaABD - areaABC);
}

vector <Point> polygon;
vector <vector <pair <double, int> > > events;

int main() {
    int n;
    cin >> n;
    polygon.resize(n + 1);
    for (int i = 0; i < n; ++ i) {
        cin >> polygon[i];
    }
    polygon[n] = polygon[0];
    Point source;
    cin >> source;
    events.resize(n);
    for (int i = 0; i < n; ++ i) {
        vector <double> ends;
        for (int j = 0; j < n; ++ j) {
            if (signum(det(polygon[j] - source, polygon[i + 1] - polygon[i])) != 0) {
                Point p = intersect(source, polygon[j], polygon[i], polygon[i + 1]);
                if (p.onLine(polygon[i], polygon[i + 1])) {
                    ends.push_back((p - polygon[i]).norm() / (polygon[i + 1] - polygon[i]).norm());
                }
            }
        }
        sort(ends.begin(), ends.end());
        ends.erase(unique(ends.begin(), ends.end(), equality), ends.end());
        double minValid = 2.0;
        double maxValid = -1.0;
        for (int j = 1; j < (int)ends.size(); ++ j) {
            Point p = polygon[i] + (polygon[i + 1] - polygon[i]) * ((ends[j - 1] + ends[j]) / 2.0);
            bool valid = true;
            for (int k = 0; k < n; ++ k) {
                if (signum(det(p - source, polygon[k + 1] - polygon[k])) != 0) {
                    Point q = intersect(source, p, polygon[k], polygon[k + 1]);
                    if (q.onLine(source, p) && q.onLine(polygon[k], polygon[k + 1]) && !p.onLine(polygon[k], polygon[k + 1])) {
                        valid = false;
                    }
                }
            }
            if (valid) {
                minValid = min(minValid, ends[j - 1]);
                maxValid = max(maxValid, ends[j]);
            }
        }
        if (signum(minValid - maxValid) <= 0) {
            events[i].push_back(make_pair(minValid, 1));
            events[i].push_back(make_pair(maxValid, -1));
            Point image = source.reflect(polygon[i], polygon[i + 1]);
            ends.clear();
            ends.push_back(minValid);
            ends.push_back(maxValid);
            for (int j = 0; j < n; ++ j) {
                if (signum(det(polygon[j] - image, polygon[i + 1] - polygon[i])) != 0) {
                    Point p = intersect(image, polygon[j], polygon[i], polygon[i + 1]);
                    double lambda = (p - polygon[i]).norm() / (polygon[i + 1] - polygon[i]).norm();
                    if (signum(minValid - lambda) <= 0 && signum(lambda - maxValid) <= 0) {
                        ends.push_back(lambda);
                    }
                }
            }
            sort(ends.begin(), ends.end());
            ends.erase(unique(ends.begin(), ends.end(), equality), ends.end());
            for (int j = 1; j < (int)ends.size(); ++ j) {
                Point p = polygon[i] + (polygon[i + 1] - polygon[i]) * ((ends[j - 1] + ends[j]) / 2.0);
                int id = -1;
                Point closest = p;
                for (int k = 0; k < n; ++ k) {
                    if (signum(det(p - image, polygon[k + 1] - polygon[k])) != 0) {
                        Point q = intersect(image, p, polygon[k + 1], polygon[k]);
                        if (signum((p - image).norm() - (q - image).norm()) < 0 && p.onLine(image, q) && q.onLine(polygon[k], polygon[k + 1])) {
                            if (id == -1 || signum((q - image).norm() - (closest - image).norm()) < 0) {
                                id = k;
                                closest = q;
                            }
                        }
                    }
                }
                Point u = polygon[i] + (polygon[i + 1] - polygon[i]) * ends[j - 1];
                u = intersect(image, u, polygon[id], polygon[id + 1]);
                Point v = polygon[i] + (polygon[i + 1] - polygon[i]) * ends[j];
                v = intersect(image, v, polygon[id], polygon[id + 1]);
                vector <double> scales;
                scales.push_back((u - polygon[id]).norm() / (polygon[id + 1] - polygon[id]).norm());
                scales.push_back((v - polygon[id]).norm() / (polygon[id + 1] - polygon[id]).norm());
                sort(scales.begin(), scales.end());
                events[id].push_back(make_pair(scales[0], 1));
                events[id].push_back(make_pair(scales[1], -1));
            }
        }
    }
    double result = 0;
    for (int i = 0; i < n; ++ i) {
        events[i].push_back(make_pair(0.0, 0));
        events[i].push_back(make_pair(1.0, 0));
        sort(events[i].begin(), events[i].end());
        int coverCount = events[i].front().second;
        for (int j = 1; j < (int)events[i].size(); ++ j) {
            if (coverCount == 0) {
                result += (events[i][j].first - events[i][j - 1].first) * (polygon[i + 1] - polygon[i]).norm();
            }
            coverCount += events[i][j].second;
        }
    }
    printf("%.7f\n", result);
    return 0;
}
