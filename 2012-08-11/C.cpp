#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn  =   25;

double f[maxn][1<<20],p[maxn][maxn];
int n;

inline void update(double &a,double b)
{
    if (a<b) a=b;
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j){
            scanf("%lf",&p[i][j]);
            p[i][j]/=100;
        }
    }
    for (int i=0;i<n;++i)
        for (int j=0;j<1<<n;++j)
            f[i][j]=0;
    f[0][0]=1;
    for (int i=0;i<n;++i){
        for (int j=0;j<1<<n;++j){
            if (f[i][j]>1e-12){
                for (int k=0;k<n;++k)
                if (!(j>>k&1)){
                    update(f[i+1][j|(1<<k)],f[i][j]*p[i][k]);
                }
            }
        }
    }
    printf("%.10f\n",f[n][(1<<n)-1]*100);
    return 0;
}
