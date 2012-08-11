#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn  =   405;

int n,m,up[maxn][maxn];
char s[maxn][maxn];

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i) scanf("%s",s[i]);
    for (int i=0;i<n;++i){
        for (int j=0;j<m;++j){
            if (s[i][j]=='X') up[i][j]=0;
            else{
                if (i==0) up[i][j]=1;
                else up[i][j]=up[i-1][j]+1;
            }
        }
    }
    int ans=1;
    for (int i=0;i<n;++i){
        for (int l=0;l<m;++l){
            int minh=up[i][l];
            for (int r=l;r<m;++r){
                minh=min(minh,up[i][r]);
                if (minh==0) break;
                ans=max(ans,(minh+(r-l+1))*2);
            }
        }
    }
    printf("%d\n",ans-1);
    return 0;
}

