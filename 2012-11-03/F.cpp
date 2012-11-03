#include <cstdio>
#include <cstring>
#include <cstdlib>

int n,p,k,d;
int a[10000];

inline bool solve()
{
    if (d==1){
        int x=p/k;
        int y=p%k;
        if (x>=y && (y==0 || n>k)){
            for (int i=0;i<k;++i){
                printf("%d\n",x);
            }
            if (n>k){
                printf("%d\n",y);
                for (int i=k+1;i<n;++i){
                    printf("%d\n",0);
                }
            }
            return true;
        }else{
            return false;
        }
    }else{
        int s=0;
        memset(a,0,sizeof(a));
        for (int i=0;i<d-1;++i){
            a[i]=d-1-i;
            s+=d-1-i;
        }
        if (s>p){
            return false;
        }
        a[0]+=p-s;
        for (int i=0;i<n;++i){
            printf("%d\n",a[i]);
        }
        return true;
    }
}

int main()
{
    freopen("final.in","r",stdin);
    freopen("final.out","w",stdout);
    
    scanf("%d%d%d%d",&n,&p,&k,&d);
    if (!solve()){
        puts("Wrong information");
    }
    return 0;
}

