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

const int maxn = 1 << 20;

int minFactor[maxn];
int counter[maxn];

void add(int p, int delta)
{
    while (p != 1) {
        int f = minFactor[p];
        p /= f;
        counter[f] += delta;
    }
}

int main()
{
    for (int i = 2; i < maxn; i++) {
        minFactor[i] = i;
    }
    for (int i = 2; i * i < maxn; i++) {
        if (minFactor[i] == i) {
            for (int j = i * i; j < maxn; j += i) {
                if (minFactor[j] > i) {
                    minFactor[j] = i;
                }
            }
        }
    }
    int p, q, m;
    cin >> p >> q >> m;
    for (int i = 0; i < p; i++) {
        add(p + q - i, 1);
        add(i + 1, -1);
    }
    add(p + q, -1);
    long long ans = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 0; j < counter[i]; j++) {
            ans = ans * i % m;
        }
    }
    cout << ans << endl;
}
