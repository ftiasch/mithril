#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 100000;

int n, a[N], s[N], pre[N];

long long gcd(long long a, long long b) {
    return b == 0? a: gcd(b, a % b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n - 1; ++ i) {
        s[i] = a[n - i] - a[n - 1 - i];
    }
    n --;
    pre[0] = pre[1] = 0;
    for (int i = 1; i + 1 <= n; ++ i) {
        pre[i + 1] = 0;
        int j = i;
        while (j != 0) {
            j = pre[j];
            if (s[j + 1] == s[i + 1]) {
                pre[i + 1] = j + 1;
                break;
            }
        }
    }
    int maxLen = 0;
    for (int i = 1; i <= n; ++ i) {
        maxLen = max(maxLen, pre[i]);
    }
    if (maxLen > 0) {
        int total = 0;
        long long totalSum = 0;
        for (int i = 1; i <= n; ++ i) {
            if (pre[i] == maxLen) {
                total ++;
                totalSum += s[i - maxLen];
            }
        }
        totalSum += (long long)a[n] * total;
        long long d = gcd(total, totalSum);
        total /= d;
        totalSum /= d;
        if (total < 0) {
            total *= -1;
            totalSum *= -1;
        }
        cout << totalSum << "/" << total << endl;
    } else {
        puts("impossible");
    }
    return 0;
}
