#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

const int N = 100000;

int n;
char type[N];
int value[N],output[N];

vector <int> conclusion;

int size[N + 1][2];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		char buffer[2];
		scanf("%s", buffer);
		type[i] = *buffer;
		if (type[i] == '$') {
			scanf("%d", value + i);
		}
		if (type[i] == '$') {
			conclusion.push_back(i);
		}
	}
	if (conclusion.size()==0) {
		for (int st=0;st<2;++st) {
			int cur=st;
			for (int i=0;i<n;++i){
				cur^=(type[i]=='-');
			}
			if (cur==st){
				puts("consistent");
				for (int i=0;i<n;++i){
					printf("%c",cur?'t':'f');
					cur^=(type[i]=='-');
				}
				puts("");
				return 0;
			}
		}
		puts("inconsistent");
		return 0;
	} else {
		int allWrong=0;
		for (int i=0;i<conclusion.size();++i){
			for (int st=0;st<2;++st){
				int cur=st,cntTrue=0;
				int p=conclusion[i];
				do {
					cntTrue+=cur;
					--p;
					if (p<0) p+=n;
					cur^=(type[p]=='-');
				}while (type[p]!='$');
//printf("%d %d\n",st,cntTrue);
				size[value[conclusion[i]]][st]+=cntTrue;
			}
		}
		for (int i=0;i<=N;++i){
			allWrong+=size[i][0];
		}
		int final=-1;
		for (int answer=0;answer<=n;++answer){
			int cntTrue=allWrong-size[answer][0]+size[answer][1];
			if (cntTrue==answer){
				final=answer;
				break;
			}
		}
		if (final==-1){
			puts("inconsistent");
		}else{
			int cntTrue=0;
			for (int i=0;i<conclusion.size();++i){
				int st=value[conclusion[i]]==final;
				int cur=st;
				int p=conclusion[i];
				do {
					cntTrue+=cur;
					output[p]=cur;
					--p;
					if (p<0) p+=n;
					cur^=(type[p]=='-');
				}while (type[p]!='$');
			}
			assert(cntTrue==final);
			
			puts("consistent");
			for (int i=0;i<n;++i){
				printf("%c",output[i]?'t':'f');
			}
			puts("");
		}
	}
	
	return 0;
}
