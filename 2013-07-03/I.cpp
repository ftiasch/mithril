#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn = 500;

int n, m, h[maxn][maxn], h0;
int maximum[maxn], left[maxn], right[maxn];

inline long long solve(int a, int b)
{
    long long ret = 0;
    for (int upper = 0; upper < n; ++ upper) {
        for (int i = 0; i < m; ++ i) {
            maximum[i] = 0;
        }
        for (int down = upper; down < n && down < upper + a; ++ down) {
            for (int i = 0; i < m; ++ i) {
                maximum[i] = max(maximum[i], h[down][i]);
            }
            for (int i = 0; i < m; ++ i) {
                left[i] = i - 1;
                while (left[i] >= 0 && maximum[i] >= maximum[left[i]]) {
                    left[i] = left[left[i]];
                }
            }
            for (int i = m - 1; i >= 0; -- i) {
                right[i] = i + 1;
                while (right[i] < m && maximum[i] >= maximum[right[i]]) {
                    right[i] = right[right[i]];
                }
            }
            for (int i = 0; i < m; ++ i) {
                int len = right[i] - left[i] - 1;
                if (len > b) {
                    len = b;
                }
                long long limit = h0 - maximum[i];
                limit *= n * m;
                long long div = n * m - (down - upper + 1) * len;
                long long x = limit / div;
                if (limit % div == 0) {
                    -- x;
                }
                ret = max(ret, x * (down - upper + 1) * len);
            }
        }
    }
    return ret;
}

int main()
{
    int a, b;
    scanf("%d%d%d%d", &a, &b, &n, &m);
    h0 = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            scanf("%d", &h[i][j]);
            h0 = max(h0, h[i][j]);
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            h[i][j] = h0 - h[i][j];
        }
    }
    
    printf("%lld\n", max(solve(a, b), solve(b, a)));
    
    return 0;
}

