#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn  =   400000;

int n,m,len,pr[100];
int a[maxn+1],f[maxn+1];
set<int> diff;

inline long long dfs(int step,int n,int mul,int sign)
{
    if (step==len){
        long long N=n/mul;
//printf("%d %lld\n",mul,N*(N+1)/2*mul*sign);
        return N*(N+1)/2*mul*sign;
    }
    long long res=dfs(step+1,n,mul,sign);
    if ((long long)mul*pr[step]<=n){
        res+=dfs(step+1,n,mul*pr[step],-sign);
    }
    return res;
}

inline long long solve(int n,int p)
{
    if (n<=0) return 0;
    len=0;
    while (p>1){
        int bak=f[p];
        pr[len++]=bak;
        while (f[p]==bak){
            p/=bak;
        }
    }
    return dfs(0,n,1,1);
}

int main()
{
    memset(f,-1,sizeof(f));
    for (int i=2;i<=maxn;++i){
        if (f[i]==-1){
            f[i]=i;
            if (i<=maxn/i)
            for (int j=i*i;j<=maxn;j+=i){
                if (f[j]==-1){
                    f[j]=i;
                }
            }
        }
    }
    int T;
    for (scanf("%d",&T);T;--T){
        scanf("%d%d",&n,&m);
        diff.clear();
        for (int i=0;i<m;++i){
            int op,x,y,p;
            scanf("%d%d%d",&op,&x,&y);
            if (op==1){
                scanf("%d",&p);
                
                long long ans=solve(y,p)-solve(x-1,p);
//printf("ans=  %lld    %lld\n",solve(y,p),solve(x-1,p));
                for (set<int>::iterator it=diff.begin();it!=diff.end();++it){
                    int pos=*it;
                    if (pos>=x && pos<=y){
                        if (__gcd(pos,p)==1) ans-=pos;
                        if (__gcd(a[pos],p)==1) ans+=a[pos];
                    }
                }
                
                printf("%lld\n",ans);
            }else{
                a[x]=y;
                diff.erase(x);
                if (a[x]!=x){
                    diff.insert(x);
                }
            }
        }
    }
    return 0;
}

