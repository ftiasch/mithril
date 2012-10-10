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

const int maxm  =   2005;
const int maxn  =   25;

int n,m,k;
bool sel[maxn];
int a[maxm],b[maxm],c[maxm];
int id[maxm],pos[maxm];
vector<int> adj[maxn];
int next[maxm],pre[maxm];

inline bool cmp(const int &i,const int &j)
{
    return c[i]<c[j];
}

inline bool cmpPos(const int &i,const int &j)
{
    return pos[i]>pos[j];
}

int best;

int headEdge[maxn],nextEdge[maxm];

inline void add(int u,int e)
{
    nextEdge[e]=headEdge[u];
    headEdge[u]=e;
}

void dfs(int dep,int size,int head)
{
    if (dep==n-1 || size<=k){
        int times=size-k;
        int ptr=head;
        int sum=0;
        while (times>0){
            --times;
            sum+=c[ptr];
            if (sum>=best) return;
            ptr=next[ptr];
        }
        best=sum;
        return;
    }
    
    
    if (true){
        //target-side
        sel[dep]=false;
        //remove
        int del=0,nh=head;
        for (int eid=headEdge[dep];eid!=-1;eid=nextEdge[eid]){
            if (sel[a[eid]]!=sel[dep]) continue;
            ++del;
            int p=pre[eid];
            int n=next[eid];
            if (p!=-1) next[p]=n;
            if (n!=-1){
                pre[n]=p;
                if (p==-1){
                    nh=n;
                }
            }
        }
        dfs(dep+1,size-del,nh);
        //insert
        for (int eid=headEdge[dep];eid!=-1;eid=nextEdge[eid]){
            if (sel[a[eid]]!=sel[dep]) continue;
            int p=pre[eid];
            int n=next[eid];
            if (p!=-1) next[p]=eid;
            if (n!=-1) pre[n]=eid;
        }
    }
    
    if (true){
        //source-side
        sel[dep]=true;
        //remove
        int del=0,nh=head;
        for (int eid=headEdge[dep];eid!=-1;eid=nextEdge[eid]){
            if (sel[a[eid]]!=sel[dep]) continue;
            ++del;
            int p=pre[eid];
            int n=next[eid];
            if (p!=-1) next[p]=n;
            if (n!=-1){
                pre[n]=p;
                if (p==-1){
                    nh=n;
                }
            }
        }
        dfs(dep+1,size-del,nh);
        //insert
        for (int eid=headEdge[dep];eid!=-1;eid=nextEdge[eid]){
            if (sel[a[eid]]!=sel[dep]) continue;
            int p=pre[eid];
            int n=next[eid];
            if (p!=-1) next[p]=eid;
            if (n!=-1) pre[n]=eid;
        }
    }
}

int main()
{
    freopen("flow.in","r",stdin);
    freopen("flow.out","w",stdout);

    scanf("%d%d%d",&n,&m,&k);
    memset(headEdge,-1,sizeof(headEdge));
    for (int i=0;i<m;++i){
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
        --a[i];
        --b[i];
        if (a[i]>b[i]){
            swap(a[i],b[i]);
        }
        if (b[i]==n-1){
            swap(a[i],b[i]);
        }
        id[i]=i;
        add(b[i],i);
    }
//puts("hi~~~");fflush(stdout);
    sort(id,id+m,cmp);
    for (int i=0;i<m;++i){
        if (i) pre[id[i]]=id[i-1];
        else pre[id[i]]=-1;
        if (i+1<m) next[id[i]]=id[i+1];
        else next[id[i]]=-1;
    }

    best=2000000001;
    sel[0]=true;
    sel[n-1]=false;
    dfs(1,m,id[0]);
    
    printf("%d\n",best);
    
    return 0;
}

