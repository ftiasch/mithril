#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

long long sb1[100005];

inline int solve(int m,int nb1,int sb,vector<int> &b0)
{
	int s=0,ret=0;
	for (int i=0;i<=b0.size();++i){
		if (i>0) s+=b0[i-1];
		if (s>m) break;
		
		long long remain=m-s;
		int index=upper_bound(sb1,sb1+nb1+1,remain)-sb1-1;
		if (index>0){
			int more=sb-(nb1-index);
			ret=max(ret,nb1+min(more+i,(int)b0.size()));
		}else{
			ret=max(ret,i);
		}
	}
	return ret;
}

int main()
{
	int T,test=1;
	for (scanf("%d",&T);test<=T;++test){
		int n,m;
		scanf("%d%d",&n,&m);
		vector<int> b0,b1;
		int sb=0;
		for (int i=0;i<n;++i){
			int a,b;
			scanf("%d%d",&a,&b);
			if (b>0){
				sb+=b;
				b1.push_back(a);
			}else{
				b0.push_back(a);
			}
		}
		sort(b1.begin(),b1.end());
		sort(b0.begin(),b0.end());
		
		sb1[0]=0;
		for (int i=0;i<b1.size();++i){
			sb1[i+1]=sb1[i]+b1[i];
		}
		
		int ans=solve(m,b1.size(),sb,b0);
		int l=-1,r=m;
		while (l+1<r){
			int mid=(l+r)/2;
			if (solve(mid,b1.size(),sb,b0)==ans) r=mid;
			else l=mid;
		}
		
		printf("Case %d: %d %d\n",test,ans,r);
	}
	return 0;
}
