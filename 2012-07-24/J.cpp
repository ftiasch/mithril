#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

typedef long long LL;

const int maxn  =   100005;

int n,a[maxn],b[maxn],p,total[maxn];
bool vis[maxn];

int main()
{
//while (1){
//srand(time(0)^123613761);
//    n=10,p=1000000000;
    scanf("%d%d",&n,&p);
    for (int i=1;i<=n;++i){
//        a[i]=i;
        scanf("%d",&a[i]);
        b[i]=i;
    }
//    random_shuffle(a+1,a+n+1);
//for (int i=1;i<=n;++i) printf("%d ",a[i]);
//puts("");
    
    int ans=0;
/*    do{
        bool ok=true;
        for (int i=1;i<=n;++i)
        if (a[b[i]]!=b[a[i]]) ok=false;

        ans+=ok;
    }while (next_permutation(b+1,b+1+n));
    
    printf("std=    %d\n",ans%p);
    int bak=ans%p;*/
    
    ans=1;
    int s=n;
    memset(vis,0,sizeof(vis));
    memset(total,0,sizeof(total));
    for (int i=1;i<=n;++i)
    if (!vis[i]){
        int j=i,cnt=0;
        while (!vis[j]){
            vis[j]=true;
            j=a[j];
            ++cnt;
        }
        if (cnt>1){
            ans=(LL)ans*cnt%p;
        }
//printf("%d\n",cnt);
        ++total[cnt];
    }
    
    for (int i=1;i<=n;++i)
        for (int j=1;j<=total[i];++j)
            ans=(LL)ans*j%p;

    printf("%d\n",ans);
    
    
/*    if (ans!=bak){
        puts("WA");
        while (1);
    }
}*/
    
    return 0;
}
