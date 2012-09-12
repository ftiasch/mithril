#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 500000 + 1;

int n;
int height[N];
double SQRT[N], result[2][N];

int m, start[N], choice[N];

const double EPSILON = 1e-9;

bool compare(int k, int j, int i) {
    return height[k] + SQRT[i - k] - height[j] - SQRT[i - j] < -EPSILON;
}

void solve(double* result) {
    m = 0;
    for (int i = 0; i < n; ++ i) {
        if (m == 0) {
            start[0] = 0;
            choice[0] = 0;
            m ++;
        } else {
            while (start[m - 1] >= i && compare(choice[m - 1], i, start[m - 1])) {
                m --;
            } 
            int low = max(start[m - 1], i);
            int high = n;
            while (low < high) {
                int middle = (low + high) >> 1;
                if (compare(choice[m - 1], i, middle)) {
                    high = middle;
                } else {
                    low = middle + 1;
                }
            }
            if (high < n) {
                start[m] = high;
                choice[m] = i;
                m ++;
            }
        }
//for (int k = 0; k < m; ++ k) {
//    printf("(%d, %d), ", start[k], choice[k]);
//}
//puts("");
        int k = choice[upper_bound(start, start + m, i) - start - 1];
        result[i] = height[k] - height[i] + SQRT[i - k];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; ++ i) {
        SQRT[i] = sqrt((double)i);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", height + i);
    }
    memset(result, 0, sizeof(result));
    solve(result[0]);
    reverse(height, height + n);
    solve(result[1]);
    for (int i = 0; i < n; ++ i) {
        printf("%d\n", (int)ceil(max(result[0][i], result[1][n - 1 - i])));
    }
    return 0;
}
