#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;

const int maxn     =    100005;

long long dx1[maxn],dy1[maxn],dy2[maxn],dx2[maxn];
int n,m,q,ansi[maxn],ansj[maxn],tarx[maxn],tary[maxn],id[maxn];

inline bool cmp(const int &i,const int &j)
{
    return tarx[i]+tary[i]<tarx[j]+tary[j]
        || tarx[i]+tary[i]==tarx[j]+tary[j] && tarx[i]<tarx[j];
}

inline void getX(int &i,int &j,int x,int y)
{
    int index=upper_bound(dx2,dx2+m+1,x-dx1[i])-dx2;
    if (index>0) --index;
    j=index;
}

inline void getY(int &i,int &j,int x,int y)
{
    int index=upper_bound(dy1,dy1+n+1,y-dy2[j])-dy1;
    if (index>0) --index;
    i=index;
}

const int base  =   (1<<20)-1;

int flg[base+10],stamp;

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    dx1[0]=dy1[0]=dx2[0]=dy2[0]=0;
    for (int i=1;i<=n;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        dx1[i]=x;
        dy1[i]=y;
    }
    for (int i=1;i<=m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        dx2[i]=x;
        dy2[i]=y;
    }
    
    for (int it=0;it<q;++it){
        scanf("%d%d",&tarx[it],&tary[it]);
        id[it]=it;
    }
    sort(id,id+q,cmp);
    
    int i=0,j=0,cnt=0;
    for (int k=0;k<q;++k){
        int u=id[k];
        int x=tarx[u],y=tary[u];
        int type=rand()&1;
++stamp;
        while (dx1[i]+dx2[j]!=x || dy1[i]+dy2[j]!=y){
            int key=((long long)i*1000007+j)&base;
            if (flg[key]==stamp){
                for (int dx=-2;dx<=2;++dx)
                    for (int dy=-2;dy<=2;++dy){
                        int xx=i+dx,yy=j+dy;
                        if (xx>=0 && xx<=n && yy>=0 && yy<=m){
                            if (dx1[xx]+dx2[yy]==x && dy1[xx]+dy2[yy]==y){
                                i=xx;
                                j=yy;
                                goto Break;
                            }
                        }
                    }
                ++cnt;
                //i=rand()%(n+1);
                //j=rand()%(m+1);
                i+=rand()%5;
                j+=rand()%5;
                if (i>=n) i=n;
                if (j>=m) j=m;
                ++stamp;
                Break:;
                type=rand()&1;
            }else{
                flg[key]=stamp;
            }
            if (type){
                getX(i,j,x,y);
                getY(i,j,x,y);
            }else{
                getY(i,j,x,y);
                getX(i,j,x,y);
            }
        }
        ansi[u]=i;
        ansj[u]=j;
    }
    
    for (int k=0;k<q;++k)
        printf("%d %d\n",ansi[k],ansj[k]);
//printf("%d\n",cnt);
    return 0;
}
