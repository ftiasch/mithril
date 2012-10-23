#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const double epsR   =   1e-1;
const double eps    =   1e-8;

struct Tpoint
{
    double x,y;
    Tpoint(){}
    Tpoint(double x,double y):x(x),y(y){}
    double norm(){return sqrt(x*x+y*y);}
    bool read(){return scanf("%lf%lf",&x,&y)==2;}
};

inline Tpoint operator -(const Tpoint &a,const Tpoint &b){return Tpoint(a.x-b.x,a.y-b.y);}

Tpoint a[2],b[2],o[4];

inline double sqr(double x)
{
    return x*x;
}

inline bool circleCrossCircle(Tpoint p1,double r1,Tpoint p2,double r2,Tpoint &cp1,Tpoint &cp2)
{
    double mx=p2.x-p1.x,sx=p2.x+p1.x,mx2=mx*mx;
    double my=p2.y-p1.y,sy=p2.y+p1.y,my2=my*my;
    double sq=mx2+my2,d=-(sq-sqr(r1-r2))*(sq-sqr(r1+r2));
    if (d+eps<0) return 0;
    if (d<eps) d=0;
    else d=sqrt(d);
    double x=mx*( (r1+r2)*(r1-r2)+mx*sx ) + sx*my2;
    double y=my*( (r1+r2)*(r1-r2)+my*sy ) + sy*mx2;
    double dx=mx*d,dy=my*d;
    sq*=2;
    cp1.x=(x-dy)/sq;cp1.y=(y+dx)/sq;
    cp2.x=(x+dy)/sq;cp2.y=(y-dx)/sq;
    return 1;
}

inline bool valid(Tpoint p)
{
    vector<double> A,B;
    for (int i=0;i<2;++i){
        A.push_back((p-a[i]).norm());
    }
    for (int i=0;i<2;++i){
        B.push_back((p-b[i]).norm());
    }
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    if (max(A[0],B[0])+epsR<min(B[1],A[1])){
//printf("len=    %lf\n",max(A[0],B[0])-min(B[1],A[1]));
        printf("%.10f %.10f %.10f\n",p.x, p.y, (max(A[0],B[0])+min(B[1],A[1]))/2);
        return true;
    }
    return false;
}

int main()
{
    while (a[0].read() && a[1].read() && b[0].read() && b[1].read()){
        if (a[0].norm()<eps && a[1].norm()<eps && b[0].norm()<eps && b[1].norm()<eps){
            break;
        }
        
        o[0]=a[0];
        o[1]=b[0];
        o[2]=a[1];
        o[3]=b[1];
        
        double R=1;
        bool found=false;
        while (!found){
            Tpoint cp1,cp2;
            for (int d1=-1;d1<=1;d1+=2){
                double r1=R+d1*epsR;
                for (int d2=-1;d2<=1;d2+=2){
                    double r2=R+d2*epsR;
                    for (int i=0;i<4;++i){
                        for (int j=0;j<i;++j){
                            if ((o[i]-o[j]).norm()<eps){
                                continue;
                            }
                            if ((o[i]-o[j]).norm()<=r1+r2+eps && (o[i]-o[j]).norm()+eps>=fabs(r1-r2)){
                                if (circleCrossCircle(o[i],r1,o[j],r2,cp1,cp2)){
                                    if (valid(cp1) || valid(cp2)){
                                        found=true;
                                        goto Break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            R*=2;
            Break:;
        }
    }
}
