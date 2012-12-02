#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#define PB push_back

#define FOR(i,a) for (__typeof((a).begin()) i=(a).begin();i!=(a).end();++i)

typedef unsigned long long ULL;

const ULL magic	=	0xabcdef;

const int N = 2000000 + 2;

int n, m;
char text[N], pattern[N];
vector<int> pos[300],has[300];
vector<ULL> hash[300];
ULL pw[N+10],target[300];

int main() {
	gets(text);
	gets(pattern);
	n = strlen(text);
	m = strlen(pattern);
	
	for (int i=0;i<n;++i){
		pos[text[i]].PB(i);
	}
	for (int i=33;i<=126;++i){
		if (pos[i].size()==0){
			continue;
		}
		hash[i].PB(0);
		for (int j=1;j<pos[i].size();++j){
			ULL cur=hash[i].back()*magic+(pos[i][j]-pos[i][j-1]);
			hash[i].PB(cur);
		}
	}
	
	map<int,int> first;
	for (int i=0;i<m;++i){
		if (has[pattern[i]].size()==0){
			first[pattern[i]]=i;
		}else{
			target[pattern[i]]=target[pattern[i]]*magic+(i-has[pattern[i]].back());
		}
		has[pattern[i]].PB(i);
	}
	pw[0]=1;
	for (int i=1;i<=m;++i){
		pw[i]=pw[i-1]*magic;
	}
	
	vector<int> ans;
	for (int i=0;i+m<=n;++i){
		bool ok=true;
		FOR (it,first){
			int p=i+(it->second),ch=text[p];
			int st=lower_bound(pos[ch].begin(),pos[ch].end(),p)-pos[ch].begin();
			int ed=upper_bound(pos[ch].begin(),pos[ch].end(),i+m-1)-pos[ch].begin();
			int len=has[it->first].size();
			if (ed-st!=len){
				ok=false;
			}else{
				if (len>1){
					--len;
					ok&=target[it->first]==hash[ch][st+len]-hash[ch][st]*pw[len];
				}
			}
			if (!ok) break;
		}
		if (ok) ans.PB(i);
	}
	
	printf("%d\n",ans.size());
	if (ans.size()){
		for (int i=0;i<ans.size();++i){
			if (i) printf(" ");
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	
	return 0;
}

