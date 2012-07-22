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

string print(char ch, int id)
{
    char buf[10];
    sprintf(buf, "%c%d", ch, id);
    return buf;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int s = 1; s <= n + m; s++) {
        string str = "";
        for (int i = 0; i <= s; i++) {
            int j = s - i;
            if (i > n || j > m)
                continue;
            string expr;
            if (i == 0) {
                expr = print('y', j);
            } else if (j == 0) {
                expr = print('x', i);
            } else {
                expr = "(" + print('x', i) + "|" + print('y', j) + ")";
            }
            if (str == "") {
                str = expr;
            } else {
                str = "(" + str + "&" + expr + ")";
            }
        }
        puts(str.substr(1, str.size() - 2).c_str());
    }
}
