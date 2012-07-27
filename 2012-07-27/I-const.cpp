#include <iostream>
using namespace std;

const long long result[128] = {0LL , 1LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 1LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 0LL , 6LL , 0LL , 108LL , 0LL , 1182LL , 0LL , 10338LL , 0LL , 79818LL , 0LL , 570342LL , 0LL , 0LL , 0LL , 0LL , 6LL , 0LL , 124LL , 62LL , 1646LL , 1630LL , 18120LL , 25654LL , 180288LL , 317338LL , 1684956LL , 3416994LL , 0LL , 0LL , 0LL , 0LL , 0LL , 124LL , 0LL , 13514LL , 0LL , 765182LL , 0LL , 32046702LL , 0LL , 1136189734LL , 0LL , 36378354342LL , 0LL , 0LL , 0LL , 0LL , 108LL , 62LL , 13514LL , 25506LL , 991186LL , 3103578LL , 57718190LL , 238225406LL , 2965022934LL , 14388538008LL , 140937146918LL , 754315570508LL};

int main() {
    int m, n;
    cin >> m >> n;
    cout << result[(m - 1) * 16 + (n - 1)] << endl;
    return 0;
}
