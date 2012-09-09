#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long mySqrt(long long n) {
    long long r = max((long long)sqrt(n) - 5, 0LL);
    while ((r + 1) * (r + 1) <= n) {
        r ++;
    }
    return r;
}

long long count(long long n) {
    if (n < 6) {
        return 0;
    }
    long long result = 0;
    result += n / 2 - 2;
    long long r = mySqrt(n);
    if (r > 2) {
        if (r & 1) {
            result ++;
        }
    }
    return result;
}

int main() {
    int testCount;
    cin >> testCount;
    while (testCount > 0) {
        testCount --;
        long long a, b;
        cin >> a >> b;
        cout << count(b) - count(a - 1) << endl;
    }
    return 0;
}
