#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps    =   1e-8;
const double pi     =   acos(-1.0);

struct Tpoint
{
    double x,y;
    Tpoint(){}
    Tpoint(double a,double b):x(a),y(b){}
    inline void read()
    {
        scanf("%lf%lf",&x,&y);
    }
    inline void rotate(int w,int h)
    {
        double tx=x,ty=y;
        x=ty;
        y=w-tx;
    }
    inline double norm()
    {
        return sqrt(x*x+y*y);
    }
};

inline Tpoint operator -(const Tpoint &a,const Tpoint &b){return Tpoint(a.x-b.x,a.y-b.y);}
inline double dot(const Tpoint &a,const Tpoint &b){return a.x*b.x+a.y*b.y;}
inline double det(const Tpoint &a,const Tpoint &b){return a.x*b.y-a.y*b.x;}
//=================

const int maxn      =   25;
const int maxIter   =   60;
const int maxBlock  =   79;

Tpoint p[maxn+10];
int n,W,H;

inline double dist(Tpoint a,Tpoint b,Tpoint c)
{
    if ((b-a).norm()>eps && dot(c-a,b-a)>=0 && dot(c-b,a-b)>=0){
        return fabs(det(c-a,b-a)/(b-a).norm());
    }
    return min( (a-c).norm(),(b-c).norm() );
}

inline double dist(Tpoint a,Tpoint b,Tpoint c,Tpoint d)
{
    return min(min( dist(a,b,c),dist(a,b,d) ) , min( dist(c,d,a),dist(c,d,b) ));
}

inline double calc(Tpoint a,Tpoint b)
{
    double res=1e100;
    for (int i=0;i<n;++i){
        res=min(res,dist(a,b,p[i],p[i+1]));
    }
    return res;
}

inline double dist(double L,double theta)
{
    Tpoint a(L*cos(theta),0),b(0,L*sin(theta));
    return calc(a,b);
}

inline bool check(double L)
{
    for (int r=0;r<4;++r){
        if (calc(Tpoint(0,0),Tpoint(W,0))<=L){
            return true;
        }
        if (calc(Tpoint(0,0),Tpoint(0,H))<=L){
            return true;
        }
        double step=pi/maxBlock;
        for (int block=0;block<maxBlock;++block){
            double l=block*step,r=l+step;
            for (int it=0;it<maxIter;++it){
                double m1=l+(r-l)/3,m2=r-(r-l)/3;
                if (dist(L,m1)+eps<dist(L,m2)){
                    r=m2;
                }else{
                    l=m1;
                }
            }
            if (dist(L,(l+r)/2)<=L){
                return true;
            }
        }
        for (int i=0;i<n;++i){
            p[i].rotate(W,H);
        }
        swap(W,H);
    }
    return false;
}

int main()
{
    scanf("%d%d%d",&n,&W,&H);
    
    for (int i=0;i<n;++i){
        p[i].read();
    }
    p[n]=p[0];
    
    double l=0,r=1e3;
    for (int it=0;it<40;++it){
        double mid=(l+r)/2;
        if (check(mid)){
            r=mid;
        }else{
            l=mid;
        }
    }
    printf("%.10f\n",r);
    return 0;
}
