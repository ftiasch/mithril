#include <cstdio>
#include <cstring>
#include <cstdlib>

int main()
{
    int n;
    scanf("%d", &n);
    int mad = 0;
    for (int i = 0, x; i < n; ++ i) {
        scanf("%d", &x);
        int seat = n - i + mad;
        double prob = (double)(seat - mad) / seat;
        if (x) {
            prob *= 1.0 / (seat - mad);
        }
        if (i) {
            printf(" ");
        }
        printf("%.10f", prob);
        mad += x;
    }
    puts("");
    return 0;
}
