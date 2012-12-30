#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn	=	100005;
const int maxk	=	15;

int f[maxn][2],size[maxn];
vector<int> son[maxn];
int opt_bak[maxn][2][maxk][2];
int n,k,father[maxn];

inline int getF(int u);

inline void update(int &a,int b)
{
	a=max(a,b);
}

#define opt(i,j,k) opt_bak[u][i][j][k]

inline int getF(int u,bool fl)
{
	int &res=f[u][fl];
	if (res!=-1) return res;
	res=0;
	for (int i=0;i<2;++i){
		for (int j=0;j<k;++j){
			for (int x=0;x<2;++x){
				opt(i,j,x)=0;
			}
		}
	}
	int now=0,old=1;
	for (int i=0;i<son[u].size();++i){
		int v=son[u][i];
		now=1-now;
		old=1-old;
		for (int j=0;j<k;++j){
			for (int x=0;x<2;++x){
				opt(now,j,x)=0;
			}
		}
		for (int j=0;j<k;++j){
			if (fl){
				update(opt(now,j,1),opt(old,j,0)+getF(v,true)+1);
			}
			for (int x=0;x<2;++x){
				update(opt(now,j,x),opt(old,j,x)+getF(v,false));
				if (j+1<k){
					update(opt(now,j+1,x),opt(old,j,x)+size[v]);
				}
			}
		}
	}
	for (int j=0;j<k;++j){
		for (int x=0;x<2;++x){
			update(res,opt(now,j,x));
		}
	}
	return res;
}

int main()
{
	int T;
	for (scanf("%d",&T);T--;){
		scanf("%d%d",&n,&k);
		--k;
		for (int i=1;i<=n;++i){
			son[i].clear();
		}
		for (int i=1;i<n;++i){
			scanf("%d",&father[i]);
			son[father[i]].push_back(i);
		}
		
		memset(f,-1,sizeof(f));
		memset(size,0,sizeof(size));
		for (int i=1;i<=n;++i){
			++size[i];
			if (i<n){
				size[father[i]]+=size[i];
			}
		}
		//printf("%d %d\n",getF(7),getF(8));
		//printf("%d %d\n",size[7],size[8]);
		
		printf("%d\n",getF(n,true));
	}
	return 0;
}
