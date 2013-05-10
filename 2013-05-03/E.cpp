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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

#define double long double

const double EPS = 1e-5;
const double PI = acosl(-1.0);

inline double det(double x1, double y1, double x2, double y2)
{
    return x1 * y2 - x2 * y1;
}

struct Point
{
    double x, y, z;

    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z){}

    inline double norm2() {
        return x * x + y * y + z * z;
    }

    inline double norm() {
        return sqrtl(norm2());
    }

    Point &operator+=(const Point &o) {
        return x += o.x, y += o.y, z += o.z, *this;
    }

    Point &operator-=(const Point &o) {
        return x -= o.x, y -= o.y, z -= o.z, *this;
    }

    Point &operator*=(double scale) {
        return x *= scale, y *= scale, z *= scale, *this;
    }
    
    Point &operator/=(double scale) {
        return x /= scale, y /= scale, z /= scale, *this;
    }

    Point operator+(const Point &o) const {
        return Point(x + o.x, y + o.y, z + o.z);
    }

    Point operator-(const Point &o) const {
        return Point(x - o.x, y - o.y, z - o.z);
    }

    Point operator*(double scale) const {
        return Point(x * scale, y * scale, z * scale);
    }

    double dot(const Point &o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    Point det3(const Point &o) const {
        return Point(det(y, z, o.y, o.z), det(z, x, o.z, o.x), det(x, y, o.x, o.y));
    }

    Point &normalize() {
        return *this /= norm();
    }

    void read() {
        cin >> x >> y >> z;
    }

    void print() {
        cerr << "(" << x << " " << y << " " << z << ")";
    }

    Point rot90() const {
        if (fabs(z) + fabs(y) > EPS) {
            return Point(0, -z, y);
        }
        return Point(0, 1, 1);
    }
};

const int maxn = 222;

int n;
Point pts[maxn];

inline double norm360(double a)
{
    while (a < -EPS) {
        a += 2 * PI;
    }
    a = fmodl(a, 2 * PI);
    if (a >= 2 * PI - EPS * 2) {
        a = 0;
    }
    return a;
}

struct PointOnSurface
{
    double lat, lng;

    PointOnSurface(double a, double b) : lat(a), lng(norm360(b)) {}

    bool operator<(const PointOnSurface &o) const {
        return lat + EPS < o.lat || lat < o.lat + EPS && lng + EPS < o.lng;
    }

    void print() {
        cerr << "[" << lat / PI * 100 << " " << lng / PI * 180 << "]";
    }
};

vector<PointOnSurface> newNorthPole(int north)
{
    Point Z = pts[north];
    Point X = Z.det3(Z.rot90()).normalize();
    Point Y = Z.det3(X).normalize();
    vector<PointOnSurface> ret;
    for (int i = 0; i < n; i++) {
        if (i == north) {
            continue;
        }
        Point np = Point(pts[i].dot(X), pts[i].dot(Y), pts[i].dot(Z));
        if (fabs(np.z + 1) < EPS) {
            // ignore south pole
            continue;
        }
        ret.push_back(PointOnSurface(asinl(np.z), atan2l(np.y, np.x) + 0.1132133213312));
    }
    return ret;
}

bool double_equal(double a, double b)
{
    return fabs(a - b) < EPS;
}

int solve(vector<PointOnSurface> a, vector<PointOnSurface> b)
{
    if (a.size() != b.size()) {
        return 0;
    }
//for (int i = 0; i < a.size(); i++) {
//    a[i].print(), putchar(' ');
//    b[i].print(), puts("");
//}
    set<PointOnSurface> S;
    for (int i = 0; i < b.size(); i++) {
        S.insert(b[i]);
    }
    if (a.size() == 0) {
        return 1;
    }
    int ret = 0;
    for (int i = 0; i < b.size(); i++) {
        if (fabs(b[i].lat - a[0].lat) > EPS) {
            continue;
        }
        double delta = b[i].lng - a[0].lng;
        bool valid = true;
        for (int j = 0; j < a.size(); j++) {
            if (!S.count(PointOnSurface(a[j].lat, a[j].lng + delta))) {
                valid = false;
                break;
            }
        }
        if (valid) {
            ret ++;
        }
    }
//cerr << ret << endl;
    return ret;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        pts[i].read();
        pts[i].normalize();
    }
    vector<PointOnSurface> ref = newNorthPole(0);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += solve(ref, newNorthPole(i));
    }
    cout << ans << endl;
}
