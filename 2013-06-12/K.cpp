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

typedef unsigned long long ULL;

const ULL MAGIC = 4423LLU << 32 | 3137;

pair<bool,ULL> read()
{
    static char buf[100], *ptr;
    scanf("%s", ptr = buf);
    bool fst = true;
    ULL snd = 0;
    if (*ptr == '!') {
        fst = false;
        ptr ++;
    }
    while (*ptr) {
        snd = snd * MAGIC + *ptr++;
    }
    return make_pair(fst, snd);
}

map<ULL,int> pos;
vector<ULL> seq;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        static char buf[10];
        scanf("%s", buf);
        if (*buf == 'E') {
            ULL code = read().second;
            pos[code] = seq.size();
            seq.push_back(code);
        } else if (*buf == 'D') {
            int num;
            scanf("%d", &num);
            while (num -- && !seq.empty()) {
                pos.erase(seq.back());
                seq.pop_back();
            }
        } else {
            int num;
            scanf("%d", &num);
            int minv = 0, maxv = seq.size();
            bool valid = true;
            while (num --) {
                pair<bool,ULL> code = read();
                if (code.first) {
                    if (!pos.count(code.second)) {
                        valid = false;
                    } else {
                        maxv = min(maxv, (int)seq.size() - pos[code.second] - 1);
                    }
                } else {
                    if (pos.count(code.second)) {
                        minv = max(minv, (int)seq.size() - pos[code.second]);
                    }
                }
            }
            if (valid && minv <= maxv) {
                if (minv == 0) {
                    puts("Yes");
                } else {
                    printf("%d Just A Dream\n", minv);
                }
            } else {
                puts("Plot Error");
            }
        }
    }
}
