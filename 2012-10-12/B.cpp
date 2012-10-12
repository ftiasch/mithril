#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#define PB push_back
#define MP make_pair

typedef long long LL;

const int maxn  =   50+5;
const int maxm  =   50*10000+5;

double f[2][maxm];
bool pre[maxn][maxm];
int type[maxn];
int n,x;
int a[maxn],b[maxn];
double discount[maxn];

int main()
{
    scanf("%d%d",&n,&x);
    for (int i=0;i<n;++i){
        scanf("%d%d",&a[i],&b[i]);
        discount[i]=(100-b[i])/100.0;
    }
    int s=0;
    int now=0,old=1;
    f[0][0]=x;
    for (int i=0;i<n;++i){
        now=1-now;
        old=1-old;
        for (int j=0;j<=s+a[i];++j){
            f[now][j]=x;
        }
        for (int j=0;j<=s;++j){
            if (f[now][j+a[i]]>f[old][j]){
                f[now][j+a[i]]=f[old][j];
                pre[i+1][j+a[i]]=0;
            }
            if (f[now][j]>f[old][j]*discount[i]){
                f[now][j]=f[old][j]*discount[i];
                pre[i+1][j]=1;
            }
        }
        s+=a[i];
    }
    
    double ans=x+1;
    int best=-1;
    for (int i=0;i<=s;++i){
        double tmp=f[now][i]-i;
        if (ans>tmp){
            ans=tmp;
            best=i;
        }
    }
    
    for (int i=n-1;i>=0;--i){
        int op=pre[i+1][best];
        if (op==0){
            type[i]=0;
            best-=a[i];
        }else{
            type[i]=1;
        }
    }
    
    for (int i=0;i<n;++i){
        if (type[i]==1){
            printf("%d reverse\n",i+1);
        }
    }
    for (int i=0;i<n;++i){
        if (type[i]==0){
            printf("%d front\n",i+1);
        }
    }
    return 0;
}
