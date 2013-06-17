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

#include <ext/hash_map>
using namespace __gnu_cxx;

#define FOR(it,a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

struct hashLL
{
    inline unsigned operator()(long long a) const {
        return a * 4423;
    }
};

hash_map<long long,int,hashLL> M;

int n;
char str[1 << 20];

int get(long long mask)
{
    hash_map<long long,int,hashLL>::iterator it = M.find(mask);
    return it == M.end() ? 0 : it->second;
}

int main()
{
    freopen("hyperdrome.in", "r", stdin);
    freopen("hyperdrome.out", "w", stdout);
    scanf("%d%s", &n, str);
    long long mask = 0;
    M[mask] ++;
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        int ch = tolower(str[i]) - 'a' + (isupper(str[i]) ? 26 : 0);
        mask ^= 1LL << ch;
        ret += get(mask);
        for (int j = 0; j < 52; j++) {
            ret += get(mask ^ 1LL << j);
        }
        M[mask] ++;
    }
    cout << ret << endl;
}
