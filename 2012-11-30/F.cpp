#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int MOD = 1000000000 + 7;

int m, n, r;
set <vector <int> > valid_states;

void dfs(vector <int> v) {
    if ((int)v.size() < m) {
        int t = *max_element(v.begin(), v.end()) + 2;
        for (int i = 0; i < t; ++ i) {
            vector <int> vv(v);
            vv.push_back(i);
            dfs(vv);
        }
    } else {
        bool found = false;
        for (int i = 0; i < m && !found; ++ i) {
            for (int j = i + 1; j < m && !found; ++ j) {
                if (v[i] != v[j]) {
                    for (int k = j + 1; k < m && !found; ++ k) {
                        if (v[i] == v[k]) {
                            for (int l = k + 1; l < m && !found; ++ l) {
                                found |= v[j] == v[l];
                            }
                        }
                    }
                }
            }
        }
        if (found) {
            valid_states.insert(v);
        }
    }
}

int flag[50];

void minimize(vector <int> &v) {
    int counter = 0;
    memset(flag, -1, sizeof(flag));
    for (int i = 0; i < m; ++ i) {
        if (flag[v[i]] == -1) {
            flag[v[i]] = counter ++;
        }
        v[i] = flag[v[i]];
    }
}

int main() {
    scanf("%d%d%d", &m, &n, &r);
    dfs(vector <int>(1));
    map <vector <int>, int> ways;
    foreach (iter, valid_states) {
        vector <int> v = *iter;
        v.pop_back();
        if (ways.find(v) == ways.end()) {
            int &ret = ways[v];
            int t = *max_element(v.begin(), v.end());
            ret = 1;
            for (int i = 0; i <= t; ++ i) {
                ret = (long long)ret * (r - i) % MOD;
            }
        }
    }
    for (int _ = n - m; _>=0; -- _) {
        map <vector <int>, int> new_ways;
        foreach (iter, ways) {
            const vector <int> &v = iter->first;
            int t = *max_element(v.begin(), v.end());
            for (int i = 0; i <= t + 1; ++ i) {
                int s = i <= t ? 1 : r - (t + 1);
                vector <int> vv(v);
                vv.push_back(i);
                if (valid_states.find(vv) != valid_states.end()) {
                    for (int i = 0; i + 1 < m; ++ i) {
                        vv[i] = vv[i + 1];
                    }
                    vv.pop_back();
                    minimize(vv);
                    (new_ways[vv] += (long long)iter->second * s % MOD) %= MOD;
                }
            }
        }
        ways = new_ways;
    }
    int answer = 0;
    foreach (iter, ways) {
        (answer += iter->second) %= MOD;
    }
    printf("%d\n", answer);
    return 0;
}
