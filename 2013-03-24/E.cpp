#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int maxn  =   310;

vector<int> Link[maxn];
int n;
int match[maxn],backup[maxn];
int Queue[maxn], head, tail;
int pred[maxn],base[maxn];
bool inQueue[maxn], inBlossom[maxn];
bool use[maxn];
int start, finish;
int newbase;

void push(int u)
{
    Queue[tail++]=u;
    inQueue[u]=true;
}

int pop()
{
    return Queue[head++];
}

int findCommonAncestor(int u,int v)
{
    bool inPath[maxn];
    for (int i=0;i<n;++i) inPath[i]=false;
    while (true){
        u=base[u];
        inPath[u]=true;
        if (u==start){
            break;
        }
        u=pred[match[u]];
    }
    while (true){
        v=base[v];
        if (inPath[v]){
            break;
        }
        v=pred[match[v]];
    }
    return v;
}

void resetTrace(int u)
{
    int v;
    while (base[u]!=newbase){
        v=match[u];
        inBlossom[base[u]]=inBlossom[base[v]]=true;
        u=pred[v];
        if (base[u]!=newbase) pred[u]=v;
    }
}

void BlossomContract(int u,int v)
{
    newbase=findCommonAncestor(u,v);
    for (int i=0;i<n;++i){
        inBlossom[i]=false;
    }
    resetTrace(u);resetTrace(v);
    if (base[u]!=newbase) pred[u]=v;
    if (base[v]!=newbase) pred[v]=u;
    for (int i=0;i<n;++i){
        if (inBlossom[base[i]]){
            base[i]=newbase;
            if (!inQueue[i]) push(i);
        }
    }
}

bool findAugmentingPath(int u)
{
    bool found=false;
    for (int i=0;i<n;++i){
        pred[i]=-1;
        base[i]=i;
        inQueue[i]=false;
    }
    start=u;finish=-1;
    head=tail=0;
    push(start);
    while (head<tail){
        int u=pop();
        for (int i=(int)Link[u].size()-1;i>=0;--i){
            int v=Link[u][i];
            if (use[u] && use[v] && base[u]!=base[v] && match[u]!=v){
                if (v==start || (match[v]>=0 && pred[match[v]]>=0)){
                    BlossomContract(u,v);
                }else if (pred[v]==-1){
                    pred[v]=u;
                    if (match[v]>=0) push(match[v]);
                    else{
                        finish=v;
                        return true;
                    }
                }
            }
        }
    }
    return found;
}

void augmentPath()
{
    int u,v,w;
    u=finish;
    while (u>=0){
        v=pred[u];
        w=match[v];
        match[v]=u;
        match[u]=v;
        u=w;
    }
}

void findMaxMatching()
{
    for (int i=0;i<n;++i) match[i]=-1;
    for (int i=0;i<n;++i){
        if (match[i]==-1 && use[i]){
            if (findAugmentingPath(i)){
                augmentPath();
            }
        }
    }
}

int a[maxn*maxn],b[maxn*maxn],m;

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;++i){
        scanf("%d%d",&a[i],&b[i]);
        --a[i];--b[i];
//printf("edge: %d %d\n",a[i],b[i]);
        Link[a[i]].push_back(b[i]);
        Link[b[i]].push_back(a[i]);
    }
    
    memset(use,true,sizeof(use));
    findMaxMatching();
    
    for (int i=0;i<n;++i){
//printf("%d - %d\n",i,match[i]);
        if (match[i]==-1){
            for (int j=0;j<m;++j){
                puts("NO");
            }
            return 0;
        }
        backup[i]=match[i];
    }
    
    for (int i=0;i<m;++i){
        int u=a[i],v=b[i];
        if (match[u]==v){
            puts("YES");
        }else{
            int x=match[u],y=match[v];
            match[x]=match[y]=-1;
            use[u]=use[v]=0;
            
            if (findAugmentingPath(x)){
                puts("YES");
            }else{
                puts("NO");
            }
            
            use[u]=use[v]=1;
            match[x]=u;match[y]=v;
        }
    }
    return 0;
}

