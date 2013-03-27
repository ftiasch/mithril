#include <cmath>
#include <cstdio>
#include <cstring>
#include <complex>
#include <vector>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

typedef std::complex <double> Point;

const int N = 70;
const double EPS = 1e-8;
const double PI = acos(-1.0);

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

int n;
Point points[N << 1];

double det(const Point &a, const Point &b) {
    return a.real() * b.imag() - a.imag() * b.real();
}

Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    double s_1 = det(b - a, c - a);
    double s_2 = det(b - a, d - a);
    return (s_2 * c - s_1 * d) / (s_2 - s_1);
}

bool point_comparasion(const Point &a, const Point &b) {
    if (signum(a.real() - b.real()) == 0) {
        return signum(a.imag() - b.imag()) < 0;
    }
    return signum(a.real() - b.real()) < 0;
}

bool point_equality(const Point &a, const Point &b) {
    return signum(a.real() - b.real()) == 0 && signum(a.imag() - b.imag()) == 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n << 1; ++ i) {
        int x, y;
        scanf("%d%d", &x, &y);
        points[i] = Point(x, y);
    }
    std::vector <Point> centers;
    for (int i = 1; i < n << 1; ++ i) {
        int j = 1;
        if (j == i) {
            j ++;
        }
        for (int k = 1; k < n << 1; ++ k) {
            if (k != i && k != j) {
                if (signum(det(points[i] - points[0], points[k] - points[j])) != 0) {
                    centers.push_back(intersect(points[0], points[i], points[j], points[k]));
                }
            }
        }
    }
    std::sort(centers.begin(), centers.end(), point_comparasion);
    centers.erase(std::unique(centers.begin(), centers.end(), point_equality), centers.end());
    int count = 0;
    Point answer;
    foreach (iter, centers) {
        Point c(*iter);
        bool valid = true;
        std::vector <double> args;
        for (int i = 0; i < n << 1 && valid; ++ i) {
            if (point_equality(c, points[i])) {
                valid = false;
            } else {
                double ret = std::arg(points[i] - c);
                if (signum(ret) <= 0) {
                    ret += PI;
                }
                args.push_back(ret);
            }
        }
        if (valid) {
            std::sort(args.begin(), args.end());
            for (int i = 0; i < (int)args.size() && valid; i += 2) {
                valid &= signum(args[i] - args[i + 1]) == 0;
                if (i + 2 < (int)args.size()) {
                    valid &= signum(args[i] - args[i + 2]) != 0;
                }
            }
        }
        count += valid;
        if (valid) {
            answer = c;
        }
    }
    if (count == 0) {
        puts("Impossible");
    } else if (count > 1) {
        puts("Ambiguity");
    } else {
        printf("Center of the universe found at (%.10f, %.10f)", answer.real(), answer.imag());
    }
    return 0;
}
