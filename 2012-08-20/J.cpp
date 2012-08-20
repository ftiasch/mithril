#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;

const int maxEdge   =   1005;

struct Edge
{
    int a,b,p,w,id;
    Edge(){}
    inline void read()
    {
        scanf("%d%d%d%d",&a,&b,&w,&p);
        --a;--b;
    }
}e[maxEdge];
int sum[1<<12],cost[12],order[1<<12];
int population[105];

inline bool cmp(const int &i,const int &j)
{
    return sum[i]<sum[j];
}

const int inf           =   1000000000;
const int maxFlowNode   =   105+1005+5;
const int maxFlowEdge   =   1005*3*2+5+105*2;

int head[maxFlowNode],next[maxFlowEdge],c[maxFlowEdge],vtx[maxFlowEdge],tot;
int d[maxFlowNode],pre[maxFlowNode],s,t,sign,flow;
int n,m;

inline void add(int a,int b,int cc)
{
    vtx[tot]=b;
    next[tot]=head[a];
    c[tot]=cc;
    head[a]=tot++;
    
    vtx[tot]=a;
    next[tot]=head[b];
    c[tot]=0;
    head[b]=tot++;
}

inline bool bfs()
{
    queue<int> q;
    q.push(s);
    for (int i=0;i<=t;++i) d[i]=inf;
    d[s]=0;
    sign=t;
    while (q.size()){
        int u=q.front();
        q.pop();
        for (int p=head[u];p;p=next[p])
        if (c[p] && d[vtx[p]]==inf){
            d[vtx[p]]=d[u]+1;
            if (vtx[p]==t) return true;
            q.push(vtx[p]);
        }
    }
    return false;
}

inline void push()
{
    int delta=inf,u,p;
    for (u=t;u!=s;u=vtx[p]){
        p=pre[u];
        delta=min(delta,c[p]);
        p^=1;
    }
    
    for (u=t;u!=s;u=vtx[p]){
        p=pre[u];
        c[p]-=delta;
        c[p^1]+=delta;
        if (!c[p]) sign=vtx[p^1];
        p^=1;
    }
    
    flow+=delta;
}

inline void dinic(int u)
{
    if (u==t) push();
    else{
        for (int p=head[u];p;p=next[p])
        if (c[p] && d[u]+1==d[vtx[p]]){
            pre[vtx[p]]=p;
            dinic(vtx[p]);
            if (d[sign]<d[u]) return;
            sign=t;
        }
        d[u]=-1;
    }
}

inline int calc(int mask)
{
    tot=2;
    memset(head,0,sizeof(head));
    s=n+m;t=s+1;
    for (int i=0;i<n;++i)
        add(s,i,population[i]);
    for (int i=0;i<m;++i){
        if (e[i].p<=0 || (mask>>e[i].id&1)){
            add(e[i].a,i+n,inf);
            add(i+n,e[i].b,inf);
            if (e[i].p<0){
                add(i+n,t,e[i].w);
            }
        }else{
            add(e[i].a,i+n,1);
            add(i+n,e[i].b,1);
        }
    }
    flow=0;
    while (bfs()) dinic(s);
    return flow;
}

int main()
{
    for (;scanf("%d%d",&n,&m)==2;){
        for (int i=0;i<n;++i){
            scanf("%d",&population[i]);
        }
        int N=0;
        for (int i=0;i<m;++i){
            e[i].read();
            if (e[i].p>0){
                cost[N]=e[i].w;
                e[i].id=N++;
            }else e[i].id=0;
        }
        
        int target=calc((1<<N)-1);
        
        for (int mask=0;mask<1<<N;++mask){
            sum[mask]=0;
            for (int i=0;i<N;++i)
            if (mask>>i&1){
                sum[mask]+=cost[i];
            }
            order[mask]=mask;
        }
        sort(order,order+(1<<N),cmp);
        
        int ans=sum[(1<<N)-1];
        for (int i=0;i<1<<N;++i){
            if (calc(order[i])==target){
                ans=sum[order[i]];
                break;
            }
        }
        if (target==0) puts("Poor Heaven Empire");
        else printf("%d %d\n",target,ans);
    }
    return 0;
}

