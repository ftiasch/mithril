#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int maxn = 100000;

int f[maxn + 1], g[maxn + 1];
vector<int> pre[maxn + 1];

vector< vector<int> > answer;
vector<int> current;

inline void print(int n)
{
    if (n == 0) {
        reverse(current.begin(), current.end());
        answer.push_back(current);
        reverse(current.begin(), current.end());
        return;
    }
    
    for (int i = 0; i < pre[n].size(); ++ i) {
        int x = pre[n][i];
        int num = (n - x) / (x + 1);
        for (int j = 0; j < num; ++ j) {
            current.push_back(x + 1);
        }
        print(x);
        for (int j = 0; j < num; ++ j) {
            current.pop_back();
        }
    }
}

int main()
{
    for (int i = 0; i <= maxn; ++ i) {
        f[i] = maxn + 10;
    }
    f[0] = 0;
    g[0] = 1;
    for (int i = 0; i <= maxn; ++ i) {
        for (int j = i + i + 1, k = 1; j <= maxn; j += i + 1, ++ k) {
            if (f[i] + k < f[j]) {
                f[j] = f[i] + k;
                g[j] = 0;
                pre[j].clear();
            }
            if (f[i] + k == f[j]) {
                pre[j].push_back(i);
                g[j] += g[i];
            }
        }
        //printf("%d %d\n", i, f[i]);
    }
    int T;
    for (scanf("%d", &T); T --;) {
        int n;
        scanf("%d" ,&n);
        printf("%d %d\n", g[n], f[n]);
        answer.clear();
        print(n);
        sort(answer.begin(), answer.end());
        for (int i = 0; i < answer.size(); ++ i) {
            for (int j = 0; j < answer[i].size(); ++ j) {
                if (j) {
                    printf(" ");
                }
                printf("%d", answer[i][j]);
            }
            puts("");
        }
    }
    return 0;
}

