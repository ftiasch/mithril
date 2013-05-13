#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>

int n;

struct Event {
    int type, x, y_1, y_2;

    Event(int type, int x, int y_1, int y_2) : type(type), x(x), y_1(y_1), y_2(y_2) {
    }
};

bool operator <(const Event &a, const Event &b) {
    return a.x < b.x;
}

const int N = 1000000;

int count[N], total[N];

void add(int t, int l, int r, int a, int b, int c) {
    if (b <= l || r <= a) {
        return;
    }
    if (a <= l && r <= b) {
        count[t] += c;
    } else {
        int m = l + r >> 1;
        add(t * 2, l, m, a, b, c);
        add(t * 2 + 1, m, r, a, b, c);
    }
    total[t] = r - l > 1 ? total[t * 2] + total[t * 2 + 1] : 0;
    if (count[t]) {
        total[t] = r - l;
    }
}

inline int getInt()
{
    char s[100];
    int ret = 0, cnt = 0, sign = 1;
    bool dot = false;
    scanf("%s", s);
    for (int i = 0; s[i]; ++ i) {
        if (s[i] == '-') {
            sign = -1;
        } else if (s[i] == '+') {
            sign = 1;
        } else if (s[i] == '.') {
            dot = true;
        } else if (isdigit(s[i])){
            ret = ret * 10 + s[i] - '0';
            if (dot) {
                ++ cnt;
            }
        }
    }
    while (cnt < 2) {
        ret *= 10;
        ++ cnt;
    }
    ret *= sign;
    return ret;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        std::vector <Event> events;
        for (int i = 0; i < n; ++ i) {
/*            double x_1, y_1, x_2, y_2;
            scanf("%lf%lf%lf%lf", &x_1, &y_1, &x_2, &y_2);*/
            int x_1 = getInt();
            int y_1 = getInt();
            int x_2 = getInt();
            int y_2 = getInt();
            events.push_back(Event(1, x_1, y_1, y_2));
            events.push_back(Event(-1, x_2, y_1, y_2));
        }
        std::sort(events.begin(), events.end());
        long long answer = 0;
        memset(count, 0, sizeof(count));
        memset(total, 0, sizeof(total));
        for (int i = 0; i < (int)events.size(); ++ i) {
            if (i) {
                answer += (long long)total[1] * (events[i].x - events[i - 1].x);
            }
            add(1, -100000, 100000, events[i].y_1, events[i].y_2, events[i].type);
        }
        printf("%.2f\n", answer / 10000.0);
    }
    return 0;
}
