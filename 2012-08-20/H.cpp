#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <complex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;


const int inf           =   1000000000;
const int maxFlowNode   =   1000+1000*1001/2+10;
const int maxFlowEdge   =   (1000*1001*2+1000)*2+100;

int head[maxFlowNode],next[maxFlowEdge],c[maxFlowEdge],vtx[maxFlowEdge],tot;
int d[maxFlowNode],pre[maxFlowNode],s,t,sign,flow;
int q[maxFlowNode];
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
    int h=0,tail=0;
    q[tail++]=s;
    for (int i=0;i<=t;++i) d[i]=inf;
    d[s]=0;
    sign=t;
    while (h<tail){
        int u=q[h++];
        for (int p=head[u];p;p=next[p])
        if (c[p] && d[vtx[p]]==inf){
            d[vtx[p]]=d[u]+1;
            if (vtx[p]==t) return true;
            q[tail++]=vtx[p];
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


int main()
{
    int T;
    for (scanf("%d",&T);T--;){
        int n;
        scanf("%d",&n);
        memset(head,0,sizeof(head));
        tot=2;
        s=n*(n+1)/2+n;
        t=s+1;
        int sum=0;
        for (int i=0;i<n;++i){
            for (int j=0;j<n;++j){
                int x;
                scanf("%d",&x);
                sum+=x;
                if (i>=j){
                    add(i*(i+1)/2+j,i+n*(n+1)/2,inf);
                    add(i*(i+1)/2+j,j+n*(n+1)/2,inf);
                }
                if (i>=j){
                    add(s,i*(i+1)/2+j,x);
                }else{
                    add(s,j*(j+1)/2+i,x);
                }
            }
        }
        for (int i=0;i<n;++i){
            int x;
            scanf("%d",&x);
            add(n*(n+1)/2+i,t,x);
        }
        flow=0;
        while (bfs()) dinic(s);
        sum-=flow;
        printf("%d\n",sum);
    }
    return 0;
}
