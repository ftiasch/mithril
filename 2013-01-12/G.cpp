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

bool divide(vector<int> a, const vector<int> &b, vector<int> &c)
{
    assert(a.size() > 0 && a.back() == 1);
    assert(b.size() > 0 && b.back() == 1);
    if (a.size() < b.size()) {
        return false;
    }
    c.resize(a.size() - b.size() + 1);
    for (int i = c.size() - 1; i >= 0; i--) {
        int val = a[i + b.size() - 1];
        c[i] = val;
        for (int j = b.size() - 1; j >= 0; j--) {
            a[i + j] -= b[j] * val;
        }
    }
    for (int i = 0; i < b.size(); i++) {
        if (a[i] != 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<int> input(5);
    input[4] = 1;
    for (int i = 3; i >= 0; i--) {
        scanf("%d", &input[i]);
    }
    vector<vector<int> > ans;
    while (input[0] == 0) {
        vector<int> tmp(2);
        tmp[0] = 0;
        tmp[1] = 1;
        ans.push_back(tmp);
        input.erase(input.begin());
    }
    for (int i = -20000; i <= 20000; i++) {
        long long sum = 0;
        for (int j = input.size() - 1; j >= 0; j--) {
            sum = sum * i + input[j];
        }
        if (sum == 0) {
            vector<int> tmp(2), tmp2;
            tmp[0] = -i;
            tmp[1] = 1;
            bool res = divide(input, tmp, tmp2);
            assert(res);
            ans.push_back(tmp);
            input = tmp2;
            i --;
        }
    }
    if (input.size() == 5) {
        for (int b = -20000; b <= 20000; b++) {
            if (b == 0) {
                continue;
            }
            int d = input[0] / b;
            if ((long long)b * d == input[0]) {
                for (int a = -2000; a <= 2000; a++) {
                    vector<int> tmp(3), tmp2;
                    tmp[0] = b;
                    tmp[1] = a;
                    tmp[2] = 1;
                    bool res = divide(input, tmp, tmp2);
                    if (res) {
                        ans.push_back(tmp);
                        input = tmp2;
                        break;
                    }
                }
            }
        }
    }
    if (input.size() > 1) {
        ans.push_back(input);
    }
    if (ans.size() == 1) {
        printf("Irreducible\n");
        return 0;
    }
    sort(ans.begin(), ans.end());
    for (vector<vector<int> >::iterator it = ans.begin(); it != ans.end(); ++it) {
        putchar('(');
        for (int i = it->size() - 1; i >= 0; i--) {
            int val = (*it)[i];
            if (val == 0) {
                continue;
            }
            if (i < it->size() - 1) {
                if (val > 0) {
                    putchar('+');
                } else {
                    putchar('-');
                }
            }
            if (val < 0) {
                val = -val;
            }
            if (i == 0 || val > 1) {
                printf("%d", val);
            }
            if (i > 0) {
                printf("x");
                if (i > 1) {
                    printf("%d", i);
                }
            }
        }
        putchar(')');
    }
    puts("");
}
