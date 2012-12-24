#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

const double eps = 1e-11;
const int maxn = 100;

#define time time_

int n, q;
int chargeSpeed;
int capacity[maxn], time[maxn], remain[maxn];

int main()
{
    int cas = 0;
    while (scanf("%d%d", &n, &q) == 2 && n) {
        scanf("%d", &chargeSpeed);
        double sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", capacity + i, time + i, remain + i);
            double droppingSpeed = (double)capacity[i] / time[i];
            sum += droppingSpeed / chargeSpeed;
        }
        printf("Case %d:\n", ++cas);
        printf("%d\n", (int)ceil(sum - eps));
        for (int i = 0; i < q; i++) {
            int chargers;
            scanf("%d", &chargers);
            double lo = 0, hi = 110000;
            for (int it = 0; it < 64; ++it) {
                double mid = (lo + hi) / 2.0;
                double sum = 0;
                bool valid = true;
                for (int j = 0; j < n; j++) {
                    double droppingSpeed = (double)capacity[j] / time[j];
                    double num = std::max(0.0, (droppingSpeed - (double)remain[j] / mid) / chargeSpeed);
                    if (num > 1) {
                        valid = false;
                        break;
                    }
                    sum += num;
                }
                if (valid && sum <= chargers) {
                    lo = mid;
                } else {
                    hi = mid;
                }
            }
            if (lo >= 100000) {
                puts("-1.000");
            } else {
                printf("%.3f\n", lo);
            }
        }
    }
}
