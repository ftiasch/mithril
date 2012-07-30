#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 40;
const int DELTA[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

int solveGCD(int a, int b) {
    return b == 0? a: solveGCD(b, a % b);
}

int gcd[51][51];

struct Fraction {
    int a, b;

    Fraction(int x = 0, int y = 1): a(x), b(y) {
        int d = gcd[abs(a)][abs(b)];
        assert(d != 0);
        a /= d;
        b /= d;
    }
};

ostream &operator <<(ostream &out, Fraction &f) {
    return out << f.a << "/" << f.b;
}

bool operator <(const Fraction &x, const Fraction &y) {
    if (x.b==0 && y.b==0){
        return x.a<y.a;
    }
    return x.a * y.b < y.a * x.b;
}

typedef pair <Fraction, int> Pair;

int n, m, weight[N][N];
vector <Pair> events;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= 50; ++ i) {
        for (int j = 0; j <= 50; ++ j) {
            gcd[i][j] = solveGCD(i, j);
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            scanf("%d", &weight[i][j]);
        }
    }
    long long result = 0;
    for (int i = 0; i + 1 < n; ++ i) {
        long long counter = 0;
        for (int j = 0; j < m; ++ j) {
            counter += weight[i][j] + weight[i + 1][j];
        }
        result = max(result, counter);
    }
    for (int x_0 = 0; x_0 <= n; ++ x_0) {
        for (int y_0 = 0; y_0 <= m; ++ y_0) {
            events.clear();
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < m; ++ j) {
                    Fraction minAlpha = Fraction(1, 0);
                    Fraction maxAlpha = Fraction(-1, 0);
                    for (int k = 0; k < 4; ++ k) {
                        int x = i - x_0 + DELTA[k][0];
                        int y = j - y_0 + DELTA[k][1];
                        if (i < x_0) {
                            x *= -1;
                            y *= -1;
                        }
                        if (x != 0 || y != 0) {
                            Fraction alpha = Fraction(y, x);
                            minAlpha = min(minAlpha, alpha);
                            maxAlpha = max(maxAlpha, alpha);
                        } else {
                            minAlpha = min(minAlpha, Fraction(-1,0));
                            maxAlpha = max(maxAlpha, Fraction(1,0));
                        }
                    }
                    events.push_back(make_pair(minAlpha, -weight[i][j]));
                    events.push_back(make_pair(maxAlpha, weight[i][j]));
                }
            }
            sort(events.begin(), events.end());
            long long counter = 0;
            for (int i = (int)events.size() - 1; i >= 0; -- i) {
                counter += events[i].second;
                result = max(result, counter);
            }
        }
    }
    cout << result << endl;
    return 0;
}
