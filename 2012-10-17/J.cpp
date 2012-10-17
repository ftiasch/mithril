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

const int maxn = 100000;

bool solve10(int a[], int ans10[], int drop10[])
{
    static char prev[21][11][10];
    memset(prev, -1, sizeof(prev));
    prev[0][0][0] = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j <= 10; j++) {
            for (int mod = 0; mod < 10; mod ++) {
                if (prev[i][j][mod] >= 0) {
                    prev[i + 1][j][mod] = 0;
                    if (j < 10) {
                        prev[i + 1][j + 1][(mod + a[i]) % 10] = 1;
                    }
                }
            }
        }
    }
    if (prev[20][10][0] < 0) {
        return false;
    }
    int x = 20, y = 10, z = 0;
    while (x > 0) {
        if (prev[x][y][z]) {
            x --;
            y --;
            z = (z - a[x]) % 10;
            if (z < 0) {
                z += 10;
            }
            ans10[y] = x;
        } else {
            x --;
            drop10[x - y] = x;
        }
    }
    assert(y == 0 && z == 0);
    return true;
}

int n;

vector<int> ans;

vector<bool> solve(const vector<int> &a)
{
    if (a.size() < 10) {
        assert(a.size() == 2);
        vector<bool> ret(2);
        ret[0] = true;
        ret[1] = false;
        return ret;
    }
    assert(a.size() % 10 == 0);
    int extra[20], which[20], choose[10], drop[10];
    for (int i = 0; i < 10; i++) {
        extra[i] = a[i];
        which[i] = i;
    }
    vector<int> na(a.size() / 10);
    vector<vector<int> > mapping(a.size() / 10, vector<int>(10));
    int ptr = 0;
    for (int i = 10; i < a.size(); i += 10) {
        for (int j = 0; j < 10; j++) {
            extra[10 + j] = a[i + j];
            which[10 + j] = i + j;
        }
        bool res = solve10(extra, choose, drop);
        assert(res);
        long long sum = 0;
        for (int j = 0; j < 10; j++) {
            sum += extra[choose[j]];
            choose[j] = which[choose[j]];
            drop[j] = which[drop[j]];
        }
        assert(sum % 10 == 0);
        sum /= 10;
        na[ptr] = sum;
        for (int j = 0; j < 10; j++) {
            mapping[ptr][j] = choose[j];
            extra[j] = a[drop[j]];
            which[j] = drop[j];
        }
        ptr ++;
    }
    long long sum = 0;
    for (int j = 0; j < 10; j++) {
        sum += extra[j];
    }
    assert(sum % 10 == 0);
    sum /= 10;
    na[ptr] = sum;
    for (int j = 0; j < 10; j++) {
        mapping[ptr][j] = which[j];
    }
    ptr ++;
    vector<bool> res = solve(na);
    vector<bool> ret(a.size(), false);
    for (int i = 0; i < res.size(); i ++) {
        for (int j = 0; j < 10; j++) {
            ret[mapping[i][j]] = res[i];
        }
    }
    return ret;
}

int main()
{
    srand(time(0));
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    scanf("%d", &n);
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        scanf("%d", &a[i]);
        //a[i] = rand() % n;
    }
    int a0 = 0;
    for (int i = 1; i < 2 * n; i++) {
        a0 = (a0 - a[i]) % n;
    }
    a[0] = (a0 + n) % n;
    vector<bool> ans = solve(a);
    bool first = true;
    int sum = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (ans[i] != ans[0]) {
            if (first) {
                first = false;
            } else {
                putchar(' ');
            }
            printf("%d", i + 1);
            sum += a[i];
            sum %= n;
        }
    }
    puts("");
    assert(sum == 0);
}
