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

int main()
{
    int k, r, n;
    int sum = 0;
    scanf("%d%d%d", &k, &r, &n);
    for (int i = 0; i < n; i++) {
        int xi;
        scanf("%d", &xi);
        sum += xi <= k ? r - (k - xi) : 2 * r;
    }
    printf("%d\n", sum);
}
