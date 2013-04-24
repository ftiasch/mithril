#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn  =   100005;
const int maxnode   =   maxn+maxn+2;
const int maxedge   = (100005 + maxnode) * 2 + 5;

int head[maxnode],vtx[maxedge],next[maxedge],c[maxedge],yuan[maxedge],tot;
int d[maxnode],pre[maxnode],s,t,flow,sign;
int n,m,cap[maxn],ans[maxn];
vector<int> adj[maxn];

inline void add(int a,int b,int cc)
{
    vtx[tot]=b;
    next[tot]=head[a];
    c[tot]=cc;
    yuan[tot]=cc;
    head[a]=tot++;
    
    vtx[tot]=a;
    next[tot]=head[b];
    c[tot]=0;
    yuan[tot]=0;
    head[b]=tot++;
}

inline bool bfs()
{
    queue<int> q;
    q.push(t);
    memset(d,-1,sizeof(d));
    d[t]=0;
    while (q.size()){
        int u=q.front();
        q.pop();
        for (int p=head[u];p;p=next[p]){
            if (c[p^1] && d[vtx[p]]==-1){
                q.push(vtx[p]);
                d[vtx[p]]=d[u]+1;
            }
        }
    }
    return d[s]!=-1;
}

inline void push()
{
    for (int u=t,p;u!=s;u=vtx[p]){
        p=pre[u];
        --c[p];
        if (!c[p]){
            sign=vtx[p^1];
        }
        ++c[p^=1];
    }
    ++flow;
}

inline void dinic(int u)
{
    if (u==t){
        push();
    }else{
        for (int p=head[u];p;p=next[p]){
            if (c[p] && d[vtx[p]]==d[u]-1){
                pre[vtx[p]]=p;
                dinic(vtx[p]);
                if (d[sign]>d[u]){
                    return;
                }
                sign=t;
            }
        }
        d[u]=-1;
    }
}

inline bool check(int limit)
{
    s=n+m;
    t=s+1;
    sign=t;
    memset(head,0,sizeof(head));
    tot=2;
    for (int i=0;i<limit;++i){
        add(s,i,1);
        for (int j=0;j<adj[i].size();++j){
            add(i,adj[i][j]+n,1);
        }
    }
    for (int i=0;i<m;++i){
        add(i+n,t,cap[i]);
    }
    
    flow=0;
    while (bfs()){
        dinic(s);
    }
    return flow == limit;
}

int main()
{
    //srand(time(0));
    scanf("%d%d",&n,&m);
    //n=rand()%10000+1;
    //m=rand()%10000+1;
    for (int i=0;i<m;++i){
        scanf("%d",&cap[i]);
        //cap[i]=rand()%10000+1;
    }
    for (int i=0;i<n;++i){
        int x;
        scanf("%d",&x);
        //x=rand()%10+1;
        adj[i].resize(x);
        for (int j=0;j<x;++j){
            scanf("%d",&adj[i][j]);
            //adj[i][j]=rand()%m+1;
            --adj[i][j];
        }
    }
    
    int l=0,r=n+1;
    while (l+1<r){
        int mid=(l+r)/2;
        if (check(mid)){
            l=mid;
        }else{
            r=mid;
        }
    }
//printf("ans = %d\n",l);
    check(l);
    
    for (int i=l;i<n;++i){
        add(s,i,1);
        for (int j=0;j<adj[i].size();++j){
            add(i,adj[i][j]+n,1);
        }
    }
    while (bfs()){
        dinic(s);
    }
    
    for (int i=0;i<n;++i){
        ans[i]=0;
        for (int p=head[i];p;p=next[p]){
            int v=vtx[p];
            if (v>=n && v<n+m && c[p]==0 && yuan[p]==1){
                ans[i]=v-n+1;
                break;
            }
        }
    }
    
    for (int i=0;i<n;++i){
        if (i) printf(" ");
        printf("%d",ans[i]);
    }
    puts("");
    
    return 0;
}

