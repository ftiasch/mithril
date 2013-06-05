#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int iterLimit = 10;
const int maxn = 200;
const int maxm = 20;
const short inf = 10000;
const short ONE = 1;
const short TWO = 2;

short f[maxn][maxm][maxm][maxm][maxm];
int day[maxn], maxUse, maxDay, n;
int backup[maxn], id[maxn];
short mark[maxn][maxm][maxm][maxm][maxm], stamp;

inline void regular(int &a, int &b)
{
    a = max(a, 0);
    b = max(b, 0);
    if (a == 0 || b == 0) {
        a = b = 0;
    }
}

short dfs(int i, int d1, int t1, int d2, int t2)
{
    if (i == n) {
        return 0;
    }
    regular(d1, t1);
    regular(d2, t2);
    if (make_pair(d1, t1) > make_pair(d2, t2)) {
        swap(d1, d2);
        swap(t1, t2);
    }
    short &res = f[i][d1][t1][d2][t2];
    if (mark[i][d1][t1][d2][t2] == stamp) {
        return res;
    }
    mark[i][d1][t1][d2][t2] = stamp;
    res = inf;
    if (day[i] == 0) {
        return res = dfs(i + 1, d1, t1 - 1, d2, t2 - 1);
    }
    if (day[i] == 1) {
        //use 1
        if (d1 && t1) {
            res = min(res, dfs(i + 1, d1 - 1, t1 - 1, d2, t2 - 1));
        } else {
            res = min(res, (short)(dfs(i + 1, maxUse - 1, maxDay - 1, d2, t2 - 1) + ONE));
        }
        //use 2
        if (d2 && t2) {
            res = min(res, dfs(i + 1, d1, t1 - 1, d2 - 1, t2 - 1));
        } else {
            res = min(res, (short)(dfs(i + 1, d1, t1 - 1, maxUse - 1, maxDay - 1) + ONE));
        }
    } else {
        if (d1 && t1) {
            if (d2 && t2) {
                res = min(res, dfs(i + 1, d1 - 1, t1 - 1, d2 - 1, t2 - 1));
            } else {
                res = min(res, (short)(dfs(i + 1, d1 - 1, t1 - 1, maxUse - 1, maxDay - 1) + ONE));
            }
        } else {
            if (d2 && t2) {
                res = min(res, (short)(dfs(i + 1, maxUse - 1, maxDay - 1, d2 - 1, t2 - 1) + ONE));
            } else {
                res = min(res, (short)(dfs(i + 1, maxUse - 1, maxDay - 1, maxUse - 1, maxDay - 1) + TWO));
            }
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &maxUse, &maxDay);
    for (int j = 0; j < 2; ++ j) {
        for (int i = 0; i < n; ++ i) {
            int x;
            scanf("%d", &x);
            day[i] += x;
        }
    }
    ++ stamp;
    int answer = dfs(0, 0, 0, 0, 0);
    
    memcpy(backup, day, sizeof(day));
    //greedy
    for (int i = 0; i < n; ++ i) {
        id[i] = i;
    }
    for (int iter = 0; iter < iterLimit; ++ iter) {
        if (iter == 0) {
        } else if (iter == 1) {
            reverse(id, id + n);
        } else {
            random_shuffle(id, id + n);
        }
        for (int thres = 0; thres < 2; ++ thres) {
            memcpy(day, backup, sizeof(day));
            int base = 0;
            for (int it = 0; it < n; ++ it) {
                int i = id[it];
                if (day[i] > thres) {
                    int cnt = 0;
                    for (int j = 0; j < maxDay && i + j < n && cnt < maxUse; ++ j) {
                        cnt += (day[i + j] > thres);
                    }
                    if (cnt == maxUse) {
                        ++ base;
                        cnt = 0;
                        for (int j = 0; j < maxDay && i + j < n && cnt < maxUse; ++ j) {
                            if (day[i + j] > thres) {
                                -- day[i + j];
                                ++ cnt;
                            }
                        }
                    }
                }
            }
            /*for (int i = 0; i < n; ++ i) {
                printf("%d ", day[i]);
            }*/
            ++ stamp;
            //printf(": %d + %d\n", base, dfs(0, 0, 0, 0, 0));
            answer = min(answer, base + dfs(0, 0, 0, 0, 0));
        }
    }
    
    printf("%d\n", answer);
    
//  printf("%d\n", (sizeof(f) + sizeof(mark)) >> 20);
    
    return 0;
}
