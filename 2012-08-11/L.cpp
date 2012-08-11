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
    string s;
    cin >> s;
    int pos1 = -1;
    int pos2 = -1;
    int pos3 = -1;
    if (s[s.size() - 1] == '4') {
        cout << s.substr(0, s.size() - 1) << '1' << endl;
        cout << s.substr(0, s.size() - 1) << '2' << endl;
        cout << s.substr(0, s.size() - 1) << '3' << endl;
    } else {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') {
                pos1 = i;
            } else if (s[i] == '2') {
                pos2 = i;
            } else if (s[i] == '3') {
                pos3 = i;
            }
        }
        if (pos1 >= 0) {
            cout << s.substr(0, pos1) << '4' << endl;
        }
        if (pos2 >= 0) {
            cout << s.substr(0, pos2) << '4' << endl;
        }
        if (pos3 >= 0) {
            cout << s.substr(0, pos3) << '4' << endl;
        }
    }
}
