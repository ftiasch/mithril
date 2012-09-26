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

const double pi = acos(-1.);

double get(double r, double x)
{
    return r * r * x - x * x * x / 3;
}

int main()
{
    double R, H;
    while (cin >> R >> H) {
        double right = 0;
        if (H / 2 < R) {
            right = sqrt(R * R - (H / 2) * (H / 2));
        }
        double ans = get(R, R) - get(R, right);
        ans += (H / 2) * (H / 2) * right;
        ans = pi * R * R * H * 2 - ans * 8;
        printf("%.4f\n", ans + 1e-11);
    }
}
