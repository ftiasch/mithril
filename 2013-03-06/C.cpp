#include <cmath>
#include <cstdio>
#include <cstring>
#include <complex>
#include <utility>
#include <algorithm>

using std::abs;

const int N = 10000;
const double EPS = 1e-8;
const double PI = acos(-1.0);

typedef std::complex <double> Point;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

int n, m;
double r[N], result[N];
Point c[N];

double det(const Point &a, const Point &b) {
    return a.real() * b.imag() - a.imag() * b.real();
}

Point polar(double t) {
    return Point(cos(t), sin(t));
}

Point radius(int i, double t) {
    return c[i] + polar(t) * r[i];
}

std::pair <double, int> events[N];

void add_event(double a, int v) {
    events[m ++] = std::make_pair(a, v);
}

void add_pair(double a, double b) {
    if (signum(a - b) <= 0) {
        add_event(a, 1);
        add_event(b, -1);
    } else {
        add_pair(a, PI);
        add_pair(-PI, b);
    }
}

void solve() {
    memset(result, 0, sizeof(result));
    for (int i = 0; i < n; ++ i) {
        m = 0;
        add_event(-PI, 0);
        add_event(PI, 0);
        for (int j = 0; j < n; ++ j) {
            if (i != j) {
                if (signum(abs(c[i] - c[j]) - abs(r[i] - r[j])) <= 0) {
                    if (signum(r[i] - r[j]) <= 0) {
                        add_pair(-PI, PI);
                    } 
                } else {
                    if (signum(abs(c[i] - c[j]) - (r[i] + r[j])) >= 0) {
                        continue;
                    }
                    double d = abs(c[j] - c[i]);
                    Point b = (c[j] - c[i]) / d * r[i];
                    double t = acos(std::max(std::min((r[i] * r[i] + d * d - r[j] * r[j]) / (2 * r[i] * d), 1.0), -1.0));
                    Point a = b * polar(-t);
                    Point c = b * polar(t);
                    add_pair(arg(a), arg(c));
                }
            }
        }
        std::sort(events, events + m);
        int count = events[0].second;
        for (int j = 1; j < m; ++ j) {
            double delta = events[j].first - events[j - 1].first;
            result[count] += r[i] * r[i] * (delta - sin(delta));
            result[count] += det(radius(i, events[j - 1].first), radius(i, events[j].first));
            count += events[j].second;
        }
    }
}

double answer[2];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        double x, y;
        scanf("%lf%lf%lf", &x, &y, r + i);
        c[i] = Point(x, y);
    }
    solve();
    memset(answer, 0, sizeof(answer));
    for (int i = 0; i <= n; ++ i) {
        answer[i & 1] += result[i];
        if (i + 1 < n) {
            answer[i & 1] -= result[i + 1];
        }
    }
    printf("%.5f %.5f\n", answer[0] * 0.5, answer[1] * 0.5);
    return 0;
}
