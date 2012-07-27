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

int main()
{
    double h, r, s;
    int m;
    while (cin >> h >> r >> s >> m) {
        double H = sqrt(h * h + r * r) * (s / h);
        for (int i = m; i > 0; i--) {
            double res = pow((double)i / m, 1.0 / 3.0) * H;
            printf("%.10f\n", res);
        }
    }
}
