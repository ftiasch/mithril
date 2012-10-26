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

const int maxn = 16;

struct UnionFind
{
    int parent[maxn];
    int comps;

    void clear(int n) {
        memset(parent, -1, sizeof(parent));
        comps = n;
    }

    int findRoot(int p) {
        return parent[p] < 0 ? p : (parent[p] = findRoot(parent[p]));
    }

    bool mergeComp(int a, int b) {
        a = findRoot(a);
        b = findRoot(b);
        if (a == b) {
            return false;
        }
        comps --;
        parent[a] = b;
        return true;
    }
};

typedef vector<pair<int,int> > Intervals;

long long solve(int n)
{
    if (n == 1) {
        return 2;
    }
    vector<pair<UnionFind, Intervals> > st;
    UnionFind uf;
    uf.clear(n);
    if (n % 2 == 1) {
        for (int i = 0; i < n; i += 2) {
            for (int j = 0; j < i; j += 2) {
                Intervals ints;
                ints.push_back(make_pair(0, i));
                ints.push_back(make_pair(i + 1, n));
                ints.push_back(make_pair(0, j));
                ints.push_back(make_pair(j + 1, n));
                st.push_back(make_pair(uf, ints));
            }
        }
    } else {
        for (int i = 1; i < n; i += 2) {
            for (int j = 0; j < i; j += 2) {
                Intervals ints;
                ints.push_back(make_pair(0, j));
                ints.push_back(make_pair(j + 1, i));
                ints.push_back(make_pair(i + 1, n));
                ints.push_back(make_pair(0, n));
                st.push_back(make_pair(uf, ints));
            }
        }
    }
    long long ret = 0;
    while (!st.empty()) {
        uf = st.back().first;
        Intervals ints = st.back().second;
        st.pop_back();
        while (!ints.empty() && ints.back().first == ints.back().second) {
            ints.pop_back();
        }
        if (ints.empty()) {
            if (uf.comps == 1) {
                ret ++;
            }
        } else {
            int l = ints.back().first;
            int r = ints.back().second;
            ints.pop_back();
            if ((r - l) % 2 == 0) {
                for (int m = l + 1; m < r; m += 2) {
                    UnionFind uf2 = uf;
                    uf2.mergeComp(l, m);
                    ints.push_back(make_pair(l + 1, m));
                    ints.push_back(make_pair(m + 1, r));
                    st.push_back(make_pair(uf2, ints));
                    ints.pop_back();
                    ints.pop_back();
                }
            }
        }
    }
    return ret * 4;
}

int main()
{
    const int ans[17] = {0,2,4,4,12,16,56,84,324,524,2152,3656,15704,27640,122776,221908,1011756};
    int n;
    while (cin >> n) {
        cout << ans[n] << endl;
    }
}
