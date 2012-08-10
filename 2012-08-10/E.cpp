#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long LL;

const int maxn  =   1555;

int x[maxn],y[maxn],n;

inline LL cross(int i,int j,int k)
{
    LL x1=x[j]-x[i],y1=y[j]-y[i];
    LL x2=x[k]-x[i],y2=y[k]-y[i];
    return x1*y2-x2*y1;
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i) scanf("%d%d",&x[i],&y[i]);
    LL ans=0;
    LL C3=(LL)(n-1)*(n-2)*(n-3)/6;
    for (int o=0;o<n;++o){
        vector<pair<double,int> > a;
        for (int i=0;i<n;++i)
        if (o!=i){
            a.push_back(make_pair(atan2((double)y[i]-y[o],(double)x[i]-x[o]),i));
        }
        sort(a.begin(),a.end());
        LL sum=0;
        for (int i=0,cnt=0,j=0;i<a.size();++i){
            if (cnt==0){
                j=i+1;
                if (j==a.size()) j=0;
            }
            while (j!=i && cross(o,a[i].second,a[j].second)>=0){
                ++cnt;
                ++j;
                if (j==a.size()) j=0;
            }
            sum+=(LL)cnt*(cnt-1)/2;
            
            if (cnt > 0) --cnt;
        }
        ans+=C3-sum;
//printf("    %lld\n",C3-sum);
    }
    ans=(LL)n*(n-1)*(n-2)*(n-3)/24-ans;
    cout << ans << endl;
    return 0;
}

