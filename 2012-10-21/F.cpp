#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn  =   10005;

vector<int> adj[maxn];
int d[maxn],n,m;
double A[maxn],P[maxn];

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i){
        scanf("%lf%lf",&P[i],&A[i]);
    }
    for (int i=0;i<m;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        ++d[b];
    }
    vector<int> q;
    for (int i=1;i<=n;++i){
        if (!d[i]){
            q.push_back(i);
        }
    }
    for (int i=0;i<q.size();++i){
        int u=q[i];
        for (int j=0;j<adj[u].size();++j){
            int v=adj[u][j];
            if (!(--d[v])){
                q.push_back(v);
            }
        }
    }
    
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    A[x]+=y;
    
    for (int i=0;i<q.size();++i){
        int u=q[i];
        if (A[u]>P[u]){
            double delta=A[u]-P[u];
            A[u]=P[u];
            if (adj[u].size()){
                delta/=adj[u].size();
                for (int j=0;j<adj[u].size();++j){
                    int v=adj[u][j];
                    A[v]+=delta;
                }
            }
        }
    }
    printf("%.10f\n",A[z]);
    
    return 0;
}

