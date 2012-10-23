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

const int INF = 1000000000;

int main()
{
    unsigned long long n, k;
    while (cin >> n >> k && n) {
        unsigned long long p10 = 1;
        vector<string> S;
        while (true) {
            unsigned long long z = (p10 + k - 1) / k * k;
            if (z <= n) {
                ostringstream ssout;
                ssout << z;
                S.push_back(ssout.str());
            } else {
                break;
            }
            if (p10 / INF == INF) {
                break;
            }
            p10 *= 10;
        }
        sort(S.begin(), S.end());
        cout << S[0] << endl;
    }
}
