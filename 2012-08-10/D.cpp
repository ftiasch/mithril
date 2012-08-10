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

const int maxn = 20000;

int n;

vector<int> muls, nums, psum;

vector<pair<int,int> > states;

int pair2int(pair<int,int> s)
{
    return psum[s.first] + s.second;
}

pair<int,int> int2pair(int s)
{
    return states[s];
}

pair<int,int> goLeft(pair<int,int> a)
{
    int num = nums[a.first];
    return make_pair(a.first, (a.second + num - 1) % num);
}

pair<int,int> goRight(pair<int,int> a)
{
    int num = nums[a.first];
    return make_pair(a.first, (a.second + 1) % num);
}

pair<int,int> goUp(pair<int,int> a)
{
    assert(a.first > 0);
    return make_pair(a.first - 1, a.second / muls[a.first - 1]);
}

pair<int,int> goDown(pair<int,int> a, int digit)
{
    assert(a.first < muls.size());
    assert(0 <= digit && digit < muls[a.first]);
    return make_pair(a.first + 1, a.second * muls[a.first] + digit);
}

vector<int> adj[maxn];

void prepare()
{
    muls.assign(1, n);
    for (int i = n - 4; i >= 1; i--) {
        muls.push_back(i);
    }
    nums.assign(1, 1);
    for (int i = 0; i < muls.size(); i++) {
        nums.push_back(nums.back() * muls[i]);
    }
    psum.assign(1, 0);
    states.clear();
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums[i]; j++) {
            states.push_back(make_pair(i, j));
        }
        psum.push_back(psum.back() + nums[i]);
    }
    for (int i = 0; i < states.size(); i++) {
        adj[i].clear();
        pair<int,int> state = int2pair(i);
        if (state.first > 0) {
            adj[i].push_back(pair2int(goUp(state)));
        }
        adj[i].push_back(pair2int(goLeft(state)));
        adj[i].push_back(pair2int(goRight(state)));
        if (state.first < muls.size()) {
            for (int j = 0; j < muls[state.first]; j++) {
                adj[i].push_back(pair2int(goDown(state, j)));
            }
        }
    }
}

int readState()
{
    static char str[maxn];
    pair<int,int> state(0, 0);
    scanf("%s", str);
    for (int i = 0; str[i]; i++) {
        if (str[i] == 'b') {
            state = goUp(state);
        } else if (str[i] == 'l') {
            state = goLeft(state);
        } else if (str[i] == 'r') {
            state = goRight(state);
        } else {
            state = goDown(state, str[i] - '0');
        }
    }
    return pair2int(state);
}

int dist[maxn];

vector<int> wys[maxn];

void add(vector<int> &a, const vector<int> &b)
{
    if (a.size() < b.size()) {
        a.resize(b.size(), 0);
    }
    for (int i = 0; i < b.size(); i++) {
        a[i] += b[i];
    }
    int carry = 0;
    for (int i = 0; i < a.size() || carry; i++) {
        if (i == a.size()) {
            a.push_back(0);
        }
        a[i] += carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
}

ostream &operator<<(ostream &out, const vector<int> &a)
{
    for (int i = a.size() - 1; i >= 0; i--) {
        out << a[i];
    }
    if (a.empty()) {
        out << 0;
    }
    return out;
}

int main()
{
    scanf("%d", &n);
    prepare();
    int src = readState(), dest = readState();
    memset(dist, -1, sizeof(dist));
    dist[src] = 0;
    queue<int> Q;
    Q.push(src);
    for (int i = 0; i < states.size(); i++) {
        wys[i].clear();
    }
    wys[src].assign(1, 1);
    while (!Q.empty()) {
        int p = Q.front();
        Q.pop();
        for (int i = 0; i < adj[p].size(); i++) {
            int q = adj[p][i];
            if (dist[q] < 0) {
                dist[q] = dist[p] + 1;
                Q.push(q);
            }
            if (dist[q] == dist[p] + 1) {
                add(wys[q], wys[p]);
            }
        }
    }
    cout << wys[dest] << endl;
}
