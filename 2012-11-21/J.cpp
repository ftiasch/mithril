#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;
const int LIMIT = 100;

double a, b, w, h;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

double get_height(double theta) {
    return a * cos(theta) + b * sin(theta);
}

double get_width(double theta) {
    return a * sin(theta) + b * cos(theta);
}

bool checkJB(int a, int b, int h, int w) {
    if (signum(a - w) < 0) {
        double cosAng = (double)a / w;
        double sinAng = sqrt(1 - cosAng * cosAng);
        double h2 = sinAng * a;
        if (signum(h2 * 2 - h) <= 0) {
            double all = (h - h2) / cosAng;
            if (signum(all - b) >= 0) {
                return true;
            }
        }
    }
    return false;
}

bool check(int a, int b, int w, int h) {
    ::a = a, ::b = b, ::w = w, ::h = h;
    double phi = atan((double)a / b);
    double low = 0;
    double high = PI / 2 - phi;
    for (int _ = 0; _ < LIMIT; ++ _) {
        double middle = (low + high) / 2.0;
        if (get_height(middle) <= h) {
            low = middle;
        } else {
            high = middle;
        }
    }
    if (signum(get_height(low) - h) > 0) {
        return false;
    }
    return signum(get_width(0) - w) <= 0 || signum(get_width(low) - w) <= 0;
}

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    int n;
    scanf("%d", &n);
    while (n --) {
        int w, h;
        scanf("%d%d", &h, &w);
        if (check(a, b, w, h) || check(a, b, h, w) || check(b, a, w, h) || check(b, a, h, w) || checkJB(a, b, h, w) || checkJB(b, a, h, w)) {
            puts("Block the hole");
        } else {
            puts("Too small");
        }
    }
    return 0;
}
