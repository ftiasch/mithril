#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100;

int a[N],f[N][N],s[N+1];

inline int dfs(int l,int r)
{
    if (l>r) return 0;
    int &res=f[l][r];
    if (res!=-1) return res;
    res=1000000000;
    for (int k=l;k<=r;++k){
        res=min(dfs(l+1,k)+(k-l)*a[l]+(k-l+1)*(s[r+1]-s[k+1])+dfs(k+1,r),res);
    }
    return res;
}

int main() {
    int testCount;
    scanf("%d", &testCount);
    for (int t = 1; t <= testCount; ++ t) {
        int n;
        scanf("%d", &n);
        s[0]=0;
        for (int i = 0; i < n; ++ i) {
            scanf("%d", a + i);
            s[i+1]=s[i]+a[i];
        }
        memset(f,-1,sizeof(f));
        printf("Case #%d: %d\n", t, dfs(0,n-1));
    }
    return 0;
}
