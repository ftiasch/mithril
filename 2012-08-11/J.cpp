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

map<string,int> M;
map<string,int>::iterator it;

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        string of, name;
        cin >> a >> of >> b;
        for (int i = 0; i < a; i++) {
            cin >> name;
            if (M.count(name)) {
                M[name] = min(M[name], b);
            } else {
                M[name] = b;
            }
        }
    }
    vector<vector<string> > names(512);
    for (it = M.begin(); it != M.end(); ++it) {
        names[it->second].push_back(it->first);
    }
    int cnt = 0;
    for (int i = 1; i < 512; i++) {
        if (names[i].size() == 1 && cnt + 1 == i) {
            cout << i << " " << names[i][0] << endl;
        }
        cnt += names[i].size();
    }
}
