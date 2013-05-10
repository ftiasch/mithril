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
    int n, cap;
    scanf("%d%d", &n, &cap);
    int sum = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        int ai;
        scanf("%d", &ai);
        sum += ai;
        if (sum >= cap) {
            sum = 0;
            cnt ++;
        }
    }
    printf("%d\n", cnt);
}
