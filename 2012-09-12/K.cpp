#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cassert>
#include <ctime>
using namespace std;

const int maxn	=	2005;

int a[maxn],n;

inline bool solve()
{
	int ptr=0;
	vector< pair<char,int> > ans;
	for (int i=1;i<n;++i){
//for (int j=0;j<n;++j){printf("%d ",a[j]);}puts("");
		int st;
		for (int j=0;j<n;++j)
		if (a[j]==i){
			st=j;
		}
		int ca=0;
		while ((ptr+2)%n!=st){
			--ptr;
			if (ptr<0) ptr+=n;
			++ca;
		}
		if (ca) ans.push_back(make_pair('a',ca));
		int best=-1,size;
		for (int _=0;_<n;++_){
			int cur=-1;
			if (a[(ptr+1+n)%n]==i-1) cur=0;
			else if (a[ptr]==i-1) cur=1;
			if (cur!=-1){
				if (best==-1 || cur<best){
					best=cur;
					size=ans.size();
				}
			}
			
			ans.push_back(make_pair('b',1));
assert(a[(ptr+2)%n]==i);
			a[(ptr+2)%n]=a[(ptr+1)%n];
			a[(ptr+1)%n]=a[(ptr+0)];
			a[(ptr+0)]=i;
			
			ans.push_back(make_pair('a',2));
			ptr=(ptr-1+n)%n;
			ptr=(ptr-1+n)%n;
			
			cur=-1;
			if (a[(ptr+1+n)%n]==i-1) cur=0;
			else if (a[ptr]==i-1) cur=1;
			if (cur!=-1){
				if (best==-1 || cur<best){
					best=cur;
					size=ans.size();
				}
			}
		}
		
		if (best==-1) return false;
		
		while (ans.size()>size){
			pair<char,int> op=ans.back();
			ans.pop_back();
			
			if (op.first=='a'){
				ptr+=op.second;
				ptr%=n;
			}else{
				for (int j=0;j<op.second;++j){
					a[ptr]=a[(ptr+1)%n];
					a[(ptr+1)%n]=a[(ptr+2)%n];
					a[(ptr+2)%n]=i;
				}
			}
		}
		
		if (best==1){
//printf("	");for (int j=0;j<n;++j){printf("%d ",a[j]);}puts("");
			ans.push_back(make_pair('a',1));
			--ptr;
			if (ptr<0) ptr+=n;
			best=-1;
			for (int _=0;_<n;++_){
				int cur=-1;
				if (a[(ptr+3)%n]==0) cur=0;
				else if (a[(ptr+4)%n]==0) cur=1;
				if (cur!=-1){
					if (best==-1 || cur<best){
						best=cur;
						size=ans.size();
					}
				}
			
				ans.push_back(make_pair('b',1));
				int bak=a[(ptr+2)%n];
				a[(ptr+2)%n]=a[(ptr+1)%n];
				a[(ptr+1)%n]=a[(ptr+0)%n];
				a[(ptr+0)%n]=bak;
			
				ans.push_back(make_pair('a',2));
				ptr=(ptr-1+n)%n;
				ptr=(ptr-1+n)%n;
			
				cur=-1;
				if (a[(ptr+3)%n]==0) cur=0;
				else if (a[(ptr+4)%n]==0) cur=1;
				if (cur!=-1){
					if (best==-1 || cur<best){
						best=cur;
						size=ans.size();
					}
				}
			
			}
//printf("	");for (int j=0;j<n;++j){printf("%d ",a[j]);}puts("");
			if (best==-1) return false;
		
			while (ans.size()>size){
				pair<char,int> op=ans.back();
				ans.pop_back();
			
				if (op.first=='a'){
					for (int j=0;j<op.second;++j){
						ptr=(ptr+1)%n;
					}
				}else{
					for (int j=0;j<op.second;++j){
						int bak=a[(ptr+0)];
						a[(ptr+0)]=a[(ptr+1)%n];
						a[(ptr+1)%n]=a[(ptr+2)%n];
						a[(ptr+2)%n]=bak;
					}
				}
			}
		}

	}
	int ca=0;
	while (a[ptr]!=0){
		++ca;
		ptr=(ptr-1+n)%n;
	}
	ans.push_back(make_pair('a',ca));
	
	for (int i=0;i<n;++i){
		if (a[(i+ptr)%n]!=i) return false;
	}
	
	vector< pair<char,int> > stack;
	for (int i=0;i<ans.size();++i){
		if (stack.size()>0 && stack.back().first==ans[i].first){
			stack.back().second+=ans[i].second;
			int base;
			if (stack.back().first=='a') base=n;
			else base=3;
			stack.back().second%=base;
			if (stack.back().second==0) stack.pop_back();
		}else{
			stack.push_back(ans[i]);
			int base;
			if (stack.back().first=='a') base=n;
			else base=3;
			stack.back().second%=base;
			if (stack.back().second==0) stack.pop_back();
		}
	}
	
	printf("%d\n",stack.size());
	for (int i=0;i<stack.size();++i){
		if (i) printf(" ");
		printf("%d%c",stack[i].second,stack[i].first);
	}
	puts("");
	
	return true;
}

int main()
{
    scanf("%d",&n);
//    n=100;
/*	srand(time(0)^21361631);
    for (int i=0;i<n;++i) a[i]=i;
    int ptr=0;
    for (int _=0;_<10000;++_){
    	pair<char,int> op;
    	if (rand()%2) op.first='a';
    	else op.first='b';
    	op.second=rand()%10+1;
    	if (op.first=='a'){
			for (int j=0;j<op.second;++j){
				ptr=(ptr+1)%n;
			}
		}else{
			for (int j=0;j<op.second;++j){
				int bak=a[(ptr+0)%n];
				a[(ptr+0)%n]=a[(ptr+1)%n];
				a[(ptr+1)%n]=a[(ptr+2)%n];
				a[(ptr+2)%n]=bak;
			}
		}
    }
    for (int i=0;i<n;++i){
    	printf("%d ",a[i]);
    }
    puts("");*/
    for (int i=0;i<n;++i){
    	scanf("%d",&a[i]);
    	--a[i];
    }
    
    if (!solve()) puts("NIE DA SIE");
    
    return 0;
}

