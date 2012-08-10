#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn  =   2000005;
const unsigned long long magic  =   37;

char s[maxn];
unsigned long long pw[maxn],h[maxn];

inline unsigned long long calc(int l,int r)
{
    return h[r+1]-h[l]*pw[r-l+1];
}

int main()
{
    scanf("%s",s);
    int n=strlen(s);
    for (int i=0;i<n;++i) s[i+n]=s[i];
    
    h[0]=0;
    pw[0]=1;
    for (int i=0;i<n+n;++i){
        h[i+1]=h[i]*magic+s[i]-'a'+1;
        pw[i+1]=pw[i]*magic;
    }
    
    int rank=1;
    for (int i=1;i<n;++i){
        int l=0,r=n+1;
        while (l+1<r){
            int mid=(l+r)>>1;
            if (calc(0,mid-1)==calc(i,i+mid-1)){
                l=mid;
            }else{
                r=mid;
            }
        }
        if (l<n && s[l]>s[i+l]){
            ++rank;
        }
    }
    
    printf("%d\n",rank);
    
    return 0;
}
