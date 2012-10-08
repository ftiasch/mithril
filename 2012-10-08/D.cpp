#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

// 15 * 1
// 7 * 2
// 5 * 3

const long long RESULT[3][2] = {{2LL, 20922789888000LL},
                                {90LL, 1197104804LL},
                                {2664LL, 21594814509800LL}};

int n, m;

long long gcd(long long a, long long b) {
    return b == 0? a: gcd(b, a % b);
}

int main() {
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    scanf("%d%d", &n, &m);
    bool reversed = false;
    if (n > m) {
        reversed = true;
        swap(n, m);
    }
    long long x = RESULT[n - 1][1];
    long long y = RESULT[n - 1][0];
    if (reversed) {
        swap(x, y);
        swap(n, m);
    }
    cout << x << " " << y << endl;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            assert(gcd(x + i, y + j) > 1);
        }
    }
    return 0;
}
