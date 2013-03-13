#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

const int maxn  =   400;

int n;
double x[maxn*maxn],y[maxn*maxn];
bool vis[maxn*maxn];

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n*n;++i){
        scanf("%lf%lf",&x[i],&y[i]);
        vis[i]=false;
    }
    bool fir=true;
    int order=0;
    for (int b=0;b<n;++b){
        double l=b*1.0/n,r=l+1.0/n;
        vector< pair<double,int> > a;
        for (int i=0;i<n*n;++i){
            if (!vis[i] && l-1e-9<=x[i] && x[i]<=r+1e-9){
                vis[i]=true;
                a.push_back(make_pair(y[i],i+1));
            }
        }
        sort(a.begin(),a.end());
        if (a.size()){
            if (order) reverse(a.begin(),a.end());
            order^=1;
        }
        for (int i=0;i<a.size();++i){
            if (fir){
                fir=false;
            }else{
                printf(" ");
            }
            printf("%d",a[i].second);
        }
    }
    for (int i=0;i<n*n;++i){
        assert(vis[i]);
    }
    puts("");
    return 0;
}
