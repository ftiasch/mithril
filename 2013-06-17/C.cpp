#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define SIZE(v) ((int)(v).size())

const int N = 100000;

int n, a[N], b[N];
std::pair <int, int> intevals[N];

struct Fraction {
    int p, q;

    Fraction(int p, int q) : p(p), q(q) {}
};

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    Point &operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    Fraction slope() const {
        return Fraction(y, x);
    }
};

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

Point operator -(Point a, const Point &b) {
    return a -= b;
}

bool check(const Point &a, const Point &b, const Point &c) {
    return det(b - a, c - b) < 0;
}

bool operator < (const Fraction &a, const Fraction &b) {
    return (long long)a.p * b.q < (long long)b.p * a.q;
}

int main() {
    freopen("caravan.in", "r", stdin);
    freopen("caravan.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &intevals[i].first, &intevals[i].second);
    }
    std::sort(intevals, intevals + n);
    for (int i = 0; i < n; ++ i) {
        a[i] = intevals[i].first;
        b[i] = intevals[i].second;
    }
    std::vector <Point> stack;
    Fraction answer(1, 0);
    for (int i = 0; i < n; ++ i) {
        // add (i, a[i])
        Point p(i, a[i]);
        while (SIZE(stack) >= 2 && !check(stack[SIZE(stack) - 2], stack.back(), p)) {
            stack.pop_back();
        }
        stack.push_back(p);
        // query (i + 1, b[i])
        Point q(i + 1, b[i]);
        int low = 0;
        int high = SIZE(stack) - 1;
        while (low < high) {
            int middle = low + high + 1 >> 1;
            if (det(stack[middle] - stack[middle - 1], q - stack[middle]) <= 0) {
                low = middle;
            } else {
                high = middle - 1;
            }
        }
        Point &r = stack[low];
        answer = std::min(answer, (q - r).slope());
    }
    int p = answer.p;
    int q = answer.q;
    int g = std::__gcd(p, q);
    printf("%d/%d\n", p / g, q / g);
    return 0;
}
