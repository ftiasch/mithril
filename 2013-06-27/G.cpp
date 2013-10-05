#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

typedef long long Long;

struct Fraction {
    Long p, q;

    Fraction() : p(0), q(1) {}

    Fraction(Long p, Long q) : p(p), q(q) {
        Long g = std::__gcd(p, q);
        this->p /= g;
        this->q /= g;
    }

    long double double_value() const {
        return (long double)p / q;
    }
};

Fraction operator *(const Fraction &a, const Fraction &b) {
    return Fraction(a.p * b.p, a.q * b.q);
}

bool operator < (const Fraction &a, const Fraction &b) {
    return a.double_value() < b.double_value();
}

std::vector <std::string> maps;
std::map <std::string, int> names;

int get_id(std::string name) {
    if (names.count(name)) {
        return names[name];
    }
    int new_id = names.size();
    maps.push_back(name);
    return names[name] = new_id;
}

const int N = 8;

Fraction graph[N][N];

int main() {
    int test_count = 0;
    int m;
    while ((std::cin >> m) && m) {
        printf("Case %d: ", ++ test_count);
        maps.clear();
        names.clear();
        for (int i = 0; i < N; ++ i) {
            for (int j = 0; j < N; ++ j) {
                graph[i][j] = Fraction();
            }
        }
        for (int i = 0; i < m; ++ i) {
            int x, y;
            std::string a, b, c;
            std::cin >> x >> a >> c >> y >> b;
            graph[get_id(a)][get_id(b)] = Fraction(y, x);
            graph[get_id(b)][get_id(a)] = Fraction(x, y);
        }
        int n = names.size();
        for (int k = 0; k < n; ++ k) {
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < n; ++ j) {
                    if (graph[i][j].p == 0) {
                        graph[i][j] = graph[i][k] * graph[k][j];
                    }
                }
            }
        }
        int need;
        std::string a;
        std::cin >> need >> a;
        double minimum = 1e100;
        int amount = 0;
        int id = -1;
        for (int i = 0; i < n; ++ i) {
            if (i != get_id(a) && graph[i][get_id(a)].p != 0) {
                int y = ceil(need / graph[i][get_id(a)].double_value());
                if (y <= 100000) {
                    double got = y * graph[i][get_id(a)].double_value();
                    if (got >= need && got < minimum) {
                        minimum = got;
                        amount = y;
                        id = i;
                    }
                }
            }
        }
//printf("%d\n", id);
        printf("%d %s\n", amount, maps[id].c_str());
    }
    return 0;
}
