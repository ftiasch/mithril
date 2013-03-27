#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

int get_step(int x, int y) {
    if (x < 2) {
        return 0;
    }
    (x -= 2) /= 3;
    y /= 3;
    int base = std::min(x, y);
    int value = base * 2 + 1;
    if (x == base && y != base) {
        return value + 1;
    }
    return value;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        int min_win = INT_MAX;
        int min_lose = INT_MAX;
        for (int i = 0, x, y; i < n; ++ i) {
            scanf("%d%d", &x, &y);
            int step = get_step(x, y);
            if (step & 1) {
                min_win = std::min(min_win, step);
            } else {
                min_lose = std::min(min_lose, step);
            }
        }
        printf("%s wins the game\n", min_win < min_lose ? "Andrew" : "Peter");
    }
    return 0;
}
//   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
//   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
//   1   1   1   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2
//   1   1   1   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2
//   1   1   1   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2   2
//   1   1   1   3   3   3   4   4   4   4   4   4   4   4   4   4   4   4   4   4
//   1   1   1   3   3   3   4   4   4   4   4   4   4   4   4   4   4   4   4   4
//   1   1   1   3   3   3   4   4   4   4   4   4   4   4   4   4   4   4   4   4
//   1   1   1   3   3   3   5   5   5   6   6   6   6   6   6   6   6   6   6   6
//   1   1   1   3   3   3   5   5   5   6   6   6   6   6   6   6   6   6   6   6
//   1   1   1   3   3   3   5   5   5   6   6   6   6   6   6   6   6   6   6   6
//   1   1   1   3   3   3   5   5   5   7   7   7   8   8   8   8   8   8   8   8
//   1   1   1   3   3   3   5   5   5   7   7   7   8   8   8   8   8   8   8   8
//   1   1   1   3   3   3   5   5   5   7   7   7   8   8   8   8   8   8   8   8
//   1   1   1   3   3   3   5   5   5   7   7   7   9   9   9  10  10  10  10  10
//   1   1   1   3   3   3   5   5   5   7   7   7   9   9   9  10  10  10  10  10
//   1   1   1   3   3   3   5   5   5   7   7   7   9   9   9  10  10  10  10  10
//   1   1   1   3   3   3   5   5   5   7   7   7   9   9   9  11  11  11  12  12
//   1   1   1   3   3   3   5   5   5   7   7   7   9   9   9  11  11  11  12  12
//   1   1   1   3   3   3   5   5   5   7   7   7   9   9   9  11  11  11  12  12
