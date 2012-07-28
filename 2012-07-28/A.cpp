#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}
};

bool operator <(const Point &a, const Point &b) { 
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool operator ==(const Point &a, const Point &b) { return a.x == b.x && a.y == b.y; }
Point operator -(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
int det(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }

const int N = 50;

int n, maxLow[N][N][2], aux[N][N][2], maxHigh[N][N][2], cnt[N];
Point points[N];

void update(int &x, int a) {
    x = max(x, a);
}

int turn(int i, int j, int k) {
    return det(points[j] - points[i], points[k] - points[j]);
}

void clear(int arr[N][N][2]) {
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            for (int k = 0; k < 2; ++ k) {
                arr[i][j][k] = INT_MIN;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }
    sort(points, points + n);
    int newN = 0;
    for (int i = 0; i < n; ++ i) {
        cnt[newN] = 0;
        points[newN] = points[i];
        int j = i;
        while (j < n && points[i] == points[j]) {
            j ++;
            cnt[newN] ++;
        }
        newN ++;
        i = j - 1;
    }
    n = newN;
    clear(maxLow);
    for (int start = 0; start < n; ++ start) {
        clear(aux);
        for (int i = start + 1; i < n; ++ i) {
            aux[start][i][0] = cnt[start] + cnt[i];
        }
        for (int i = start; i < n; ++ i) {
            for (int j = i + 1; j < n; ++ j) {
                for (int t = 0; t < 2; ++ t) {
                    if (aux[i][j][t] == INT_MIN) {
                        continue;
                    }
                    for (int k = j + 1; k < n; ++ k) {
                        if (turn(i, j, k) >= 0) {
                            update(aux[j][k][t | (turn(i, j, k) > 0)], aux[i][j][t] + cnt[k]);
                        }
                    }
                }
            }
        }
        for (int i = start; i < n; ++ i) {
            for (int j = i + 1; j < n; ++ j) {
                for (int t = 0; t < 2; ++ t) {
                    update(maxLow[start][j][t], aux[i][j][t]);
                }
            }
        }
    }
    clear(maxHigh);
    for (int start = 0; start < n; ++ start) {
        clear(aux);
        for (int i = 0; i < start; ++ i) {
            aux[start][i][0] = cnt[start] + cnt[i];
        }
        for (int i = start; i >= 0; -- i) {
            for (int j = i - 1; j >= 0; -- j) {
                for (int t = 0; t < 2; ++ t) {
                    if (aux[i][j][t] == INT_MIN) {
                        continue;
                    }
                    for (int k = j - 1; k >= 0; -- k) {
                        if (turn(i, j, k) >= 0) {
                            update(aux[j][k][t | (turn(i, j, k) > 0)], aux[i][j][t] + cnt[k]);
                        }
                    }
                }
            }
        }
        for (int i = start - 1; i >= 0; -- i) {
            for (int j = i - 1; j >= 0; -- j) {
                for (int t = 0; t < 2; ++ t) {
                    update(maxHigh[start][j][t], aux[i][j][t]);
                }
            }
        }
    }
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        update(result, cnt[i]);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            for (int lowT = 0; lowT < 2; ++ lowT) {
                for (int highT = 0; highT < 2; ++ highT) {
                    if (lowT == 0 && highT == 0) {
                        update(result, maxLow[i][j][0]);
                    } else if (maxLow[i][j][lowT] != INT_MIN && maxHigh[j][i][highT] != INT_MIN) {
                        update(result, maxLow[i][j][lowT] + maxHigh[j][i][highT] - cnt[i] - cnt[j]);
                    }
                }
            }
        }
    }
    printf("%d\n", result);
    return 0;
}
