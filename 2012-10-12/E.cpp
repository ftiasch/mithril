#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const double pi =   acos(-1.0);

struct P3
{
    double x,y,z;
    P3(){}
    P3(double x,double y,double z):x(x),y(y),z(z){}
    inline double norm()
    {
        return sqrt(x*x+y*y+z*z);
    }
    inline void read()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
};

inline P3 operator +(const P3 &a,const P3 &b){return P3(a.x+b.x,a.y+b.y,a.z+b.z);}
inline P3 operator -(const P3 &a,const P3 &b){return P3(a.x-b.x,a.y-b.y,a.z-b.z);}
inline P3 operator *(const P3 &a,const double &b){return P3(a.x*b,a.y*b,a.z*b);}
inline P3 operator /(const P3 &a,const double &b){return P3(a.x/b,a.y/b,a.z/b);}
//====================================================================================

const int num_interval  =   1000;
const int iter_times    =   100;

const double eps    =   1e-8;

P3 p1,p2;
double r,d;

inline double calc(P3 a,P3 b)
{
    double d=(a-b).norm();
    double ang=acos( (2.0*r*r-d*d)/2.0/r/r );
    return ang*r;
}

inline double getDist(double mid,double radii,double z)
{
    P3 p3(radii*cos(mid),radii*sin(mid),z);
//printf("%lf %lf %lf\n",p3.x,p3.y,p3.z);
//printf("%lf %lf %lf\n",p1.x,p1.y,p1.z);
    return calc(p1,p3)+calc(p2,p3);
}

inline double solve(double l,double r,double radii,double z)
{
    for (int _=0;_<iter_times;++_){
        double m1=(l*2+r)/3;
        double m2=(l+r*2)/3;        
        if (getDist(m1,radii,z)<getDist(m2,radii,z)){
            r=m2;
        }else{
            l=m1;
        }
    }
    return getDist((l+r)/2,radii,z);
}

int main()
{
    scanf("%lf%lf",&r,&d);
    double r1=sqrt(fabs(r*r-d*d/4.0));
    
//    printf("r1= %lf\n",r1);
    
    p1.read();p2.read();
    
    double res=1e100;
    double step=2*pi/num_interval;
    for (int i=0;i<num_interval;++i){
        res=min(res,solve(i*step,i*step+step,r1,0.5*d));
    }
    
    P3 o1(0,0,0),o2(0,0,d);
    if (fabs((p1-o1).norm()-r)<eps && fabs((p2-o1).norm()-r)<eps){
//puts("a");
        res=min(res,calc(p1,p2));
    }
    if (fabs((p1-o2).norm()-r)<eps && fabs((p2-o2).norm()-r)<eps){
//puts("b");
        res=min(res,calc(p1,p2));
    }
    
    printf("%.10f\n",res);
    return 0;
}

