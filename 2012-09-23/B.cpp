#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;

const int inf	=	1000000000;

const int maxn		=	105;
const int maxk		=	30;
const int maxnode	=	(maxn+maxk+5)*2;
const int maxedge	=	maxnode*maxnode*2;

int head[maxnode],vtx[maxedge],next[maxedge],c[maxedge],cost[maxedge],tot;
int d[maxn][maxn];
int dist[maxnode],pre[maxnode],s,t,flow,Tcost;
bool vis[maxnode];

inline void add(int a,int b,int cst)
{
//printf("%d %d %d\n",a,b,cst);
	vtx[tot]=b;
	next[tot]=head[a];
	cost[tot]=cst;
	c[tot]=1;
	head[a]=tot++;
	
	vtx[tot]=a;
	next[tot]=head[b];
	c[tot]=0;
	cost[tot]=-cst;
	head[b]=tot++;
}


inline bool spfa()
{
	queue<int> q;
	for (int i=0;i<=t;++i) dist[i]=inf;
	dist[s]=0;
	q.push(s);
	memset(vis,false,sizeof(vis));
	while (q.size()){
		int u=q.front();
		vis[u]=false;
		q.pop();
		for (int p=head[u];p;p=next[p]){
			if (c[p] && dist[vtx[p]]>dist[u]+cost[p]){
				pre[vtx[p]]=p;
				dist[vtx[p]]=dist[u]+cost[p];
				if (!vis[vtx[p]]){
					vis[vtx[p]]=true;
					q.push(vtx[p]);
				}
			}
		}
	}
	if (dist[t]==inf) return false;
	for (int u=t,p;u!=s;u=vtx[p]){
		p=pre[u];
		--c[p];
		++c[p^=1];
	}
	++flow;
	Tcost+=dist[t];
	return true;
}

int main()
{
	for (int n,m,cycle_num;scanf("%d%d%d",&n,&m,&cycle_num)==3 && (n|m|cycle_num);){
		for (int i=0;i<=n;++i){
			for (int j=0;j<=n;++j){
				d[i][j]=inf;
			}
			d[i][i]=0;
		}
		for (int i=0;i<m;++i){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			d[a][b]=d[b][a]=min(d[a][b],c);
		}
		
		for (int k=0;k<=n;++k){
			for (int i=0;i<=n;++i){
				for (int j=0;j<=n;++j){
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
				}
			}
		}
		
		memset(head,0,sizeof(head));
		tot=2;
		int leftSize=n+cycle_num;
		for (int i=1;i<=n;++i){
			for (int j=i+1;j<=n;++j){
				add(j,i+leftSize,d[i][j]);
			}
			for (int j=1;j<=cycle_num;++j){
				add(n+j,i+leftSize,d[i][0]);
			}
		}
		for (int i=1;i<=cycle_num;++i){
			for (int j=1;j<=n;++j){
				add(j,n+i+leftSize,d[j][0]);
			}
		}
		s=0;t=leftSize*2+1;
		for (int i=1;i<=leftSize;++i){
			add(s,i,0);
			add(i+leftSize,t,0);
			if (i>n) add(i,i+leftSize,0);
		}
		flow=0;
		Tcost=0;
		while (spfa());
//printf("flow	=	%d\n",flow);
		printf("%d\n",Tcost);
	}
	return 0;
}


