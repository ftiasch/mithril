#include <cstdio>
#include <cstring>
using namespace std;

int n;
char number[16];

int dfs(int step,long long sum,long long last,int sign)
{
    if (step==n){
        sum+=last*sign;
        return sum==0 && sign==-1;
    }
    
    //=
    int res=0;
    if (sign==1){
        res+=dfs(step+1,sum+last*sign,(number[step]-'0'),-1);
    }
    
    //+
    res+=dfs(step+1,sum+last*sign,(number[step]-'0'),sign);
    
    //concate
    res+=dfs(step+1,sum,last*10+(number[step]-'0'),sign);
    
    return res;
}

int main() {
    while (scanf("%s", number) == 1) {
        if (strcmp(number, "END") == 0) {
            break;
        }
        n = strlen(number);
        int result=dfs(1,0,number[0]-'0',1);
        printf("%d\n", result);
    }
    return 0;
}
