#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        cout << "Case " << t << ": " << (a <= 20 && b <= 20 && c <= 20 ? "good" : "bad") << endl;
    }
    return 0;
}
