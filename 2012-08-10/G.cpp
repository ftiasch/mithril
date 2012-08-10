#include <cstdio>
#include <cstring>
using namespace std;

static const int N = 16;

int n;
bool visit[1 << N];

void printMask(int mask) {
    for (int i = 0; i < n; ++ i) {
        putchar('0' + (mask >> i & 1));
    }
    puts("");
}

void construct(int mask) {
    if (!visit[mask]) {
        visit[mask] = true;
        int ones = mask;
        while (ones) {
            int i = ones & -ones;
            construct(mask ^ i);
            ones ^= i;
        }
        printMask(mask);
    }
}

int main() {
    scanf("%d", &n);
    memset(visit, 0, sizeof(visit));
    visit[0] = true;
    for (int i = 0; i < n; ++ i) {
        int id = i;
        construct(((1 << n) - 1) ^ (1 << id));
    }
    return 0;
}
