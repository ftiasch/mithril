#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

const int maxn	=	1005;

double ps[maxn],pw[maxn];
double cost[maxn][maxn],f[55][maxn];
int g[55][maxn];

int main()
{
	for (int n,m;scanf("%d%d",&n,&m)==2 && (n|m);){
		map<int,double> prob;
		for (int i=0;i<n;++i){	
			int p;
			scanf("%d",&p);
			while (p--){
				int x;double pro;
				scanf("%d%lf",&x,&pro);
				prob[x]+=pro;
			}
		}
		
		vector<int> pos;
		vector<double> weight;
		for (map<int,double>::iterator it=prob.begin();it!=prob.end();++it){
			pos.push_back(it->first);
			weight.push_back(it->second);
		}
		
		n=pos.size();// n changes its meaning!
		
		ps[0]=0;
		pw[0]=0;
		for (int i=0;i<n;++i){
			ps[i+1]=ps[i]+weight[i];
			pw[i+1]=pw[i]+pos[i]*weight[i];
		}
		
		for (int i=0;i<n;++i){
			int mid=i;
			for (int j=i;j<n;++j){
				while (mid+1<=j && (ps[mid+1]-ps[i])*2<=(ps[j+1]-ps[i])) ++mid;
				cost[i][j]=(ps[mid+1]-ps[i])*pos[mid]-(pw[mid+1]-pw[i]);
				cost[i][j]+=(pw[j+1]-pw[mid+1])-(ps[j+1]-ps[mid+1])*pos[mid];
//printf("%d %d %lf	%d\n",pos[i],pos[j],cost[i][j],pos[mid]);
			}
		}
		
		for (int i=0;i<=m;++i){
			for (int j=0;j<=n;++j){
				f[i][j]=1e100;
			}
		}
		f[0][0]=0;
		memset(g,0,sizeof(g));
		for (int i=1;i<=m;++i){
			for (int j=i;j<=n;++j){
				int st=max(g[i-1][j],g[i][j-1]);
//printf("%d %d %d\n",i,j,st);
				for (int k=st;k<j;++k){
					if (f[i-1][k]<1e90 && f[i-1][k]+cost[k][j-1]<f[i][j]){
						f[i][j]=f[i-1][k]+cost[k][j-1];
						g[i][j]=k;
					}
				}
			}
		}
		printf("%.2f\n",f[m][n]);
	}
	return 0;
}

