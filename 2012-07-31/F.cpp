#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

const double pi     =   acos(-1.0);
const double eps    =   1e-8;

inline double solveV(double h)
{
    double v1=((1-1.0/3.0)-(h-1.0/3.0*h*h*h));
    double R=sqrt(1-h*h);
    double v2=R*R*h/3.0;
    return v1+v2;
}

int main()
{
    double h,lambda;
    scanf("%lf%lf",&h,&lambda);
    
    double sina=1.0/lambda;
    double cosa=sqrt(1-sina*sina);
    
    double a=asin(sina);
    double c=acos(h);
    double angle=a+c;
    if (pi-2*angle<eps){
        puts("1.0000000000");
        return 0;
    }
    double len=sqrt( 2-2*cos(pi-2*angle) );
    
    double hh=len*cosa-h;

//printf("%lf\n",hh);
    double v=4.0/3;
    double s=4*pi;
    double v1=solveV(hh);
    double s1=v1;
    
    double v2=solveV(h);
    double s2=v2;
    double s3=v-s2;
    
    printf("%.10f\n",s1/s3);
    
    return 0;
}

