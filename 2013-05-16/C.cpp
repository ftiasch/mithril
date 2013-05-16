#include <cstdio>
#include <cstring>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

int solve(int a, int b)
{
    if (a == 0 && b == 0) {
        return 0;
    }
    int a3 = a % 3, b3 = b % 3;
    if (a3 == b3) {
        return solve(a / 3, b / 3) * 3 + a3;
    }
    return solve(a / 3, b / 3) * 3 + (3 ^ a3 ^ b3);
}

int main()
{
    int n;
    scanf("%d", &n);
    int m = n * (n - 1) / 6;
    printf("%d\n", m);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int k = solve(i, j);
            if (k > j) {
                printf("%d %d %d\n", i + 1, j + 1, k + 1);
            }
        }
    }
}
