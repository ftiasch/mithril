#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn  =   2005;

int f[maxn],g[maxn],id[maxn],n,m,l[maxn],nl[maxn];
int mark[maxn];

inline bool cmp(const int &i,const int &j)
{
    return l[i]<l[j];
}

int main()
{
    scanf("%d%d",&m,&n);
    f[0]=n;
    l[0]=n;
    for (int i=2;i<=m;++i){
        for (int j=0;j<i-1;++j){
            id[j]=j;
//printf("%d:%d ",f[j],l[j]);
        }
//puts("");
        sort(id,id+(i-1),cmp);
        int s=0;
        for (int j=0;j<i-1 && j+j+2<=i;++j){
            s+=l[id[j]]+1;
        }
//printf("s=  %d\n",s);
        if (s>n){
            for (int j=i-1;j>0;--j){
                f[j]=f[j-1];
                l[j]=l[j-1];
            }
            f[0]=-1;
            l[0]=-1;
        }else{
            memset(g,0,sizeof(g));
            for (int j=0;j<i-1 && j+j+2<=i;++j){
                g[id[j]+1]=l[id[j]]+1;
            }
            
            for (int j=0;j<i-1;++j)
                mark[1+l[id[j]]]=-1;
            for (int j=0;j<i-1;++j)
                if (mark[1+l[id[j]]]==-1 || mark[1+l[id[j]]]>g[id[j]+1])
                     mark[1+l[id[j]]]=g[id[j]+1];
            for (int j=1;j<i;++j)
                nl[j]=mark[1+l[j-1]];
            g[0]=n-s;
            nl[0]=n-s;
            memcpy(f,g,sizeof(f));
            memcpy(l,nl,sizeof(l));
        }
    }
    printf("%d\n",f[0]);
    return 0;
}
