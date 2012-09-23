#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
using namespace std;

inline void RE()
{
	vector<int> a;
	printf("%d\n",a[1]);
}

int n,stdAns[1<<5],pw3[10];
vector<pair<string,unsigned> > candidates;

int best_length;
vector<pair<int,unsigned> > sel[1<<5];

inline string toString(unsigned x)
{
	string ret="";
	for (int i=0;i<1<<n;++i){
		if (x>>i&1){
			ret+="1";
		}else{
			ret+="0";
		}
	}
	return ret;
}

inline void dfs(int step,unsigned cover,int length)
{
	if (best_length!=-1 && length>=best_length) return;
	if (step<0){
		best_length=length;
		return;
	}
	if (cover>>step&1U){
		dfs(step-1,cover,length);
		return;
	}
	
	for (int i=0;i<sel[step].size();++i){
		dfs(step-1,cover|sel[step][i].second,length+sel[step][i].first+1);
	}
}

inline int solve(int st,unsigned cover)
{
	for (int i=0;i<1<<n;++i){
		sel[i].clear();
	}
	for (int i=st;i<candidates.size();++i){
		int length=candidates[i].first.size();
		unsigned mask=candidates[i].second;
		for (int j=0;j<1<<n;++j){
			if (mask>>j&1U){
				sel[j].push_back(make_pair(length,mask));
			}
		}
	}
	for (int i=0;i<1<<n;++i){
		sort(sel[i].begin(),sel[i].end());
	}
	
	best_length=-1;
	dfs((1<<n)-1,cover,0);
	return best_length;
}

int main()
{
	pw3[0]=1;
	for (int i=1;i<=5;++i){
		pw3[i]=pw3[i-1]*3;
	}
	for (;scanf("%d",&n)==1 && n;){
		memset(stdAns,-1,sizeof(stdAns));
		map<unsigned,string> terms;
		unsigned all0=0;
		for (int i=0;i<1<<n;++i){
			int mask=0,x;
			for (int j=0;j<n;++j){
				scanf("%d",&x);
				mask|=x<<j;
			}
			if (stdAns[mask]!=-1){
				puts("duplicate mask!");
				RE();
			}
			scanf("%d",&stdAns[mask]);
			if (stdAns[mask]==0){
				all0|=1U<<mask;
			}
		}
		
		//generation begin
		for (int stat=1;stat<pw3[n];++stat){
			int x=stat,coef[n];
			vector<string> tokens;
			for (int i=0;i<n;++i){
				int y=x%3;
				coef[i]=y;
				string cur;
				if (y==0){
					//not occurs
				}else if (y==1){
					//positive
					cur="A";
					cur[0]+=i;
					tokens.push_back(cur);
				}else{
					//negative
					cur="-A";
					cur[1]+=i;
					tokens.push_back(cur);
				}
				x/=3;
			}
			sort(tokens.begin(),tokens.end());
			string term="";
			for (int i=0;i<tokens.size();++i){
				term+=tokens[i];
			}
			unsigned cover=0;
			bool valid=true;
			for (int mask=0;mask<(1<<n) && valid;++mask){
				int res=1;
				for (int i=0;i<n;++i){
					if (coef[i]==1){
						res&=mask>>i&1;
					}else if (coef[i]==2){
						res&=~mask>>i&1;
					}
				}
				if (res==stdAns[mask]){
					cover|=1U<<mask;
				}else if (res>stdAns[mask]){
					valid=false;
				}
			}
			
			if (valid && cover){
				if (terms[cover]=="" || terms[cover].size()>term.size() || terms[cover].size()==term.size() && term<terms[cover]){
					terms[cover]=term;
				}
			}
		}
		
		candidates.clear();
		for (map<unsigned,string>::iterator it=terms.begin();it!=terms.end();++it){
//cout << toString(it->first) << " " << it->second << endl;
			candidates.push_back(make_pair(it->second,it->first));
		}
		candidates.push_back(make_pair("-AA",all0));
		sort(candidates.begin(),candidates.end());
		
		
		int min_length=solve(0,0);
//printf("%d\n",min_length);
		unsigned cur_mask=0;
		string ans="";
		for (int i=0;i<candidates.size();++i){
			if ((candidates[i].second&cur_mask)!=candidates[i].second){
				if (solve(i+1,cur_mask|candidates[i].second)+ans.size()+1+candidates[i].first.size()==min_length){
					ans+="+";
					ans+=candidates[i].first;
					cur_mask|=candidates[i].second;
				}
			}
		}
		printf("%s\n",ans.c_str()+1);
	}
	return 0;
}

