#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 75;

int n;
bitset<maxn> cover[maxn];
int cnt[maxn], order[maxn];
vector<int> choice[maxn], answer, sel;

inline bool byCnt(const int &i, const int &j)
{
    return cnt[i] > cnt[j];
}

inline bool byChoice(const int &i, const int &j)
{
    return choice[i].size() < choice[j].size();
}

inline void dfs(int i, bitset<maxn> current)
{
    if (sel.size() >= answer.size()) {
        return;
    }
    if (i == n) {
        answer = sel;
        return;
    }
    int pos = order[i];
    if (current.test(pos)) {
        dfs(i + 1, current);
    } else {
        for (int j = 0; j < choice[pos].size(); ++ j) {
            int x = choice[pos][j];
            sel.push_back(x);
            dfs(i + 1, current | cover[x]);
            sel.pop_back();
        }
    }
}

int main()
{
    for (int test = 1;scanf("%d", &n) == 1; ++ test) {
        answer.clear();
        for (int i = 0; i < n; ++ i) {
            choice[i].clear();
            answer.push_back(i);
        }
        for (int i = 0; i < n; ++ i) {
            cover[i].reset();
            char s[maxn + 1];
            scanf("%s", s);
            cnt[i] = 0;
            for (int j = 0; j < n; ++ j) {
                if (i == j || s[j] == '1') {
                    cover[i].set(j);
                    ++ cnt[i];
                    choice[j].push_back(i);
                } else {
                    cover[i].reset(j);
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            sort(choice[i].begin(), choice[i].end(), byCnt);
            order[i] = i;
        }
        sort(order, order + n, byChoice);
        sel.clear();
        bitset<maxn> cur;
        cur.reset();
        dfs(0, cur);
        
        printf("Case %d: %d", test, answer.size());
        for (int i = 0; i < answer.size(); ++ i) {
            printf(" %d", answer[i] + 1);
        }
        puts("");
    }
    return 0;
}

