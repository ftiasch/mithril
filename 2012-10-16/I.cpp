#include <cstdio>
#include <cstring>
#include <set>
#include <map>
using namespace std;

const int N = 100000;

int n, x[N], y[N];
map <int, set <int> > xs, ys, xpy, xmy;

bool find(set <int> &s, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    set <int> :: iterator iter = s.lower_bound(a + 1);
    return iter != s.end() && *iter < b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", x + i, y + i);
        xs[x[i]].insert(y[i]);
        ys[y[i]].insert(x[i]);
        xpy[x[i] + y[i]].insert(x[i] - y[i]);
        xmy[x[i] - y[i]].insert(x[i] + y[i]);
    }
    int now_x = 0;
    int now_y = 0;
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        bool found = false;
        if (now_x == x[i]) {
            found = true;
            if (find(xs[now_x], now_y, y[i])) {
                break;
            }
        }
        if (now_y == y[i]) {
            found = true;
            if (find(ys[now_y], now_x, x[i])) {
                break;
            }
        }
        if (now_x + now_y == x[i] + y[i]) {
            found = true;
            if (find(xpy[now_x + now_y], now_x - now_y, x[i] - y[i])) {
                break;
            }
        }
        if (now_x - now_y == x[i] - y[i]) {
            found = true;
            if (find(xmy[now_x - now_y], now_x + now_y, x[i] + y[i])) {
                break;
            }
        }
        if (!found) {
            break;
        }
        xs[x[i]].erase(y[i]);
        ys[y[i]].erase(x[i]);
        xpy[x[i] + y[i]].erase(x[i] - y[i]);
        xmy[x[i] - y[i]].erase(x[i] + y[i]);
        now_x = x[i];
        now_y = y[i];
        result ++;
    }
    printf("%d\n", result);
    return 0;
}
