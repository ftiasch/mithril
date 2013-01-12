#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn  =   1005;

int f[maxn][maxn],pre[maxn][maxn];
int id[maxn],P[maxn],n,out[maxn];

inline int calc(int i,int j)
{
    return P[j]*(1000/P[i]);
}

inline bool byP(const int &i,const int &j)
{
    return P[i]<P[j];
}

inline bool update(int &a,int b)
{
    if (a==-1 || a>b){
        a=b;
        return true;
    }
    return false;
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%d",&P[i]);
        id[i]=i;
    }
    sort(id,id+n,byP);
    
    memset(f,-1,sizeof(f));
    f[0][0]=0;
    int ans=-1,ansi,ansj;
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j){
            if (f[i][j]!=-1){
                int A=id[i],B=id[j];
                int k=max(i,j)+1;
                if (k==n){
                    if (update(ans,f[i][j]+calc(B,A))){
                        ansi=i;
                        ansj=j;
                    }
                    continue;
                }
                int C=id[k];
                if (update(f[i][k],f[i][j]+calc(B,C))){
                    pre[i][k]=j;
                }
                if (update(f[k][j],f[i][j]+calc(C,A))){
                    pre[k][j]=i;
                }
            }
        }
    }
//    printf("ans= %d\n",ans);
    int l=0,r=n;
    while (ansi!=ansj){
        int k=max(ansi,ansj);
//printf("%d %d\n",ansi,ansj);
        if (k==ansj){
            out[--r]=id[k];
            ansj=pre[ansi][k];
        }else{
            out[l++]=id[k];
            ansi=pre[k][ansj];
        }
    }
    out[l++]=id[ansi];
    for (int i=0;i<n;++i){
        if (out[i]==0){
            for (int j=0;j<n;++j){
                if (j) printf(" ");
                printf("%d",out[(i+j)%n]+1);
            }
            puts("");
            return 0;
        }
    }
    return 0;
}

