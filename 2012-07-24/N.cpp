#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn  =   100005;
const int maxm  =   200006*2;

int head[maxn],vtx[maxm],next[maxm],prev[maxm],tot;
int n,m,mark[maxn],stamp;

inline void add(int a,int b)
{
    vtx[tot]=b;
    next[tot]=head[a];
    prev[head[a]]=tot;
    head[a]=tot++;
}

inline void remove(int p)
{
    int nxt=next[p],pre=prev[p];
    next[pre]=nxt;
    prev[nxt]=pre;
}

int level[maxn];

inline bool testOneRoad()
{
    stamp=0;
    memset(mark,0,sizeof(mark));
    for (int i=1;i<=n;++i){
        level[i]=i;
    }
    double limit=CLOCKS_PER_SEC*1.5;
    while (clock()<limit){
        ++stamp;
        random_shuffle(level+1,level+n+1);
        int s=1;
        for (int i=1;i<=n;++i)
        if (level[i]==1) s=i;
        
        for (int i=1;i<n;++i){
            mark[s]=stamp;
            bool found=false;
            int v=-1;
            for (int p=head[s];p;p=next[p]){
                if (mark[vtx[p]]!=stamp){
                    if (v==-1 || level[v]>level[vtx[p]]){
                        v=vtx[p];
                        found=true;
                    }
                }
            }
            if (!found) return false;
            s=v;
        }
    }
    return true;
}

int dfn[maxn],low[maxn],stack[maxn],cnt,top,cntB,d[maxn];

inline void dfs(int x,int father)
{
    dfn[x]=low[x]=++cnt;
    stack[++top]=x;
    for (int t=head[x];t;t=next[t]){
        if (dfn[vtx[t]]==0){
            int tmp=top;
            dfs(vtx[t],x);
            low[x]=min(low[x],low[vtx[t]]);
            if (low[vtx[t]]>=dfn[x]){
                ++cntB;
                top=tmp;
            }
        }else if (vtx[t]!=father){
            low[x]=min(low[x],dfn[vtx[t]]);
        }
    }
}

int main()
{
    srand(19911226);    
    scanf("%d%d",&n,&m);
    memset(head,0,sizeof(head));
    tot=2;
    for (int i=0;i<m;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
        ++d[a];
        ++d[b];
    }
    
    cntB=0;
    for (int i=1;i<=n && cntB<2;++i)
    if (dfn[i]==0) dfs(i,-1);
    
    if (cntB>1){
        puts("NO");
        return 0;
    }
    
    if (!testOneRoad()){
        puts("NO");
        return 0;
    }
    
    for (int i=1;i<=n;++i)
    if (d[i]!=d[1]){
        puts("NO");
        return 0;
    }
    
    puts("YES");

    
    return 0;
}
