#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long Long;

const int N = 100000;

int n;
short c[N];
int x[N][2], y[N][2];
vector <int> yvalues;

bool state[N];

int color[N << 3][3];
int length[N << 3][8];
long long result[8];

void build(int t, int l, int r) {
    for (int i = 0; i < 3; ++ i) {
        color[t][i] = 0;
    }
    length[t][0] = yvalues[r] - yvalues[l];
    for (int mask = 1; mask < 8; ++ mask) {
        length[t][mask] = 0;
    }
    if (l + 1 < r) {
        int m = (l + r) >> 1;
        build(t << 1, l, m);
        build((t << 1) + 1, m, r);
    }
}

void cover(int t, int l, int r, int a, int b, int c, int d) {
    if (b <= yvalues[l] || yvalues[r] <= a) {
        return;
    }
    if (a <= yvalues[l] && yvalues[r] <= b) {
        color[t][c] += d;
    } else {
        int m = (l + r) >> 1;
        cover(t << 1, l, m, a, b, c, d);
        cover((t << 1) + 1, m, r, a, b, c, d);
    }
    int coverMask = 0;
    for (int i = 0; i < 3; ++ i) {
        if (color[t][i] > 0) {
            coverMask |= 1 << i;
        }
    }
    if (l + 1 == r) {
        for (int mask = 0; mask < 8; ++ mask) {
            length[t][mask] = 0;
        }
        length[t][coverMask] = yvalues[r] - yvalues[l];
    } else {
        for (int mask = 0; mask < 8; ++ mask) {
            length[t][mask] = 0;
        }
        for (int mask = 0; mask < 8; ++ mask) {
            length[t][mask | coverMask] += length[t << 1][mask];
            length[t][mask | coverMask] += length[(t << 1) + 1][mask];
        }
    }
}

int main() {
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        scanf("%d", &n);
        yvalues.clear();
        for (int i = 0; i < n; ++ i) {
            char buffer[2];
            scanf("%s%d%d%d%d", buffer, &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
            if (*buffer == 'R') {
                c[i] = 0;
            } 
            if (*buffer == 'G') {
                c[i] = 1;
            }
            if (*buffer == 'B') {
                c[i] = 2;
            }
            yvalues.push_back(y[i][0]);
            yvalues.push_back(y[i][1]);
        }
        sort(yvalues.begin(), yvalues.end());
        yvalues.erase(unique(yvalues.begin(), yvalues.end()), yvalues.end());
        vector <pair <int, int> > events;
        for (int i = 0; i < n; ++ i) {
            events.push_back(make_pair(x[i][0], i));
            events.push_back(make_pair(x[i][1], i));
        }
        sort(events.begin(), events.end());
        memset(state, 0, sizeof(state));
        int max = (int)yvalues.size() - 1;
        memset(result, 0, sizeof(result));
        build(1, 0, max);
        for (int k = 0; k < (int)events.size(); ++ k) {
            int id = events[k].second;
            if (k > 0) {
                long long width = events[k].first - events[k - 1].first;
                if (width > 0) {
                    for (int mask = 1; mask < 8; ++ mask) {
                        result[mask] += length[1][mask] * width;
                    }
                }
            }
            cover(1, 0, max, y[id][0], y[id][1], c[id], state[id]? -1: 1);
            state[id] ^= 1;
        }
        printf("Case %d:\n", t);
        cout << result[1] << endl;
        cout << result[2] << endl;
        cout << result[4] << endl;
        cout << result[3] << endl;
        cout << result[5] << endl;
        cout << result[6] << endl;
        cout << result[7] << endl;
    }
    return 0;
}
