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

const int maxn = 100;

int seqLR[maxn], seqRL[maxn];
int n;

int getCode()
{
    char buf[10];
    scanf("%s", buf);
    return *buf - 'A';
}

string solve(int l, int r)
{
    if (l == r) {
        return string(1, 'A' + seqRL[l]);
    }
    int mask = 0;
    for (int i = l; i <= r; i++) {
        mask |= 1 << seqRL[i];
    }
    vector<int> LR;
    for (int i = 0; i < n; i++) {
        if (mask >> seqLR[i] & 1) {
            LR.push_back(seqLR[i]);
        }
    }
    assert((int)LR.size() == r - l + 1);
    assert(seqRL[l] == LR[0]);
    int pos = find(LR.begin(), LR.end(), seqRL[l + 1]) - LR.begin();
    assert(pos != (int)LR.size());
    vector<int> positions;
    positions.push_back(r + 1);
    for (int i = 1; i <= pos; i++) {
        positions.push_back(find(seqRL, seqRL + n, LR[i]) - seqRL);
    }
    for (int i = 1; i < (int)positions.size(); i++) {
        assert(positions[i-1] > positions[i]);
    }
    assert(positions.back() == l + 1);
    string ret = "";
    for (int i = 1; i < (int)positions.size(); i++) {
        ret += solve(positions[i], positions[i-1] - 1);
    }
    return string(1, 'A' + seqRL[l]) + "(" + ret + ")";
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        seqRL[i] = getCode();
    }
    for (int i = 0; i < n; i++) {
        seqLR[i] = getCode();
    }
    cout << solve(0, n - 1) << endl;
}
