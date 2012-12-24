#include <cstdio>
#include <cstring>

int main()
{
    int tests;
    scanf("%d", &tests);
    for (int cas = 1; cas <= tests; ++cas) {
        int a, b;
        scanf("%d%d", &a, &b);
        double rounds = 0, winA = 0.0, winB = 0.0;
        double prob = 1.0;
        for (int it = 0; it < 1000; ++it) {
            int c = a < b ? a : b;
            prob *= 0.5;
            if (c == a) {
                winB += prob;
                rounds += prob * (it + 1);
            }
            if (c == b) {
                winA += prob;
                rounds += prob * (it + 1);
            }
            if (a == b) {
                break;
            }
            if (a < b) {
                b -= c;
                a += c;
            } else {
                b += c;
                a -= c;
            }
        }
        printf("Case %d: %.6f %.6f\n", cas, rounds, winA);
    }
}
