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

int a[maxn];
int n;

long long opt[maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    sort(a, a + n);
    opt[0] = 0;
    for (int i = 0; i < n; i++) {
        opt[i + 1] = max(opt[i], a[i] - opt[i]);
    }
    cout << opt[n] << endl;
}
