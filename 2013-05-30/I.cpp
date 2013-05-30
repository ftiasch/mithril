#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 10;
const double K = 0.097;
const double EPS = 1e-9;

int n;
double tank[N], pipe[N], height[N];

double solve(double pressure, double vol, double h, double l, double r, int mul = 1)
{
    for (int iter = 0; iter < 50; ++ iter) {
        double delta = (l + r) / 2.0;
        if (pressure * vol / (vol - delta) <= 1.0 + (tank[0] - h - mul * delta) * K) {
            l = delta;
        } else {
            r = delta;
        }
    }
    return l;
}

int main() {
    int test_count = 0;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++ i) {
            scanf("%lf", tank + i);
            height[i] = 0.0;
        }
        for (int i = 0; i < n - 1; ++ i) {
            scanf("%lf", pipe + i);
        }
        
        height[0] = tank[0];
        height[1] = pipe[0];
        double pressure = 1;
        for (int i = 1; i < n; ++ i) {
            double vol = tank[i] - height[i];
            for (int j = i + 1; j < n; ++ j) {
                vol += tank[j];
            }
            if (i + 1 < n) {
                double delta = solve(pressure, vol, height[i], 0, pipe[i] - height[i]);
                height[i] += delta;
                pressure = pressure * vol / (vol - delta);
                vol -= delta;
                
                if (height[i] >= pipe[i] - EPS) {
                    delta = solve(pressure, vol, height[i], 0, pipe[i], 0);
                    height[i + 1] += delta;
                    pressure = pressure * vol / (vol - delta);
                    vol -= delta;
                    
                    if (height[i + 1] >= pipe[i] - EPS) {
                        height[i] += solve(pressure, tank[i] - height[i], height[i], 0, tank[i] - height[i]);
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                height[i] += solve(pressure, tank[i] - height[i], height[i], 0, tank[i] - height[i]);
            }
        }

        double answer = 0.0;
        for (int i = 0; i < n; ++ i) {
            answer += height[i];
        }
        printf("Case %d: %.3f\n\n", ++ test_count, answer);
    }
    return 0;
}
