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

long long solve(string s)
{
    int l = 0, r = s.size() - 1;
    vector<int> exact, miss;
    while (l <= r) {
        if (l == r) {
            exact.push_back(s[l] == '?' ? 10 : 1);
            miss.push_back(0);
        } else if (s[l] == '?' && s[r] == '?') {
            exact.push_back(10);
            miss.push_back(90);
        } else if (s[l] == '?' || s[r] == '?') {
            exact.push_back(1);
            miss.push_back(9);
        } else if (s[l] == s[r]) {
            exact.push_back(1);
            miss.push_back(0);
        } else {
            exact.push_back(0);
            miss.push_back(1);
        }
        l ++, r--;
    }
    long long ret = 0;
    for (int i = 0; i <= exact.size(); i++) {
        long long mul = 1;
        for (int j = 0; j < exact.size(); j++) {
            mul *= i == j ? miss[j] : exact[j];
        }
        ret += mul;
    }
    return ret;
}

int main()
{
    string s;
    while (cin >> s && s != "0") {
        long long ret = 0;
        for (int i = 1; i < s.size(); i++) {
            for (char ch = '1'; ch <= '9'; ch++) {
                ret += solve(ch + string(i - 1, '?'));
            }
        }
        for (int i = 0; i < s.size(); i++) {
            for (char j = i == 0 ? '1' : '0'; j < s[i]; j++) {
                ret += solve(s.substr(0, i) + j + string(s.size() - i - 1, '?'));
            }
        }
        ret += solve(s);
        cout << ret << endl;
    }
}
