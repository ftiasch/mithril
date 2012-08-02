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
#include <climits>
using namespace std;

int main()
{
    int n, m;
    while (cin >> n >> m) {
        vector<pair<int,int> > fs;
        for (int i = 2; i * i <= m; i++) {
            if (m % i == 0) {
                int cnt = 0;
                while (m % i == 0) {
                    m /= i;
                    cnt ++;
                }
                fs.push_back(make_pair(i, cnt));
            }
        }
        if (m > 1) {
            fs.push_back(make_pair(m, 1));
        }
        int ret = INT_MAX;
        for (int i = 0; i < fs.size(); i++) {
            int sum = 0, tmp = n;
            while (tmp /= fs[i].first) {
                sum += tmp;
            }
            sum /= fs[i].second;
            ret = min(ret, sum);
        }
        if (ret == 0) {
            puts("NIE");
        } else {
            printf("%d\n", ret);
        }
    }
}
