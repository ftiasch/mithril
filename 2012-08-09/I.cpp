#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long a, b,d,x;
for (;cin >> a >> b;){
    if (a>b){
        cout << 0 << endl;
        goto Break;
    }
    
    d=b-a;
    x=1;
    while (d>0 && d%2==0){
        x*=2;
        d/=2;
    }
    
    if (a == b) {
        cout << 1 << endl;
    } else {
        cout << x+1 << endl;
    }
Break:;
}
    
    return 0;
}
