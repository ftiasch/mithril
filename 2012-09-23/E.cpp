#include <cstdio>
#include <cstring>
#include <cstdlib>

const int maxn	=	55;

const int dx[]	=	{0,1,0,-1};
const int dy[]	=	{1,0,-1,0};

int n;
char s[maxn][maxn];
int color[maxn][maxn],nc,size[maxn*maxn],cnt;

inline void flood(int x,int y,int c)
{
	if (x<0 || x>=n || y<0 || y>=n) return;
	if (s[x][y]!='#') return;
	if (color[x][y]!=-1) return;
	color[x][y]=c;
	++cnt;
	for (int k=0;k<4;++k){
		flood(x+dx[k],y+dy[k],c);
	}
}

int main()
{
	for (;scanf("%d",&n)==1 && n;){
		for (int i=0;i<n;++i){
			scanf("%s",s[i]);
		}
		int ans=0;
		memset(color,-1,sizeof(color));
		nc=0;
		for (int i=0;i<n;++i){
			for (int j=0;j<n;++j){
				if (s[i][j]=='#'){
					if (color[i][j]==-1){
						cnt=0;
						flood(i,j,nc);
						size[nc++]=cnt;
					}
					int len[4];
					for (int k=0;k<4;++k){
						int x=i+dx[k],y=j+dy[k];
						len[k]=0;
						while (x>=0 && x<n && y>=0 && y<n && s[x][y]=='#'){
							++len[k];
							x+=dx[k];
							y+=dy[k];
						}
					}
					
					if (len[0]>0 && len[0]==len[1] && len[0]==len[2] && len[0]==len[3]){
						if (len[0]+len[1]+len[2]+len[3]+1==size[color[i][j]]){
							++ans;
						}
					}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

