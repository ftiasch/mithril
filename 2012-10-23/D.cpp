#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

inline bool check(long long a,long long b,long long c)
{
    long long len=2;
    long long sum=0;
    int dep=1;
    while (sum+len<a){
        sum+=len;
        ++dep;
        len*=2;
    }
    long long st=len*2-1;
    if (b<st || (b-st)%(2*len)>=len){
        return false;
    }
    long long prefer=a-len+1;
    long long pos=(b-st)%(len*2);
    long long cc=st+2*len*((b-st)/(2*len))+len;
    for (int i=0;i<dep;++i){
        if ((prefer>>i&1)!=(pos>>i&1)){
            cc+=1LL<<i;
        }
    }
    return c==cc;
}

int main()
{
    long long a,b,c;
    for (;cin >> a >> b >> c;){
        if ((a|b|c)==0) break;
        if (a>c) swap(a,c);
        if (b>c) swap(b,c);
        if (a>b) swap(a,b);
        if (check(a,b,c)) puts("Bob wins the game.");
        else puts("Alice wins the game.");
    }
    return 0;
}

