// Problem K -- Parse Tree
// Author: Bin Jin
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

const int maxn = 512;

struct Grid {
    int height, width;
    int middle;

    vector<string> grid;

    Grid(int h, int w, int m) :
        height(h), width(w), middle(m), grid(h, string(w, ' ')) { }

    string &operator[](int r) {
        return grid[r];
    }

    const string &operator[](int r) const {
        return grid[r];
    }

    void print() const {
        for (int i = 0; i < height; i++)
            puts(grid[i].c_str());
    }
};

int matching[maxn];
char expr[maxn];
int n;

Grid solve(int l, int r)
{
    while (matching[l] == r) {
        l ++;
        r --;
    }
    if (l == r) {
        Grid ret(1, 1, 0);
        ret[0][0] = expr[l];
        return ret;
    }
    int lastPM = -1, lastMD = -1, firstP = -1;
    for (int i = l; i <= r; i++) {
        if (expr[i] == '(') {
            i = matching[i];
        } else if (expr[i] == '+' || expr[i] == '-') {
            lastPM = i;
        } else if (expr[i] == '*' || expr[i] == '/') {
            lastMD = i;
        } else if (expr[i] == '^' && firstP < 0) {
            firstP = i;
        }
    }
    int pos = lastPM >= 0 ? lastPM : lastMD >= 0 ? lastMD : firstP;
    assert(pos > l && pos < r);
    Grid L = solve(l, pos - 1);
    char oper = expr[pos];
    Grid R = solve(pos + 1, r);
    Grid ret(max(L.height, R.height) + 2, L.width + R.width + 5, L.width + 2);
    int delta = L.width + 5;
    for (int i = 0; i < L.height; i++)
        for (int j = 0; j < L.width; j++)
            ret[i+2][j] = L[i][j];
    for (int i = 0; i < R.height; i++)
        for (int j = 0; j < R.width; j++)
            ret[i+2][j+delta] = R[i][j];
    ret[1][L.middle] = '|';
    ret[1][R.middle+delta] = '|';
    ret[0][L.middle] = '.';
    ret[0][R.middle+delta] = '.';
    for (int i = L.middle + 1; i < R.middle + delta; i++)
        ret[0][i] = '-';
    ret[0][ret.middle] = oper;
    ret[0][ret.middle-1] = '[';
    ret[0][ret.middle+1] = ']';
    return ret;
}

int main()
{
    while (scanf("%s", expr) == 1) {
        n = strlen(expr);
        memset(matching, -1, sizeof(matching));
        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (expr[i] == '(') {
                st.push_back(i);
            } else if (expr[i] == ')') {
                int j = st.back();
                st.pop_back();
                matching[i] = j;
                matching[j] = i;
            }
        }
        Grid output = solve(0, n - 1);
        output.print();
    }
}
