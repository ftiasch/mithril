#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 500000;
const int D = 1001;

int dx, dy, n, m, q, a[N], b[N];

struct Event {
    int a, b, d;

    Event(int a, int b, int d) : a(a), b(b), d(d) {}
};

bool operator < (const Event &u, const Event &v) {
    return u.a < v.a;
}

int weight[D][D], sum[D << 1];

int main() {
    int test_count = 0;
    while (scanf("%d%d%d%d", &dx, &dy, &n, &q) == 4 && dx) {
        for (int i = 0; i < n; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            a[i] = x - y;
            b[i] = x + y;
        }
        printf("Case %d:\n", ++ test_count);
        while (q --) {
            scanf("%d", &m);
            std::vector <Event> events;
            for (int i = 0; i < n; ++ i) {
                events.push_back(Event(a[i] - m, b[i] - m, 1));
                events.push_back(Event(a[i] - m, b[i] + m + 1, -1));
                events.push_back(Event(a[i] + m + 1, b[i] - m, -1));
                events.push_back(Event(a[i] + m + 1, b[i] + m + 1, 1));
            }
            std::sort(events.begin(), events.end());
            memset(sum, 0, sizeof(sum));
            int min_b = 2;
            int max_b = dx + dy;
            int zero = 0;
            for (int now_a = 1 - dy, i = 0; now_a <= dx - 1; ++ now_a) {
                while (i < (int)events.size() && events[i].a <= now_a) {
                    int eb = events[i].b;
                    if (eb <= max_b) {
                        if (eb < min_b) {
                            zero += events[i].d;
                        } else {
                            sum[eb] += events[i].d;
                        }
                    }
                    i ++;
                }
                int now_sum = zero;
                for (int now_b = min_b; now_b <= max_b; ++ now_b) {
                    now_sum += sum[now_b];
                    if ((now_a - now_b) % 2 == 0) {
                        int x = (now_b + now_a) / 2;
                        int y = (now_b - now_a) / 2;
                        if (1 <= x && x <= dx && 1 <= y && y <= dy) {
                            weight[x][y] = now_sum;
                        }
                    }
                }
            }
            int answer = -1;
            for (int y = 1; y <= dy; ++ y) {
                for (int x = 1; x <= dx; ++ x) {
                    if (weight[x][y] > answer) {
                        answer = weight[x][y];
                    }
                }
            }
            for (int y = 1; y <= dy; ++ y) {
                for (int x = 1; x <= dx; ++ x) {
                    if (weight[x][y] == answer) {
                        printf("%d (%d,%d)\n", answer, x, y);
                        answer = -1;
                    }
                }
            }
        }
    }
    return 0;
}
