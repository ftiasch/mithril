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

const int maxn = 111111;
const int inf = 1000000010;

int n, k;
int a[maxn];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    multiset<int> S(a, a + n);
    vector<int> ans;
    int sum = 0;
    while (ans.size() < k) {
        multiset<int>::iterator it = S.upper_bound(sum + 1);
        if (it == S.begin()) {
            ans.push_back(*it);
            S.erase(it);
        } else {
            --it;
            ans.push_back(*it);
            sum += *it;
            sum = min(sum, inf);
            S.erase(it);
        }
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", ans[i]);
    }
    puts("");
}
