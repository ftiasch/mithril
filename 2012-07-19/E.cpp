#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define lowbit(x) ((x)&(-(x)))

const int maxk  =   105;
const int maxn  =   30;

struct node
{
    int e,h,d,r;
}level[maxk],monster[maxn];

inline bool operator <(const node &a,const node &b)
{
    return a.e<b.e;
}

bool f[1<<20];
int ind[1<<20],sExp[1<<20],sl[1<<20],n,k,pre[1<<20];

inline void print(int stat)
{
    if (stat==0) return;
    int x=pre[stat];
    print(stat^(1<<x));
    if (stat!=(1<<x)) printf(" ");
    printf("%d",x+1);
}

int main()
{
    scanf("%d%d",&n,&k);
    for (int i=0;i<k;++i){
        scanf("%d%d%d%d",&level[i].e,&level[i].h,&level[i].d,&level[i].r);
    }
    for (int i=0;i<n;++i){
        scanf("%d%d%d",&monster[i].h,&monster[i].d,&monster[i].e);
        ind[1<<i]=i;
    }
    sExp[0]=0;sl[0]=0;
    for (int i=1;i<1<<n;++i){
        sExp[i]=sExp[i-lowbit(i)]+monster[ind[lowbit(i)]].e;
        node tmp; tmp.e=sExp[i];
        sl[i]=(upper_bound(level,level+k,tmp)-level)-1;
    }
    memset(f,false,sizeof(f));
    f[0]=true;
    int ans=0,ansp=0;
    for (int i=0;i<1<<n;++i)
    if (f[i]){
        if (sExp[i]>ans){
            ans=sExp[i];
            ansp=i;
        }
        int l=sl[i];
        for (int j=0;j<n;++j)
        if (!(i>>j&1) && !f[i|(1<<j)]){
            bool ok=false;
            
            int d2=monster[j].d-level[l].r;
            if (d2<=0){
                int nl=sl[i|(1<<j)],hp=level[l].h;
                hp+=level[nl].h-level[l].h;
                if (hp<=0) ok=false;
                else ok=true;
            }else{
                int d1=level[l].d;
                int t1=(monster[j].h+d1-1)/d1,t2=(level[l].h+d2-1)/d2;
                long long hp=level[l].h-(long long)d2*t1;
//printf("%d %d %d %d\n",i,j,t1,d2);
                if (hp<=0){
                    ok=false;
                }else{
                    int nl=sl[i|(1<<j)];
                    hp+=level[nl].h-level[l].h;
                    if (hp<=0) ok=false;
                    else ok=true;
                }
            }
            
            if (ok){
                f[i|(1<<j)]=true;
                pre[i|(1<<j)]=j;
            }
        }
    }
    printf("%d\n",ans);
    printf("%d\n",__builtin_popcount(ansp));
    if (ansp){
        print(ansp);
        puts("");
    }
    
    return 0;
}
