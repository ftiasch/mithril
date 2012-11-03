#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000;

int n;
long long data[N][2];
pair <int, int> points[N];

bool mark[N];

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long result[2][3];

int main() {
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &points[i].first, &points[i].second);
    }
    sort(points, points + n);
    for (int i = 0; i < n; ++ i) {
        data[i][0] = points[i].first;
        data[i][1] = points[i].second;
    }
    for (int t = 0; t < 2; ++ t) {
        for (int i = 0; i < 3; ++ i) {
            for (int j = i + 1; j < 3; ++ j) {
                memset(mark, 0, sizeof(mark));
                long long start_x = data[i][0];
                long long start_y = data[i][1];
                long long delta_x = data[j][0] - data[i][0];
                long long delta_y = data[j][1] - data[i][1];
                long long x = start_x;
                long long y = start_y;
                for (int k = 0; k < n; ++ k) {
                    if (data[k][0] == x && data[k][1] == y) {
                        mark[k] = true;
                        x += delta_x;
                        y += delta_y;
                    }
                }
                delta_x = 0;
                delta_y = 0;
                int first = -1;
                int last = -1;
                for (int k = 0; k < n; ++ k) {
                    if (!mark[k]) {
                        if (last != -1) {
                            delta_x = gcd(abs(delta_x), abs(data[k][0] - data[last][0]));
                            if (data[k][0] - data[last][0] < 0) {
                                delta_x *= -1;
                            }
                            delta_y = gcd(abs(delta_y), abs(data[k][1] - data[last][1]));
                            if (data[k][1] - data[last][1] < 0) {
                                delta_y *= -1;
                            }
                        } else {
                            first = k;
                        }
                        last = k;
                    }
                }
                result[t][2] = abs(data[j][t] - data[i][t]);
                if (result[t][2] == 0) {
                    continue;
                }
                result[t][0] = INT_MAX;
                result[t][1] = INT_MIN;
                for (int k = 0; k < n; ++ k) {
                    if (mark[k]) {
                        result[t][0] = min(result[t][0], data[k][t]);
                        result[t][1] = max(result[t][1], data[k][t]);
                    }
                }
                if (first == -1) {
                    result[t ^ 1][0] = INT_MAX;
                    result[t ^ 1][1] = INT_MIN;
                    result[t ^ 1][2] = abs(data[1][t ^ 1] - data[0][t ^ 1]);
                    for (int k = 0; k < n; ++ k) {
                        result[t ^ 1][0] = min(result[t ^ 1][0], data[k][t ^ 1]);
                        result[t ^ 1][1] = max(result[t ^ 1][1], data[k][t ^ 1]);
                    }
                    if (result[t ^ 1][2] == 0) {
                        result[t ^ 1][0] ++;
                        result[t ^ 1][1] ++;
                        result[t ^ 1][2] = 1;
                    }
                    cout << result[0][0] << " " << result[0][1] << " " << result[0][2] << " " << result[1][0] << " " << result[1][1] << " " << result[1][2] << endl;
                    return 0;
                } else {
                    long long start_x = data[first][0];
                    long long start_y = data[first][1];
                    long long x = start_x;
                    long long y = start_y;
                    for (int k = 0; k < n; ++ k) {
                        if (data[k][0] == x && data[k][1] == y) {
                            mark[k] = true;
                            x += delta_x;
                            y += delta_y;
                        }
                    }
                    x -= delta_x;
                    y -= delta_y;
                    result[t ^ 1][0] = (t ^ 1) ? start_y : start_x;
                    result[t ^ 1][1] = (t ^ 1) ? y : x;
                    result[t ^ 1][2] = abs((t ^ 1) ? delta_y : delta_x);
                    if (result[t ^ 1][0] > result[t ^ 1][1]) {
                        swap(result[t ^ 1][0], result[t ^ 1][1]);
                    }
                    if (result[t ^ 1][2] == 0) {
                        result[t ^ 1][2] = 1;
                    }
                    bool valid = true;
                    for (int k = 0; k < n; ++ k) {
                        valid &= mark[k];
                    }
                    if (valid) {
                        cout << result[0][0] << " " << result[0][1] << " " << result[0][2] << " " << result[1][0] << " " << result[1][1] << " " << result[1][2] << endl;
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}
