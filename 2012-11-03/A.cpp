#nclude <cstdio>
#include <iostream>
using namespace std;

long long n;

int main() {
    freopen("aztec.in", "r", stdin);
    freopen("aztec.out", "w", stdout);
    cin >> n;
    long long step = 1;
    long long result = 0;
    while (step <= n) {
        result ++;
        n -= step;
        step += 4 * result;
    }
    cout << result << endl;
    return 0;
}
