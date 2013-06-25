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

bool leadTo0(const string &s)
{
    if (s.size() % 2 == 0) {
        if (s.find('1') == -1) {
            return true;
        }
        return false;
    }
    string odd = "", even = "";
    for (int i = 1; i < s.size(); i += 2) {
        odd += s[i];
        even += (char)((s[i - 1] ^ s[i + 1]) + '0');
    }
    return leadTo0(odd) && leadTo0(even);
}

int main()
{
    int tests;
    cin >> tests;
    while (tests --) {
        string s;
        cin >> s;
        cout << (leadTo0(s) ? "DIES" : "LIVES") << endl;
    }
}
