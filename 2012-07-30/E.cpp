#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn      =   100005;
const double eps    =   1e-10;

int base,n,a[maxn];

inline int getLen(long long t)
{
    //double r=(double)t/base;
    if (9*(long long)base<=t*11 && t*9<=11*(long long)base) return 1;
    if (18*(long long)base<=t*11 && t*9<=22*(long long)base) return 2;
    return -1;
}

inline bool solve()
{
    vector<int> out;
    vector<double> b;
    int x=1;
    for (int i=0;i<n;++i){
        int len=getLen(a[i]);
        if (len==-1) return false;
        for (int j=0;j<len;++j)
            out.push_back(x);
        b.push_back((double)a[i]/len);
        x^=1;
    }
    double mi=*min_element(b.begin(),b.end());
    double ma=*max_element(b.begin(),b.end());
    if (ma/mi>1.1/0.9+eps) return false;
    if (out.size()%2) return false;
    vector<int> ans;
    for (int i=0;i<out.size();i+=2){
        if (out[i]==1 && out[i+1]==0) ans.push_back(1);
        else if (out[i]==0 && out[i+1]==1) ans.push_back(0);
        else return false;
    }
    if (ans[0]!=1 || ans[ans.size()-1]!=0) return false;
    
    for (int i=0;i<ans.size();++i) printf("%d",ans[i]);
    puts("");
    return true;
}

int main()
{
    int T;
    for (scanf("%d",&T);T--;){
        scanf("%d",&n);
        for (int i=0;i<n;++i) scanf("%d",&a[i]);
        base=a[0];
        if (!solve()) puts("ERROR");
    }
    return 0;
}

