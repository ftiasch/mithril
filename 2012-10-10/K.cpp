#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;

#define left my_left
#define right my_right

const int maxn  =   3005;

int m,n;
int f[maxn][maxn],g[maxn][maxn];
deque< pair<int,int> > left[maxn],right[maxn];

int main()
{
    freopen("work.in","r",stdin);
    freopen("work.out","w",stdout);
    
    scanf("%d%d",&m,&n);
    for (int i=1;i<=n;++i){
        f[i][i-1]=0;
        g[i][i-1]=i;
    }
    
    for (int len=1;len<=n;++len){
        for (int i=1;i+len-1<=n;++i){
            int j=i+len-1;
            g[i][j]=j+1;
            for (int k=g[i][j-1];k<=g[i+1][j];++k){
            //for (int k=i;k<=j;++k){
                if (f[i][k-1]>f[k+1][j]){
                    g[i][j]=k;
                    break;
                }
            }
//printf("%d %d %d\n",i,j,g[i][j]);
            f[i][j]=1000000000;
            if (true){
                int k=i;
                while (right[j].size() && right[j].back().second>=k+f[k+1][j]){
                    right[j].pop_back();
                }
                right[j].push_back(make_pair(k,k+f[k+1][j]));
                
                while (right[j].size() && right[j].front().first>=g[i][j]){
                    right[j].pop_front();
                }
                if (right[j].size()){
                    f[i][j]=min(f[i][j],right[j].front().second);
                }
            }
            if (true){
                int k=j;
                while (left[i].size() && left[i].back().second>=k+f[i][k-1]){
                    left[i].pop_back();
                }
                left[i].push_back(make_pair(k,k+f[i][k-1]));
                while (left[i].size() && left[i].front().first<g[i][j]){
                    left[i].pop_front();
                }
                if (left[i].size()){
                    f[i][j]=min(f[i][j],left[i].front().second);
                }
            }
        }
    }

    printf("%d\n",f[m][n]);
    
    return 0;
}

