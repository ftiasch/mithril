#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn  =   100005;

int a[maxn],b[maxn],n,m;

int main()
{
    freopen("electricity.in","r",stdin);
    freopen("electricity.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i){
        scanf("%d",&a[i]);
    }
    sort(a,a+n);
    reverse(a,a+n);
    for (int i=0;i<m;++i){
        scanf("%d",&b[i]);
    }
    sort(b,b+m);
    reverse(b,b+m);
    
    int ca=1,cb=0;
    int ans=0;
    bool change=true;
    for (int i=0,j=0;change;){
        ans=max(ans,ca);
        change=false;
        if (cb>0 && j<m && !change){
            ca+=b[j++];
            cb--;
            change=true;
        }
        if (ca>0 && i<n && !change){
            cb+=a[i++];
            ca--;
            change=true;
        }
    }
    printf("%d\n",ans);
    return 0;
}

