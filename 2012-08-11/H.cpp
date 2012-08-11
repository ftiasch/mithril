#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ULL;

const ULL magic =   37;
const int maxn  =   1000005;
const ULL base  =   1000000007;

ULL h[maxn],a[maxn];
char tmp[1000005];
int n;

inline ULL encode(char tmp[])
{
    ULL h=0;
    for (int i=0;tmp[i];++i){
        h=(h*magic+tmp[i]-'a'+1);
    }
    return h;
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%s",tmp);
        h[i]=encode(tmp);
        for (int j=0;tmp[j];++j){
            tmp[j]=(tmp[j]-'a'+13)%26+'a';
        }
        a[i]=encode(tmp);
    }
    
    sort(h,h+n);
    sort(a,a+n);
    int m=unique(a,a+n)-a;
    int ans=0;
    for (int i=0;i<m;++i){
        ULL x=a[i];
        int index=lower_bound(h,h+n,x)-h;
        if (index<n && h[index]==x){
            ++ans;
        }
    }
    printf("%d\n",ans);
    return 0;
}

