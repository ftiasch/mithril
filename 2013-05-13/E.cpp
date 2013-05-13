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

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

const double PI = acos(-1.);
const double EPS = 1e-11;

int main()
{
    int w, h, offsetX, offsetY, scale, rotAngle;
    while (cin >> w >> h >> offsetX >> offsetY >> scale >> rotAngle) {
        if (scale == 0) {
            break;
        }
        complex<double> now = 0;
        complex<double> rot, offset;
        rot.imag() = sin(rotAngle / 180.0 * PI);
        rot.real() = cos(rotAngle / 180.0 * PI);
        offset.imag() = offsetY;
        offset.real() = offsetX;
        /*for (int it = 0; it < 500; ++it) {
            now = now * rot * (scale * 0.01);
            now.imag() += offsetY;
            now.real() += offsetX;
        }*/
        // now = now * rot * (scale * 0.01) + offset
        now = -offset / (rot * (scale * 0.01) - 1.0);
        printf("%.2f %.2f\n", now.real() + EPS, now.imag() + EPS);
    }
}
