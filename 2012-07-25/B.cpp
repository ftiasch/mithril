#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int dx[]  =   {-1,0,1,0};
const int dy[]  =   {0,1,0,-1};

const int maxn  =   25;

vector< vector<int> > plans[10][3][3][3][3];
vector< pair<int,int> > forbids[maxn*maxn][4];
vector< pair<pair<int,int>,int> > e;
vector<int> adj[maxn*maxn];
char s[maxn][maxn];
bool mark[maxn*maxn];
int father[maxn*maxn],number[maxn*maxn],n,forbidCnt[maxn*maxn][4];
int x[maxn*maxn],y[maxn*maxn],id[maxn][maxn],w,h;

inline bool range(int x,int y)
{
    return x>=0 && x<h && y>=0 && y<w;
}

inline int Find(int x)
{
    if (x==father[x]) return x;
    return father[x]=Find(father[x]);
}

inline bool dfs()
{
    int best=-1,mini=0;
    for (int i=0;i<n;++i)
    if (!mark[i]){
        int u=min(2,number[adj[i][0]]);
        int l=min(2,number[adj[i][1]]);
        int d=min(2,number[adj[i][2]]);
        int r=min(2,number[adj[i][3]]);
        int cost=plans[number[i]][u][l][d][r].size();
        if (best==-1 || cost<mini){
            mini=cost;
            best=i;
        }
    }
    if (best==-1){
        //check connection!
        for (int i=0;i<n;++i) father[i]=i;
        for (int i=0;i<e.size();++i){
            father[Find(e[i].first.first)]=Find(e[i].first.second);
        }
        for (int i=0;i<n;++i){
            if (Find(i)!=Find(0)) return false;
        }
        
        //print
        for (int i=0;i<e.size();++i){
            int u=e[i].first.first,v=e[i].first.second;
            int x1=x[u],y1=y[u];
            int x2=x[v],y2=y[v];
            int dx=x2-x1,dy=y2-y1;
            if (dx) dx/=abs(dx);
            if (dy) dy/=abs(dy);
            x1+=dx;y1+=dy;
            while (x1!=x2 || y1!=y2){
                if (e[i].second==2){
                    if (dx) s[x1][y1]='"';
                    else s[x1][y1]='=';
                }else{
                    if (dx) s[x1][y1]='|';
                    else s[x1][y1]='-';
                }
                x1+=dx;y1+=dy;
            }
        }
        
        for (int i=0;i<h;++i)
            puts(s[i]);
        
        return true;
    }
    if (mini==0) return false;
    
    int u=min(2,number[adj[best][0]]);
    int l=min(2,number[adj[best][1]]);
    int d=min(2,number[adj[best][2]]);
    int r=min(2,number[adj[best][3]]);
    mark[best]=true;
    vector<vector<int> > &plan=plans[number[best]][u][l][d][r];
    int bak=number[best];
    number[best]=0;
    
    for (int i=0;i<plan.size();++i){
        bool ok=true;
        for (int j=0;j<plan[i].size() && ok;++j)
        if (plan[i][j]>0 && forbidCnt[best][j]) ok=false;
        if (!ok) continue;
        for (int j=0;j<plan[i].size();++j){
            number[adj[best][j]]-=plan[i][j];
            if (plan[i][j]>0){
                e.push_back(make_pair(make_pair(best,adj[best][j]),plan[i][j]));
                //calc forbid!!
                for (int k=0;k<forbids[best][j].size();++k){
                    ++forbidCnt[forbids[best][j][k].first][forbids[best][j][k].second];
                }
            }
        }
        
        if (dfs()) return true;
        
        for (int j=0;j<plan[i].size();++j){
            number[adj[best][j]]+=plan[i][j];
            if (plan[i][j]>0){
                e.pop_back();
                //calc forbid!!
                for (int k=0;k<forbids[best][j].size();++k){
                    --forbidCnt[forbids[best][j][k].first][forbids[best][j][k].second];
                }
            }
        }
    }
    
    number[best]=bak;
    mark[best]=false;
    return false;
}

inline bool cross(int i,int j,int u,int v)
{
    if (x[i]==x[j]){
        if (y[u]==y[v]){
            return min(x[u],x[v])<x[i] && x[i]<max(x[u],x[v]) && min(y[i],y[j])<y[u] && y[u]<max(y[i],y[j]);
        }
        return false;
    }else{
        if (x[u]==x[v]){
            swap(i,u);
            swap(j,v);
            return min(x[u],x[v])<x[i] && x[i]<max(x[u],x[v]) && min(y[i],y[j])<y[u] && y[u]<max(y[i],y[j]);
        }
        return false;
    }
}

int main()
{
    for (int center=0;center<=8;++center){
        for (int u=0;u<=2;++u)
            for (int l=0;l<=2;++l)
                for (int d=0;d<=2;++d)
                    for (int r=0;r<=2;++r)
                    if (u+l+d+r==center){
                        vector<int> plan;
                        plan.push_back(u);
                        plan.push_back(l);
                        plan.push_back(d);
                        plan.push_back(r);
                        
                        for (int uu=u;uu<=2;++uu)
                        for (int ll=l;ll<=2;++ll)
                        for (int dd=d;dd<=2;++dd)
                        for (int rr=r;rr<=2;++rr)
                            plans[center][uu][ll][dd][rr].push_back(plan);
                    }
    }
    
    for (bool first=true;scanf("%d%d",&w,&h)==2 && (w|h);first=false){
        if (!first) puts("");
        n=0;
        for (int i=0;i<h;++i){
            scanf("%s",s[i]);
            for (int j=0;j<w;++j)
            if (s[i][j]>='1' && s[i][j]<='8'){
                x[n]=i;
                y[n]=j;
                number[n]=s[i][j]-'0';
                id[i][j]=n++;
            }
        }
        number[n]=0;
        for (int i=0;i<h;++i)
            for (int j=0;j<w;++j)
            if (s[i][j]>='1' && s[i][j]<='8'){
                adj[id[i][j]].clear();
                for (int k=0;k<4;++k){
                    int x=i+dx[k],y=j+dy[k];
                    while (range(x,y) && !(s[x][y]>='1' && s[x][y]<='8')){
                        x+=dx[k];
                        y+=dy[k];
                    }
                    if (range(x,y)){
                        adj[id[i][j]].push_back(id[x][y]);
                    }else{
                        adj[id[i][j]].push_back(n);
                    }
                }
            }
        
        for (int i=0;i<n;++i)
            for (int j=0;j<4;++j){
                forbids[i][j].clear();
                if (adj[i][j]<n)
                    for (int k=0;k<n;++k)
                    if (i!=k)
                        for (int l=0;l<4;++l)
                        if (adj[k][l]<n){
                            int u=adj[i][j],v=adj[k][l];
                            if (cross(i,u,k,v)){
                                forbids[i][j].push_back(make_pair(k,l));
                            }
                        }
            }
            
        e.clear();
        memset(forbidCnt,0,sizeof(forbidCnt));
        memset(mark,false,sizeof(mark));
        if (!dfs()){
            puts("No Answer!!!");
        }
    }
    return 0;
}

