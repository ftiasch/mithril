#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

const double PI = acos(-1.0);

int n;
double a[11], b[22];

double eval(double x) {
    double ret = 0.0;
    for (int i = 2 * n + 1; i >= 0; -- i) {
        ret *= x;
        ret += b[i];
    }
    return ret;
}

int main() {
    int test_count = 0;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i <= n; ++ i) {
            scanf("%lf", a + i);
        }
        memset(b, 0, sizeof(b));
        for (int i = 0; i <= n; ++ i) {
            for (int j = 0; j <= n; ++ j) {
                b[i + j + 1] += PI * a[i] * a[j] / (i + j + 1);
            }
        }
        double x_low, x_high, inc;
        scanf("%lf%lf%lf", &x_low, &x_high, &inc);
        double volumn = eval(x_high) - eval(x_low);
        printf("Case %d: %.2f\n", ++ test_count, volumn);
        if (volumn < inc) {
            puts("insufficient volume");
        } else {
            std::vector <double> marks;
            marks.push_back(x_low);
            for (int i = 0; i < 8; ++ i) {
                double low = marks.back();
                double high = x_high + 1;
                for (int _ = 0; _ < 50; ++ _) {
                    double middle = (low + high) / 2.0;
                    if (eval(middle) - eval(marks.back()) > inc) {
                        high = middle;
                    } else {
                        low = middle;
                    }
                }
                double middle = (low + high) / 2.0;
                if (middle > x_high) {
                    break;
                }
                marks.push_back(middle);
            }
            for (int i = 1; i < (int)marks.size(); ++ i) {
                printf("%.2f%c", marks[i] - x_low, " \n"[i == (int)marks.size() - 1]);
            }
        }
    }
    return 0;

}
