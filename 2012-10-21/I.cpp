#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int ceilDiv(int a,int b)
{
    return (a+b-1)/b;
}

int main()
{
    int N,M,A,B;
    scanf("%d%d%d%d",&M,&N,&B,&A);
    int a=N%A,b=M%B;
    int res=(N/A)*(M/B);
    if (a){
        res+=ceilDiv(M/B,A/a);
    }
    if (b){
        res+=ceilDiv(N/A,B/b);
    }
    if (a && b){
        if ((M/B)%(A/a)==0 && (N/A)%(B/b)==0){
            ++res;
        }
    }
    printf("%d\n",res);
    return 0;
}
