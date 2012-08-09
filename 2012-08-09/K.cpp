#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long LL;

const LL magic  =   37;
const LL base   =   1000000007;

const int maxn  =   100005;

LL h1[maxn],h2[maxn],pw[maxn];
char s[maxn];
int n,m;

inline LL calc(LL h[],int l,int r)
{
    LL res=h[r+1]-h[l]*pw[r-l+1]%base;
    if (res<0) res+=base;
    return res;
}

inline void read(LL h[],int &n)
{
    scanf("%s",s);
    n=strlen(s);
    h[0]=0;
    for (int i=0;i<n;++i){
        h[i+1]=(h[i]*magic+s[i]-'a'+1)%base;
    }
}

int main()
{
    read(h1,n);
    read(h2,m);
    pw[0]=1;
    for (int i=1;i<=100000;++i){
        pw[i]=pw[i-1]*magic%base;
    }
    
    int T;
    for (scanf("%d",&T);T--;){
        int i,j;
        scanf("%d%d",&i,&j);
        --i;--j;
        int l=0,r=min(n-i,m-j)+1;
        while (l+1<r){
            int mid=(l+r)/2;
            if (calc(h1,i,i+mid-1)==calc(h2,j,j+mid-1)) l=mid;
            else r=mid;
        }
        printf("%d\n",l);
    }
    return 0;
}

