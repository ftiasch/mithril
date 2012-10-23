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

const int MASK = 1 << 7;

int LEN[MASK];

void prepare()
{
    LEN[1] = 0;
    for (int i = 2; i < MASK; i++) {
        if ((i & (i - 1)) == 0) {
            LEN[i] = LEN[i - 1] + 1;
        } else {
            LEN[i] = LEN[i - 1];
        }
    }
}

int n, limit, mask;

int append(int prefix, int suffix)
{
    int len = LEN[suffix];
    while ((prefix >> limit) == 0 && len) {
        prefix <<= 1;
        prefix |= suffix >> --len & 1;
    }
    return prefix;
}

struct Plan
{
    int len;
    bool isRaw[10];
    int ch[10];

    bool allRaw() const {
        for (int i = 0; i < len; i++) {
            if (!isRaw[i]) {
                return false;
            }
        }
        return true;
    }
};

int sz[26];
Plan grammar[26][100];

vector<int> prefix[26];
bool visited[26][MASK];

int main()
{
    int S = 'S' - 'A';
    prepare();
    scanf("%d%d", &n, &limit);
    mask = 1 << limit + 1;
    for (int i = 0; i < 26; i++) {
        sz[i] = 0;
        prefix[i].clear();
        memset(visited[i], false, sizeof(visited[i]));
    }
    for (int i = 0; i < n; i++) {
        static char buf[1 << 10];
        scanf("%s", buf);
        int ch = buf[0] - 'A';
        assert(0 <= ch && ch < 26);
        Plan &plan = grammar[ch][sz[ch]++];
        plan.len = 0;
        for (char *ptr = buf + 3; *ptr; ptr++) {
            if (*ptr == '0' || *ptr == '1') {
                plan.isRaw[plan.len] = true;
                plan.ch[plan.len] = *ptr == '0' ? 2 : 3;
            } else {
                assert('A' <= *ptr && *ptr <= 'Z');
                plan.isRaw[plan.len] = false;
                plan.ch[plan.len] = *ptr - 'A';
            }
            plan.len ++;
        }
        if (plan.allRaw()) {
            int now = 1;
            for (int j = 0; j < plan.len; j++) {
                now = append(now, plan.ch[j]);
            }
            if (!visited[ch][now]) {
                visited[ch][now] = true;
                prefix[ch].push_back(now);
            }
        }
    }
    while (true) {
        bool changed = false;
        for (int s = 0; s < 26; s++) {
            for (int i = 0; i < sz[s]; i++) {
                static bool vis[2][MASK];
                const Plan &plan = grammar[s][i];
                bool *now = vis[0], *prev = vis[1];
                memset(now, false, sizeof(bool) * mask);
                now[1] = true;
                for (int j = 0; j < plan.len; j++) {
                    swap(now, prev);
                    memset(now, false, sizeof(bool) * mask);
                    if (plan.isRaw[j]) {
                        for (int z = 1; z < mask; z++) {
                            if (prev[z]) {
                                now[append(z, plan.ch[j])] = true;
                            }
                        }
                    } else {
                        for (int z = 1; z < mask; z++) {
                            if (prev[z]) {
                                FOR (it, prefix[plan.ch[j]]) {
                                    now[append(z, *it)] = true;
                                }
                            }
                        }
                    }
                }
                for (int z = 1; z < mask; z++) {
                    if (now[z] && !visited[s][z]) {
                        changed = true;
                        visited[s][z] = true;
                        prefix[s].push_back(z);
                    }
                }
            }
        }
        if (!changed) {
            break;
        }
    }
    printf("%d\n", prefix[S].size());
    vector<string> outputs;
    FOR (it, prefix[S]) {
        int num = *it;
        string s = "";
        while (num > 1) {
            s += (num & 1) + '0';
            num >>= 1;
        }
        reverse(s.begin(), s.end());
        outputs.push_back(s);
    }
    sort(outputs.begin(), outputs.end());
    FOR (it, outputs) {
        if (*it == "") {
            *it = "eps";
        }
        puts(it->c_str());
    }
}
