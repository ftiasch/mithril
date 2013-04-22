#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

long long n,m;

inline bool check(long long z)
{
    long long sum=0, limit=n;
    for (int i=1;i<=m && sum<n;++i){
        limit=min(limit,(z-1)/i);
        sum+=limit;
    }
    return sum<n;
}

int main()
{
    cin >> n >> m;
    long long l=0,r=n+1;
    while (l+1<r){
        long long mid=(l+r)/2;
        if (check(mid)){
            l=mid;
        }else{
            r=mid;
        }
    }
    cout << l << endl;
    
    return 0;
}

