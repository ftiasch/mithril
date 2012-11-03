#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

const double eps    =   1e-8;

int main()
{
    freopen("deepest.in","r",stdin);
    freopen("deepest.out","w",stdout);
    
    double x,y,d;
    scanf("%lf%lf%lf",&x,&y,&d);
    double l=sqrt(x*x+y*y);
    if (d+eps<l){
        puts("Impossible");
    }else if (fabs(d-l)<eps){
        puts("Single staircase");
    }else{
        double dx=x/l,dy=y/l;
        double lambda=(d-l)/2.0;
        double tx=x+dx*lambda,ty=y+dy*lambda;
        printf("%.15f %.15f %.15f\n",tx,ty,lambda);
    }
    return 0;
}

