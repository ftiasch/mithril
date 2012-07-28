#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    long long N,M,A,B,T;
    cin >> N >> M >> A >> B >> T;

    if (M<N) swap(N,M);
    if (M%N!=0){
        puts("0");
        return 0;
    }
    
    if (A==B){
        puts("-1");
        return 0;
    }
    
    if (M==N) M*=2;
    
//    cout << M << endl;
    
    if (A>B) swap(A,B);
    
    cout << T*M*(B-A)/(A*B)+1 << endl;
    return 0;
}
