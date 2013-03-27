#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double PI =   acos(-1.0);
const int maxn  =   1505;

int n,x[maxn],y[maxn];

inline int getPart(int x,int y)
{
    if (y>0) return 0;
    if (y<0) return 1;
    if (x>=0) return 0;
    return 1;
}

inline long long det(const pair<int,int> &a,const pair<int,int> &b)
{
    return (long long)a.first*b.second-(long long)a.second*b.first;
}

inline bool cmp(const pair<int,int> &a,const pair<int,int> &b)
{
    if (getPart(a.first,a.second)!=getPart(b.first,b.second)){
        return getPart(a.first,a.second)<getPart(b.first,b.second);
    }
    return det(a,b)>0;
}

int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%d%d",&x[i],&y[i]);
    }
    double ans=0;
    for (int o=0;o<n;++o){
        vector< pair<int,int> > angles;
        for (int i=0;i<n;++i){
            if (i!=o){
                angles.push_back(make_pair(y[i]-y[o],x[i]-x[o]));
            }
        }
        sort(angles.begin(),angles.end(),cmp);
        for (int i=0;i<n-1;++i){
            angles.push_back(angles[i]);
        }
        double pairs=0;
        for (int i=0,j=0;i<n-1;++i){
            if (j<=i) j=i+1;
            while (j-i<n-1 && det(angles[i],angles[j])>0){
                ++j;
            }
            int cnt=j-i-1;
            pairs+=cnt*(cnt-1)/2;
        }
        double tri=(n-1)*(n-2)/2.0*(n-3)/3;
//printf("pairs = %d, contain = %d\n",pairs,tri-pairs);
        ans+=pairs-(tri-pairs);
    }
    double ret=ans/((double)n*(n-1)/2*(n-2)/3)/2.0;
    printf("%.10f\n",ret);
    return 0;
}

