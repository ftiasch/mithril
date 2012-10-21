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

bool query(int a, int b)
{
    printf("1 %d %d\n", a, b);
    fflush(stdout);
    static char buf[128];
    scanf("%s", buf);
    return strcmp(buf, "YES") == 0;
}

vector<int> solve(int l, int r)
{
    if (l == r) {
        return vector<int>(1, l);
    }
    int m = (l + r) / 2;
    vector<int> lhs = solve(l, m);
    vector<int> rhs = solve(m + 1, r);
    vector<int> ret;
    int i = 0, j = 0;
    while (i < lhs.size() && j < rhs.size()) {
        if (query(lhs[i], rhs[j])) {
            ret.push_back(lhs[i++]);
        } else {
            ret.push_back(rhs[j++]);
        }
    }
    while (i < lhs.size()) {
        ret.push_back(lhs[i++]);
    }
    while (j < rhs.size()) {
        ret.push_back(rhs[j++]);
    }
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> res = solve(1, n);
    printf("0");
    for (int i = 0; i < res.size(); i++) {
        printf(" %d", res[i]);
    }
    puts("");
    fflush(stdout);
    return 0;
}
