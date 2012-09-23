#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
using namespace std;

typedef pair<int,int> PII;

const double eps	=	1e-9;

#define MP make_pair

int n,m,ed,st,dir;
double mat[205][205],prob[105],x[1000];

inline void move(int &x,int &y)
{
	if (n==1) return;
	
	if (x==0){
		++x;
		y=0;
	}else if (x==n-1){
		--x;
		y=1;
	}else{
		if (y==0) ++x;
		else --x;
	}
	if (x==0 || x==n-1){
		y=-1;
	}
}

inline bool addNew(map<PII,int> &hash,PII x)
{
	if (hash.count(x)) return false;
	hash[x]=hash.size()-1;
	return true;
}

inline bool solve()
{
	map<PII,int> hash;
	queue<PII> q;
	q.push(MP(st,dir));
	addNew(hash,MP(st,dir));
	while (q.size()){
		PII cur=q.front();
		q.pop();
		int x=cur.first,y=cur.second;
//printf("	%d %d\n",x,y);
		for (int i=1;i<=m;++i){
			move(x,y);
			if (prob[i]>eps){
				if (addNew(hash,MP(x,y))){
					q.push(MP(x,y));
				}
			}
		}
	}
	int N=hash.size();
	memset(mat,0,sizeof(mat));
	for (map<PII,int>::iterator it=hash.begin();it!=hash.end();++it){
		int ox=it->first.first;
		int oy=it->first.second;
		
		int x=ox,y=oy;
		for (int i=1;i<=m;++i){
			move(x,y);
			if (prob[i]>eps){
				mat[it->second][hash[MP(x,y)]]-=prob[i];
				mat[it->second][N]+=prob[i]*i;
			}
		}
		mat[it->second][it->second]+=1;
	}	

	if (ed==0 || ed==n-1){
		if (hash.count(MP(ed,-1))){
			int id=hash[MP(ed,-1)];
			memset(mat[id],0,sizeof(mat[id]));
			mat[id][id]=1;
		}else{
			return false;
		}
	}else{
		bool found=false;
		if (hash.count(MP(ed,0))){
			int id=hash[MP(ed,0)];
			memset(mat[id],0,sizeof(mat[id]));
			mat[id][id]=1;
			found=true;
		}
		
		if (hash.count(MP(ed,1))){
			int id=hash[MP(ed,1)];
			memset(mat[id],0,sizeof(mat[id]));
			mat[id][id]=1;
			found=true;
		}
		
		if (!found){
			return false;
		}
	}
	
	for (int i=0;i<N;++i){
		int pivot=i;
		for (int j=i+1;j<N;++j){
			if (fabs(mat[j][i])>fabs(mat[pivot][i])+eps){
				pivot=j;
			}
		}
		for (int j=0;j<=N;++j){
			swap(mat[i][j],mat[pivot][j]);
		}
		
		for (int j=i+1;j<N;++j){
			if (fabs(mat[j][i])>eps){
				double lambda=mat[j][i]/mat[i][i];
				for (int k=0;k<=N;++k){
					mat[j][k]-=mat[i][k]*lambda;
				}
			}
		}
	}
	
	for (int i=N-1;i>=0;--i){
		if (fabs(mat[i][i])>eps){
			x[i]=mat[i][N]/mat[i][i];
		}else{
			if (fabs(mat[i][N])<eps) x[i]=0;
			else return false;
		}
		for (int j=0;j<i;++j){
			mat[j][N]-=mat[j][i]*x[i];
		}
	}
	int id=hash[MP(st,dir)];
	printf("%.2f\n",x[id]);
	return true;
}

int main()
{
	int T;
	for (scanf("%d",&T);T--;){
		scanf("%d%d%d%d%d",&n,&m,&ed,&st,&dir);
		for (int i=1;i<=m;++i){
			int x;
			scanf("%d",&x);
			prob[i]=x/100.0;
		}
		if (!solve()){
			puts("Impossible !");
		}
	}
	return 0;
}
