#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

const double eps	=	1e-8;
const int maxn		=	505;
const int limit		=	30;

double mat[maxn][maxn],tmp[maxn][maxn];
int n;

inline void gen(double mat[][maxn])
{
	for (int i=0;i<n;++i){
		double s=0;
		for (int j=0;j<n;++j){
			mat[i][j]=rand();
			s+=mat[i][j];
		}
		for (int j=0;j<n;++j){
			mat[i][j]/=s;
		}
	}
}

int main()
{
	int T;
	for (scanf("%d",&T);T--;){
		//n=500;gen(mat);
		scanf("%d",&n);
		for (int i=0;i<n;++i){
			for (int j=0;j<n;++j){
				scanf("%lf",&mat[i][j]);
			}
		}
		double last=-1;
		for (int _=0;_<limit;++_){
			memset(tmp,0,sizeof(tmp));
			for (int k=0;k<n;++k){
				for (int i=0;i<n;++i){
					for (int j=0;j<n;++j){
						tmp[i][j]+=mat[i][k]*mat[k][j];
					}
				}
			}
			double cur=0;
			for (int i=0;i<n;++i){
				cur+=tmp[i][0];
			}
			if (fabs(cur-last)<eps){
				last=cur;
				break;
			}
			last=cur;
			for (int i=0;i<n;++i){
				double s=0;
				for (int j=0;j<n;++j){
					mat[i][j]=tmp[i][j];
					s+=mat[i][j];
				}
				for (int j=0;j<n;++j){
					mat[i][j]/=s;
				}
			}
		}
		printf("%.10f\n",last/n);
	}
	//printf("%lf\n",(double)clock()/CLOCKS_PER_SEC);
	return 0;
}
