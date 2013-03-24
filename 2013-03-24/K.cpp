#include <cstdio>
#include <cstring>
#include <complex>
#include <vector>
#include <utility>
#include <algorithm>

const int N = 100000;
const double EPS = 1e-9;
const double PI = acos(-1.0);

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

typedef std::complex <double> Point;

int n;
Point points[N];

bool by_norm(const Point &a, const Point &b) {
    return signum(std::abs(a) - std::abs(b)) < 0;
}

bool by_arg(const Point &a, const Point &b) {
    return signum(std::arg(a) - std::arg(b)) < 0;
}

int circle_count;

double det(const Point &a, const Point &b) {
    return a.real() * b.imag() - a.imag() * b.real();
}

double dot(const Point &a, const Point &b) {
    return a.real() * b.real() + a.imag() * b.imag();
}

double turn(const Point &a, const Point &b) {
    double ret = atan2(det(a, b), dot(a, b));
    if (signum(ret) < 0) {
        return 2 * PI + ret;
    }
    return ret;
}

std::vector <std::pair <double, int> > axises;
int flag[N];

std::vector <int> manacher(const std::vector <double> &string) {
    int n = string.size();
    std::vector <int> length((n << 1) - 1, 0);
    length[0] = 1;
    for (int i = 1, j = 0; i < (n << 1) - 1; ++ i) {
        int p = i >> 1;
        int q = i - p;
        int r = (j + 1 >> 1) + length[j] - 1;
        length[i] = r < q ? 0 : std::min(r - q + 1, length[(j << 1) - i]);
        while (p - length[i] >= 0 && q + length[i] < n && signum(string[p - length[i]] - string[q + length[i]]) == 0) {
            length[i] ++;
        }
        if (q + length[i] - 1 > r) {
            j = i;
        }
    }
    return length;
}

double my_arg(const Point &p) {
    double ret = std::arg(p);
    if (signum(ret) <= 0) {
        ret += PI;
    }
    return ret;
}

void find_axis(Point* points, int n) {
    if (n == 1) {
        if (signum(std::abs(points[0])) != 0) {
            axises.push_back(std::make_pair(my_arg(points[0]), circle_count ++));
        }
        return;
    }
    std::sort(points, points + n, by_arg);
    std::vector <double> angles;
    for (int i = 0; i < n; ++ i) {
        angles.push_back(turn(points[i], points[(i + 1) % n]));
    }
    for (int k = 0; k < 2; ++ k) {
        for (int i = 0; i < n; ++ i) {
            angles.push_back(angles[i]);
        }
    }
    std::vector <int> length = manacher(angles);
    for (int i = 0; i < n; ++ i) {
        if (length[(n + i << 1) - 1] >= n) {
            axises.push_back(std::make_pair(my_arg(points[i]), circle_count));
        }
    }
    for (int i = 0; i < n; ++ i) {
        if (length[n + i << 1] >= n) {
            double ret = (std::arg(points[i]) + std::arg(points[(i + 1) % n])) / 2.0;
            if (signum(ret) <= 0) {
                ret += PI;
            }
            axises.push_back(std::make_pair(ret, circle_count));
        }
    }
    circle_count ++;
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    while (test_count --) {
        scanf("%d", &n);
        Point center(0.0, 0.0);
        for (int i = 0; i < n; ++ i) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            center += (points[i] = Point(x, y));
        }
        if (n == 1) {
            puts("YES");
            continue;
        }
        center /= n;
        for (int i = 0; i < n; ++ i) {
            points[i] -= center;
        }
        std::sort(points, points + n, by_norm);
//for (int i = 0; i < n; ++ i) {
//    printf("%.5f %.5f\n", points[i].real(), points[i].imag());
//}
        axises.clear();
        circle_count = 0;
        for (int begin = 0; begin < n; ) {
            int end = begin;
            while (end < n && !by_norm(points[begin], points[end])) {
                end ++;
            }
            find_axis(points + begin, end - begin);
            begin = end;
        }
        std::sort(axises.begin(), axises.end());
        bool found = false;
        int flag_count = 0;
        memset(flag, -1, sizeof(flag));
        for (int begin = 0; begin < (int)axises.size(); ) {
            int end = begin;
            while (end < (int)axises.size() && signum(axises[begin].first - axises[end].first) == 0) {
                end ++;
            }
            int left = circle_count;
            for (int i = begin; i < end; ++ i) {
                int &ret = flag[axises[i].second];
                if (ret != flag_count) {
                    left --;
                    ret = flag_count;
                }
            }
            found |= left == 0;
            flag_count ++;
            begin = end;
        }
        puts(found ? "YES" : "NO");
    }
    return 0;
}
