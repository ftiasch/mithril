#include <iostream>
using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;
    k ++;
    cout << 1 + (n - 2) * (k * (k - 1) / 2) + (n - 1) * k << endl;
    return 0;
}
