#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn = 105;

int n, f[maxn][maxn][2][3], stamp;
char s[1005], answer[1005];
int must;

inline bool solve(int l, int r, int left, int right)
{
    if ((r - l + 1) & 1) {
        return false;
    }
    if (l > r) {
        if (left == 1 || right == 2) {
            return true;
        } else {
            return false;
        }
    }
    int &res = f[l][r][left][right];
    if (res == stamp) {
        return false;
    }
    res = stamp;
    for (char a = (l == 0)?'1':'0'; a <= '9'; ++ a) {
        if (!left && a < s[l]) {
            continue;
        }
        if (l < must && a != answer[l]) {
            continue;
        }
        int nleft = left || (a > s[l]);
        for (char b = '0'; b <= '9'; ++ b) {
            if (a == b) {
                continue;
            }
            if (r < must && b != answer[r]) {
                continue;
            }
            int nright = right;
            if (b < s[r]) {
                nright = 0;
            } else if (b > s[r]) {
                nright = 2;
            }
            if (solve(l + 1, r - 1, nleft, nright)) {
                return true;
            }
        }
    }
    return false;
}

inline bool solve()
{
    must = 0;
    ++ stamp;
    if (!solve(0, n - 1, 0, 1)) {
        return false;
    }
    for (int i = 0; i < n; ++ i) {
        ++ must;
        for (char a = (i == 0)?'1':'0'; a <= '9'; ++ a) {
            answer[i] = a;
            ++ stamp;
            if (solve(0, n - 1, 0, 1)) {
                break;
            }
        }
    }
    return true;
}

inline bool check(int x)
{
    char s1[15], s2[15];
    sprintf(s1, "%d", x);
    sprintf(s2, "%d", x);
    int n = strlen(s1);
    reverse(s1, s1 + n);
    for (int i = 0; i < n; ++ i) {
        if (s1[i] == s2[i]) {
            return false;
        }
    }
    return true;
}

inline int brute(char s[])
{
    int x;
    sscanf(s, "%d", &x);
    ++ x;
    while (!check(x)) {
        ++ x;
    }
    return x;
}

int main()
{
    for (;scanf("%s", s) == 1 && strcmp(s, "0");) {
        //printf("%d\n", brute(s));
        n = strlen(s);
        while (!solve()) {
            ++ n;
            for (int i = 0; i < n ;++ i) {
                s[i] = '0';
            }
            s[n] = 0;
        }
        answer[n] = 0;
        puts(answer);
    }
    return 0;
}

