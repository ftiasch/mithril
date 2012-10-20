#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn  =   505;

int x[maxn],y[maxn],z[maxn],p[maxn],n,k;
int match[maxn],mark[maxn],stamp;
vector<int> adj[maxn];

inline int dist(int i,int j)
{
    return abs(x[i]-x[j])+abs(y[i]-y[j])+abs(z[i]-z[j]);
}

inline bool aug(int u)
{
    for (int i=0;i<adj[u].size();++i){
        int v=adj[u][i];
        if (mark[v]==stamp){
            continue;
        }
        mark[v]=stamp;
        if (match[v]==-1 || aug(match[v])){
            match[u]=v;
            match[v]=u;
            return true;
        }
    }
    return false;
}

inline int calc(int limit)
{
    for (int i=0;i<n;++i){
        adj[i].clear();
        for (int j=0;j<n;++j){
            if (dist(i,j)==1 && p[i]+p[j]>=limit){
                adj[i].push_back(j);
            }
        }
        if (p[i]<limit && !adj[i].size()){
            return k+1;
        }
    }
    memset(match,-1,sizeof(match));
    int res=n;
    for (int i=0;i<n;++i){
        if (match[i]!=-1){
            continue;
        }
        ++stamp;
        if (aug(i)){
            --res;
        }
    }
    return res;
}

int main()
{
    scanf("%d%d",&n,&k);
    for (int i=0;i<n;++i){
        scanf("%d%d%d%d",&x[i],&y[i],&z[i],&p[i]);
    }
    memset(mark,-1,sizeof(mark));
    stamp=0;
    int l=1,r=1000000000;
    while (l+1<r){
        int mid=(l+r)/2;
        if (calc(mid)<=k) l=mid;
        else r=mid;
    }
    if (calc(l)>k){
        puts("-1");
        return 0;
    }
    printf("%d %d\n",calc(l),l);
    for (int i=0;i<n;++i){
        if (match[i]>i){
            int j=match[i];
            printf("%.1f %.1f %.1f\n",(x[i]+x[j])/2.0,(y[i]+y[j])/2.0,(z[i]+z[j])/2.0);
        }else if (match[i]==-1){
            if (p[i]>=l){
                printf("%d %d %d\n",x[i],y[i],z[i]);
            }else{
                for (int j=0;j<n;++j){
                    if (dist(i,j)==1 && p[i]+p[j]>=l){
                        printf("%.1f %.1f %.1f\n",(x[i]+x[j])/2.0,(y[i]+y[j])/2.0,(z[i]+z[j])/2.0);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

