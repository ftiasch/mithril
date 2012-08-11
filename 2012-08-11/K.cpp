#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn  =   200005;

int f[maxn],pr[maxn],len,n,base;
int tree[maxn*4],pw[maxn];

inline void build(int num,int l,int r)
{
    if (l==r){
        pw[l]=0;
        tree[num]=1%base;
    }else{
        int mid=(l+r)>>1;
        build(num*2,l,mid);
        build(num*2+1,mid+1,r);
        tree[num]=(long long)tree[num*2]*tree[num*2+1]%base;
    }
}

inline int powmod(int x,int t)
{
    if (t==0) return 1%base;
    int y=powmod(x,t/2);
    y=(long long)y*y%base;
    if (t&1) y=(long long)y*x%base;
    return y;
}

inline void insert(int num,int l,int r,int pos,int delta)
{
    if (l==r){
        pw[l]+=delta;
        tree[num]=powmod(pr[l],pw[l]);
    }else{
        int mid=(l+r)/2;
        if (pos<=mid) insert(num*2,l,mid,pos,delta);
        else insert(num*2+1,mid+1,r,pos,delta);
        tree[num]=(long long)tree[num*2]*tree[num*2+1]%base;
    }
}

inline void mul(int x,int sign)
{
    while (x>1){
        int y=f[x],cnt=0;
        while (f[x]==y){
            x/=pr[y];
            ++cnt;
        }
//printf("%d %d\n",pr[y],cnt*sign);
        insert(1,0,len-1,y,sign*cnt);
    }
}

int main()
{
    scanf("%d%d",&n,&base);
    n-=2;
    int limit=2*n+1;
    memset(f,-1,sizeof(f));
    for (int i=2;i<=limit;++i)
    if (f[i]==-1){
        f[i]=len;
        if (i<=limit/i)
        for (int j=i*i;j<=limit;j+=i){
            if (f[j]==-1){
                f[j]=len;
            }
        }
        pr[len++]=i;
    }
    build(1,0,len-1);
    int ans=0;
    for (int i=1;i<=n;++i){
        ans+=tree[1];
        if (ans>=base) ans-=base;
        mul(2*i+1,1);
        mul(2,1);
        mul(i+2,-1);
//puts("_____________");
    }
    printf("%d\n",ans);
    
    return 0;
}

