#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ext/hash_map>
using namespace std;
using namespace __gnu_cxx;

const int maxn = 14;
const int limit = 8;

hash_map<int, bool> memo[maxn];
int n, m, k;
struct node
{
    int a, b;
}array[maxn][4];

inline int apply(int x, const node &a)
{
    return ((long long) x * a.a + a.b) % m;
}
char oper[100], answer[100];

inline char solve(int i, int x)
{
    if (i == n) {
        return (x <= k) || (x >= m - k);
    }
    int delta = oper[i] == 'T';
    return solve(i + 1, apply(x, array[i][2 + delta])) && solve(i + 1, apply(x, array[i][2 + (delta ^ 1)]))
        || solve(i + 1, apply(x, array[i][0 + delta])) && solve(i + 1, apply(x, array[i][0 + (delta ^ 1)]));
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s", oper);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 4; ++ j) {
//            array[i][j].a = 0;
//            array[i][j].b = rand() % m;
            scanf("%d%d", &array[i][j].a, &array[i][j].b);
            ++ array[i][j].a;
            array[i][j].a %= m;
            array[i][j].b %= m;
            if (array[i][j].a < 0) {
                array[i][j].a += m;
            }
            if (array[i][j].b < 0) {
                array[i][j].b += m;
            }
        }
    }
    
    //memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; ++ i) {
        memo[i].clear();
    }
    int x = 0;
    for (int i = 0; i < n; ++ i) {
        bool flag = true;
        for (int j = 2; j < 4; ++ j) {
            if (!solve(i + 1, apply(x, array[i][j]))) {
                flag = false;
                break;
            }
        }
        if (flag) {
            answer[i] = 'B';
        } else {
            answer[i] = 'T';
        }
        int choice = (answer[i] == 'B') * 2 + (oper[i] == 'B');
        x = apply(x, array[i][choice]);
    }
    answer[n] = 0;
    puts(answer);

    return 0;
}
