#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector <vector <int> > left, right;

int n;

#define SIZE(v) (int)(v).size()

void construct(int d, int l, int r) {
    if (r - l > 1) {
        if (SIZE(left) <= d) {
            left.push_back(vector <int>());
        }
        if (SIZE(right) <= d) {
            right.push_back(vector <int>());
        }
        int m = l + r >> 1;
        for (int i = l; i < m; ++ i) {
            left[d].push_back(i);
        }
        for (int i = m; i < r; ++ i) {
            right[d].push_back(i);
        }
        construct(d + 1, l, m);
        construct(d + 1, m, r);
    }
}

const int N = 500;

int color[N][N];

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i) 

int main() {
    freopen("avia2.in", "r", stdin);
    freopen("avia2.out", "w", stdout);
    scanf("%d", &n);
    construct(0, 0, n);
    for (int i = 0; i < SIZE(left) && i < SIZE(right); ++ i) {
        foreach (x, left[i]) {
            foreach (y, right[i]) {
                color[*x][*y] = color[*y][*x] = i + 1;
            }
        }
    }
    printf("%d\n", min(SIZE(left), SIZE(right)));
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            printf("%d%c", color[i][j], j == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
