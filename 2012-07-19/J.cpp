#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn      =   605;
const int maxm      =   50005*2*2;
const double eps    =   1e-11;
const double inf    =   1e100;

int head[maxn],vtx[maxm],next[maxm],tot;
double c[maxm],yuan[maxm],flow;
int d[maxn],pre[maxn],s,t,sign;
int n,m;

inline int fan(int x)
{
    if (x>n) return x-n;
    return x+n;
}

inline void add(int a,int b,double cc)
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
    sign=t;
    for (int i=1;i<=2*n;++i) d[i]=-1;
    d[s]=0;
    queue<int> q;
    q.push(s);
    while (q.size()){
        int u=q.front();
        q.pop();
        for (int p=head[u];p!=-1;p=next[p])
            if (c[p]>eps && d[vtx[p]]==-1){
                d[vtx[p]]=d[u]+1;
                if (vtx[p]==t) return true;
                q.push(vtx[p]);
            }
    }
    return false;
}

int mark[maxm],stamp=0;

inline void push()
{
    int u,p;
    double delta=inf,div=1;
    ++stamp;
    for (u=t;u!=s;u=vtx[p]){
        p=pre[u];
        delta=min(delta,c[p]);
        if (mark[p]==stamp) div=2;
        else{
            mark[p]=mark[p^2]=stamp;
        }
        p^=1;
    }
    //printf("%lf\n",delta);
    delta/=div;
    flow+=delta*2;
    for (u=t;u!=s;u=vtx[p]){
        //printf("%d ",u);
        p=pre[u];
        c[p]-=delta;
        c[p^1]+=delta;

        if (c[p^2]+eps<delta){
            puts("Wrong!");
            while (1);
        }
        c[p^2]-=delta;
        c[p^3]+=delta;

        p^=1;
    }

    for (u=t;u!=s;u=vtx[p]){
        if (c[p]<eps) sign=vtx[p^1];
        p^=1;
    }
    //puts("");
}

inline void dinic(int u)
{
    if (u==t) push();
    else{
        for (int p=head[u];p!=-1;p=next[p])
            if (c[p]>eps && d[vtx[p]]==d[u]+1){
                pre[vtx[p]]=p;
                dinic(vtx[p]);
                if (d[sign]<d[u]) return;
                sign=t;
            }
        d[u]=-1;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    tot=0;
    memset(head,-1,sizeof(head));
    for (int i=0;i<m;++i){
        int a,b;
        double c;
        scanf("%d%d%lf",&a,&b,&c);
        add(a,b,c);
        add(fan(b),fan(a),c);
    }

    s=1;t=n+1;
    flow=0;
    while (bfs()){
        //printf("%lf\n",flow);
        dinic(s);
    }

    printf("%.10f\n",flow);
    for (int i=0;i<tot;i+=4){
        if (i>0) printf(" ");
        printf("%.10f",yuan[i]-c[i]);
    }
    puts("");

    //printf("%lf\n",(double)clock()/CLOCKS_PER_SEC);
    return 0;
}

