#include <cstdio>
#include <cstring>
#include <cstdlib>

const int limit =   22;

int f[1<<limit],n;
char s[1000];
int first[1000][26];

inline void update(int &a,int b)
{
    if (a<b) a=b;
}

int main()
{
    scanf("%d",&n);
    if (n>limit){
        puts("NO");
        return 0;
    }
    scanf("%s",s+1);
    int len=strlen(s+1);
    for (int i=0;i<n;++i){
        first[len][i]=len+1;
    }
    for (int i=len-1;i>=0;--i){
        memcpy(first[i],first[i+1],sizeof(first[i]));
        first[i][s[i+1]-'a']=i+1;
    }
    memset(f,0,sizeof(f));
    bool flg=true;
    for (int mask=0;mask<1<<n;++mask){
        int i=f[mask];
//printf("%d %d\n",mask,i);
        if (i==len+1){
            flg=false;
            break;
        }
        for (int ch=0;ch<n;++ch){
            if (mask>>ch&1){
                continue;
            }
            update(f[mask|1<<ch],first[i][ch]);
        }
    }
    printf("%s\n",flg?"YES":"NO");
    return 0;
}

