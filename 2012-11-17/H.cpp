#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int B = 100000;

char buffer[B], from[B], to[B];

int parse(char *text) {
    int n = strlen(text), y;
    text[n - 2] = '\0';
    sscanf(text, "%d", &y);
    if (text[n - 1] == 'C') {
        return 754 - y;
    }
    return 753 + y;
}

int solve(int n) {
    if (n) {
        int ret = solve(n / 10);
        int r = n % 10;
        if (r == 0) {
            ret += 0;
        } else if (r == 1) {
            ret += 1;
        } else if (r == 2) {
            ret += 2;
        } else if (r == 3) {
            ret += 3;
        } else if (r == 4) {
            ret += 2;
        } else if (r == 5) {
            ret += 1;
        } else if (r == 6) {
            ret += 2;
        } else if (r == 7) {
            ret += 3;
        } else if (r == 8) {
            ret += 4;
        } else if (r == 9) {
            ret += 2;
        }
        return ret;
    }
    return 0;
}

int main() {
    freopen("roman.in", "r", stdin);
    freopen("roman.out", "w", stdout);
    scanf("%s", buffer);
    for (int i = 0; buffer[i]; ++ i) {
        if (buffer[i] == '-') {
            buffer[i] = ' ';
        }
    }
    sscanf(buffer, "%s%s", from, to);
    int from_year = parse(from);
    int to_year = parse(to);
    int answer = 0;
    for (int year = from_year; year <= to_year; ++ year) {
        int ret = solve(year);
        answer = max(answer, ret);
    }
    printf("%d\n", answer);
    return 0;
}
