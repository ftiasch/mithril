#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int parseTime() {
    char buffer[10];
    scanf("%s", buffer);
    for (int i = 0; i < strlen(buffer); ++ i) {
        if (buffer[i] == ':') {
            buffer[i] = ' ';
        }
    }
    int min, sec;
    sscanf(buffer, "%d %d", &min, &sec);
    return min * 60 + sec;
}

int main() {
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        printf("Case %d: ", t);
        int a = parseTime();
        int b = parseTime();
        int c = parseTime();
        int d = parseTime();
        if (max(a, c) <= min(b, d)) {
            puts("Mrs Meeting");
        } else {
            puts("Hits Meeting");
        }
    }
    return 0;
}
