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
    int n;
    while (cin >> n) {
        int m = n;
        int ans = 1;
        for (int i = 2; i * i <= m; i++) {
            if (m % i == 0) {
                int cnt = 0;
                while (m % i == 0) {
                    m /= i;
                    cnt ++;
                }
                cnt = (cnt + 1) / 2;
                for (int j = 0; j < cnt; j++) {
                    ans *= i;
                }
            }
        }
        ans *= m;
        set<int> S;
        vector<int> lst;
        lst.push_back(1);
        S.insert(1);
        while (true) {
            int newv = (lst.back() + ans) % n;
            if (S.insert(newv).second) {
                lst.push_back(newv);
            } else {
                break;
            }
        }
        if (lst.size() <= 2) {
            lst.clear();
            lst.push_back(1);
            lst.push_back(0);
        }
        printf("%d\n", lst.size());
        for (int i = 0; i < lst.size(); i++) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", lst[i]);
        }
        puts("");
    }
}
