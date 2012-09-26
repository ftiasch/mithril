#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

#define PB push_back

const int maxn	=	65;
const int maxd	=	5;

vector<int> adj[maxn];

struct Mask
{
	//0..300-1
	static const int maxn	=	299/32+1;
	unsigned a[maxn];
	int bitCount;
	
	Mask(){memset(a,0,sizeof(a));bitCount=0;}
	
	inline void clear()
	{
		memset(a,0,sizeof(a));
		bitCount=0;
	}
	
	int getBit(int index)
	{
		int i=index>>5;
		int j=index&31;
		return (int)(a[i]>>j&1U);
	}
	
	void setBit(int index)
	{
		if (getBit(index)==1) return;
		++bitCount;
		int i=index>>5;
		int j=index&31;
		a[i]|=1U<<j;
	}
	
	bool equals(const Mask &b)
	{
		for (int i=0;i<maxn;++i){
			if (a[i]!=b.a[i]) return false;
		}
		return true;
	}
	
	bool hasCommon(const Mask &b)
	{
		for (int i=0;i<maxn;++i){
			if (a[i]&b.a[i]) return true;
		}
		return false;
	}
	
	Mask orMask(const Mask &b)
	{
		Mask ret;
		for (int i=0;i<maxn;++i){
			ret.a[i]=a[i]|b.a[i];
		}
		return ret;
	}
}cover[maxn*maxd*maxd];

bool choose[maxn*maxd*maxd];
struct node
{
	int u,l,r;
	node(int a,int b,int c)
	{
		u=a;
		l=b;
		r=c;
	}
};
vector<node> leftSide;
vector<int> candidates[maxn*maxd],conflict[maxn*maxd*maxd];
int n,m,d;

inline void output()
{
	int ansl[maxn],ansr[maxn];
	memset(ansl,0,sizeof(ansl));
	memset(ansr,0,sizeof(ansr));
	for (int i=0;i<(int)leftSide.size();++i){
		if (choose[i]){
assert(ansl[leftSide[i].u]==0);
			ansl[leftSide[i].u]=leftSide[i].l+1;
			ansr[leftSide[i].u]=leftSide[i].r+1;
		}
	}
	for (int i=0;i<n;++i){
		printf("%d %d\n",ansl[i],ansr[i]);
	}
}

int forbid[maxn*maxd*maxd];

inline void select(int index,int sign)
{
	choose[index]^=1;
	for (int i=0;i<(int)conflict[index].size();++i){
		forbid[conflict[index][i]]+=sign;
	}
}

inline bool cmpBitCount(const int &i,const int &j)
{
	return cover[i].bitCount>cover[j].bitCount || cover[i].bitCount==cover[j].bitCount && conflict[i].size()<conflict[j].size();
}

int search_order[maxn*maxd];

inline bool cmpCandidatesCount(const int &i,const int &j)
{
	return candidates[i].size()>candidates[j].size();
}

inline bool dfs(int step,Mask current)
{
	int u;
	while (step>=0){
		u=search_order[step];
		if (current.getBit(u)){
			--step;
		}else{
			break;
		}
	}
	if (step<0){
		output();
		return true;
	}

	for (int i=0;i<(int)candidates[u].size();++i){
		int index=candidates[u][i];
		if (forbid[index]>0){
			continue;
		}
//printf("%d\n",index);
		select(index,1);
		if (dfs(step-1,current.orMask(cover[index]))) return true;
//printf("-%d\n",index);
		select(index,-1);
	}
	return false;
}

int main()
{
	for (;scanf("%d%d%d",&n,&m,&d)==3;){
		for (int i=0;i<n;++i){
			adj[i].clear();
			adj[i].push_back(i);
		}
		for (int i=0;i<m;++i){
			int a,b;
			scanf("%d%d",&a,&b);
			--a;--b;
			adj[a].PB(b);
			adj[b].PB(a);
		}
		
		for (int i=0;i<n;++i){
			sort(adj[i].begin(),adj[i].end());
			adj[i].erase( unique(adj[i].begin(),adj[i].end()), adj[i].end() );
		}

		leftSide.clear();
		for (int i=0;i<n;++i){
			int s,e;
			scanf("%d%d",&s,&e);
			--s;--e;
			for (int st=s;st<=e;++st){
				for (int ed=st;ed<=e;++ed){
					leftSide.PB(node(i,st,ed));
				}
			}
		}
//printf("%u\n",leftSide.size());fflush(stdout);
		
		for (int i=0;i<n*d;++i){
			candidates[i].clear();
		}
		for (int i=0;i<(int)leftSide.size();++i){
			conflict[i].clear();
		}
//printf("%u\n",leftSide.size());fflush(stdout);
		for (int i=0;i<(int)leftSide.size();++i){
			int u=leftSide[i].u,l=leftSide[i].l,r=leftSide[i].r;
			cover[i].clear();
			for (int j=0;j<adj[u].size();++j){
				int v=adj[u][j];
				for (int k=l;k<=r;++k){
					int right=v*d+k;
//printf("%d %d %d	%d\n",u,v,k,right);
					cover[i].setBit(right);
					candidates[right].PB(i);
				}
			}
			for (int j=0;j<i;++j){
				if (cover[i].hasCommon(cover[j]) || leftSide[i].u==leftSide[j].u){
					conflict[i].PB(j);
					conflict[j].PB(i);
				}
			}
		}

//printf("%u\n",leftSide.size());fflush(stdout);
		bool vis[leftSide.size()];
		memset(vis,false,sizeof(vis));
		for (int i=0;i<(int)leftSide.size();++i)if (!vis[i]){
			for (int j=i+1;j<(int)leftSide.size();++j)if (!vis[j]){
//printf("%d %d\n",i,j);fflush(stdout);
				if (cover[i].equals(cover[j])){
					vis[j]=true;
				}
			}
		}

		for (int i=0;i<n*d;++i){
			search_order[i]=i;
			sort(candidates[i].begin(),candidates[i].end(),cmpBitCount);
			int ptr=0;
			for (int j=0;j<candidates[i].size();++j){
				if (!vis[candidates[i][j]]){
					candidates[i][ptr++]=candidates[i][j];
				}
			}
			candidates[i].resize(ptr);
		}

		sort(search_order,search_order+n*d,cmpCandidatesCount);
		
		Mask current;
		memset(choose,0,sizeof(choose));
		memset(forbid,0,sizeof(forbid));
		if (!dfs(n*d-1,current)){
			puts("No solution");
		}
		puts("");
	}
	return 0;
}

