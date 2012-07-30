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

string solve(int n, string s, int k)
{
    int carry0 = 0;
    if (s.size() > n) {
        s = s.substr(s.size() - n);
        carry0 = 1;
    }
    int g = n;
    while (n % g || k % g) {
        g --;
    }
    vector<int> digits(n), ans(n);
    for (int msk = 0; msk < (1 << n - 1); msk++) {
        int carry = carry0;
        bool valid = true;
        for (int i = 0; i < n; i++) {
            carry = carry * 10 + (s[i] - '0');
            int nc = 0;
            if (i + 1 < n && msk >> i & 1) {
                carry --;
                nc ++;
            }
            if (carry < 0) {
                valid = false;
                break;
            }
            digits[i] = carry;
            carry = nc;
        }
        if (carry) {
            continue;
        }
        if (!valid) {
            continue;
        }
        for (int i = 0; i < g; i++) {
            bool found = false;
            for (int digit = 0; digit < 10; digit++) {
                if (i == 0 && digit == 0) {
                    continue;
                }
                ans[i] = digit;
                int p = i;
                bool valid = true;
                while (true) {
                    int q = (p + k) % n;
                    if (q == i) {
                        if (ans[q] != digits[p] - ans[p]) {
                            valid = false;
                        }
                        break;
                    }
                    ans[q] = digits[p] - ans[p];
                    if (ans[q] < 0 || ans[q] > 9) {
                        valid = false;
                        break;
                    }
                    p = q;
                }
                if (valid) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                valid = false;
                break;
            }
        }
        if (valid) {
            string ret = "";
            for (int i = 0; i < n; i++) {
                ret += (char)('0' + ans[i]);
            }
            return ret;
        }
    }
    return "";
}

int main()
{
    string sum;
    int k;
    cin >> sum >> k;
    string res = solve(sum.size(), sum, k);
    if (res == "" && sum[0] == '1' && sum.size() >= 2) {
        res = solve(sum.size() - 1, sum, k);
    }
    if (res == "") {
        res = "IMPOSSIBLE";
    }
    cout << res << endl;
}
