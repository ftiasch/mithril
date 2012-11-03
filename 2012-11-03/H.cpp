#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int inf   =   1000000000;
const int limit =   10000;
const int maxn  =   1005*2;
const int maxm  =   (10005+maxn)*2;

int head[maxn],next[maxm],c[maxm],vtx[maxm],tot;
int pre[maxn];
vector<int> path[maxn];

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

inline void bfs(int s)
{
    queue<int> q;
    q.push(s);
    memset(pre,-1,sizeof(pre));
    pre[s]=-2;
    while (q.size()){
        int u=q.front();
        q.pop();
        for (int p=head[u];p;p=next[p]){
            if (c[p] && pre[vtx[p]]==-1){
                pre[vtx[p]]=p;
                q.push(vtx[p]);
            }
        }
    }
}

inline void getPath(int u,vector<int> &ret)
{
    ret.clear();
    while (u){
        int p=pre[u];
        ret.push_back(p);
        u=vtx[p^1];
    }
}

inline void push(vector<int> &path,int sign)
{
    for (int i=0;i<path.size();++i){
        int p=path[i];
        c[p]-=sign;
        c[p^1]+=sign;
    }
}

int main()
{
    freopen("hospital.in","r",stdin);
    freopen("hospital.out","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    tot=2;
    memset(head,0,sizeof(head));
    int s=0;
    for (int i=1;i<=n;++i){
        if (i<=k){
            int m;
            scanf("%d",&m);
            for (int j=0;j<m;++j){
                int x;
                scanf("%d",&x);
                add(x+n,i,inf);
            }
        }
        add(i,i+n,1);
        if (i>k){
            add(s,i,inf);
        }
    }
    
    bfs(s);
    vector<int> cant;
    for (int i=1;i<=k;++i){
        if (pre[i+n]!=-1){
            getPath(i+n,path[i]);
        }else{
            cant.push_back(i);
        }
    }
    
    printf("%d\n",(int)cant.size());
    for (int i=0;i<cant.size();++i){
        if (i){
            printf(" ");
        }
        printf("%d",cant[i]);
    }
    puts("");
    
    vector< pair<int,int> > answer;
    int ans=0;
    for (int i=1;i<=k;++i){
        if (path[i].size()){
            push(path[i],1);
            bfs(s);
            for (int j=i+1;j<=n;++j){
                if (j<=k && path[j].size()==0 || pre[j+n]!=-1){
                    continue;
                }
                if (answer.size()<limit){
                    answer.push_back(make_pair(i,j));
                }
                ++ans;
            }
            push(path[i],-1);
        }
    }
    printf("%d\n",ans);
    if (ans<=limit){
        for (int i=0;i<answer.size();++i){
            printf("%d %d\n",answer[i].first,answer[i].second);
        }
    }
    return 0;
}

