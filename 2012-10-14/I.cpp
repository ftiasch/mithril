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

const double PI = acos(-1.);
const double EPS = 1e-11;

struct Point
{
    double x, y, z;

    Point(){}

    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    Point(double lat, double lng) :
        x(cos(lat) * sin(lng)),
        y(cos(lat) * cos(lng)),
        z(sin(lat)) {}

    Point operator+(const Point &o) const {
        return Point(x + o.x, y + o.y, z + o.z);
    }

    Point operator-(const Point &o) const {
        return Point(x - o.x, y - o.y, z - o.z);
    }

    Point operator*(double scale) const {
        return Point(x * scale, y * scale, z * scale);
    }

    Point operator/(double scale) const {
        return Point(x / scale, y / scale, z / scale);
    }

    double norm() const {
        return sqrt(x * x + y * y + z * z);
    }

    Point normalize() const {
        return *this / norm();
    }

    Point det(const Point &o) const {
        return Point(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }

    double dot(const Point &o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    double angleWith(const Point &o) const {
        return acos(dot(o) / norm() / o.norm());
    }

    void show() {
        printf("(%.3f %.3f %.3f)", x, y, z);
    }
};

int main()
{
    double H, R, lat0, lng0, lat1, lng1;
    while (cin >> R >> H >> lat0 >> lng0 >> lat1 >> lng1) {
        double latLimit = acos(R / (R + H));
        double zLimit = sin(latLimit);
        const int times = 1 << 10;
        Point start(lat0, lng0), finish(lat1, lng1);
        Point X = start;
        Point Z = start.det(finish).normalize();
        Point Y = Z.det(X).normalize();
        double ang = start.angleWith(finish);
        double sum = 0;
        for (int i = 0; i < times; i++) {
            double lBound = ang * i / times;
            double rBound = ang * (i + 1) / times;
#define CHECK(a) ((X * cos(a) + Y * sin(a)).z <= zLimit + EPS)
            bool lFlag = CHECK(lBound);
            bool rFlag = CHECK(rBound);
            if (lFlag == rFlag) {
                if (lFlag) {
                    sum += rBound - lBound;
                }
            } else {
                double lo = lBound, hi = rBound;
                for (int it = 0; it < 100; ++it) {
                    double mid = (lo + hi) * 0.5;
                    if (CHECK(mid) == lFlag) {
                        lo = mid;
                    } else {
                        hi = mid;
                    }
                }
                if (lFlag) {
                    sum += lo - lBound;
                } else {
                    sum += rBound - hi;
                }
            }
        }
        double percent = sum / ang * 100;
        printf("%.3f\n", percent);
    }
}
