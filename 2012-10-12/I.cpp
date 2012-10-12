#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;

struct Tpoint
{
    double x,y;
    Tpoint(){}
    Tpoint(double x,double y):x(x),y(y){}
    inline double norm()
    {
        return sqrt(x*x+y*y);
    }
    inline void read()
    {
        scanf("%lf%lf",&x,&y);
/*        x=rand()%1000;
        y=rand()%1000;*/
    }
    inline void show()
    {
        printf("%.10f %.10f\n",x,y);
    }
};

inline Tpoint operator +(const Tpoint &a,const Tpoint &b){return Tpoint(a.x+b.x,a.y+b.y);}
inline Tpoint operator -(const Tpoint &a,const Tpoint &b){return Tpoint(a.x-b.x,a.y-b.y);}
inline Tpoint operator *(const Tpoint &a,const double &b){return Tpoint(a.x*b,a.y*b);}
inline Tpoint operator /(const Tpoint &a,const double &b){return Tpoint(a.x/b,a.y/b);}
inline double dot(const Tpoint &a,const Tpoint &b){return a.x*b.x+a.y*b.y;}
inline double det(const Tpoint &a,const Tpoint &b){return a.x*b.y-a.y*b.x;}
//==========================================================================================

const double pi     =   acos(-1.0);
const double eps    =   1e-8;

const int iter_num  =   32;
const int inter_num =   500;
//O(iter_num*inter_num*nlogn)
//nlogn is about 50

const int maxn  =   15;

Tpoint p[maxn];
int n;
double L,R;

inline double solve(Tpoint p0)
{
    double ang[n*2];
    double res=1e100;
    for (int i=0;i<n;++i){
        Tpoint cur=p[i]-p0;
        if (cur.norm()>R+eps || cur.norm()+eps<L){
            //check the distance range
            return res;
        }
        ang[i]=atan2(cur.y,cur.x);
    }
    sort(ang,ang+n);
    for (int i=0;i<n;++i){
        ang[i+n]=ang[i]+2*pi;
    }
    for (int i=0;i<n;++i){
        if (ang[i]+pi>=ang[i+n-1]){
            //check the angle range
            res=min(res,ang[i+n-1]-ang[i]);
        }
    }
    return res;
}

inline double solve(Tpoint o,double ang)
{
    return solve(o+Tpoint(cos(ang),sin(ang))*R);
}

inline double solve(Tpoint o,double l,double r,Tpoint &ans)
{
    double t=solve(o,l);
    if (t>1e20) return 1e100;
    for (int _=0;_<iter_num;++_){
        double m1=(l*2+r)/3;
        double m2=(l+r*2)/3;
        if (solve(o,m1)+eps<solve(o,m2)){
            r=m2;
        }else{
            l=m1;
        }
    }
    ans=o+Tpoint(cos(l),sin(l))*R;
    return solve(o,l);
}

inline double sqr(double x)
{
    return x*x;
}

inline bool circleCrossCircle(Tpoint p1,double r1,Tpoint p2,double r2,Tpoint &cp1,Tpoint &cp2)
{
    double mx=p2.x-p1.x,sx=p2.x+p1.x,mx2=mx*mx;
    double my=p2.y-p1.y,sy=p2.y+p1.y,my2=my*my;
    double sq=mx2+my2,d=-(sq-sqr(r1-r2))*(sq-sqr(r1+r2));
    if (d+eps<0) return false;
    if (d<eps) d=0;
    else d=sqrt(d);
    double x=mx*( (r1+r2)*(r1-r2)+mx*sx ) + sx*my2;
    double y=my*( (r1+r2)*(r1-r2)+my*sy ) + sy*mx2;
    double dx=mx*d,dy=my*d;
    sq*=2;
    cp1.x=(x-dy)/sq;cp1.y=(y+dx)/sq;
    cp2.x=(x+dy)/sq;cp2.y=(y-dx)/sq;
    return true;
}

inline bool circleCrossLine(Tpoint o,double r,Tpoint a,Tpoint b,Tpoint &cp1,Tpoint &cp2)
{
    double d=fabs(det(a-o,b-o)/(a-b).norm());
    if (r+eps<d) return false;
    Tpoint dir=b-a;
    dir=dir/dir.norm();
    Tpoint foot=a+dir*dot(o-a,dir);
    double len=sqrt(fabs(r*r-d*d));
    cp1=foot+dir*len;
    cp2=foot-dir*len;
    return true;
}

int main()
{
    srand(time(0)^151671);
    scanf("%d%lf%lf",&n,&L,&R);
    for (int i=0;i<n;++i){
        p[i].read();
    }
//printf("%.10f\n",solve(Tpoint(4.9749371855331,0.5)));
    
    double res=1e100;
    Tpoint best;
    for (int i=0;i<n;++i){
        Tpoint cp1,cp2;
        vector<Tpoint> bak;
        for (int j=0;j<n;++j){
            if (i!=j){
                if (circleCrossCircle(p[i],R,p[j],R,cp1,cp2)){
                    bak.push_back(cp1);bak.push_back(cp2);
                }
                if (circleCrossCircle(p[i],R,p[j],L,cp1,cp2)){
                    bak.push_back(cp1);bak.push_back(cp2);
                }
            }
        }
        for (int j=0;j<n;++j){
            for (int k=j+1;k<n;++k){
                if (circleCrossLine(p[i],R,p[j],p[k],cp1,cp2)){
                    bak.push_back(cp1);bak.push_back(cp2);
                }
            }
        }
        
        vector<double> special;
        for (int j=0;j<bak.size();++j){
            Tpoint cur=bak[j]-p[i];
            special.push_back(atan2(cur.y,cur.x));
        }
        sort(special.begin(),special.end());
        special.push_back(special[0]+2*pi);
        
        for (int _=1;_<special.size();++_){
            double left=special[_-1],right=special[_];
            double step=(right-left)/inter_num;
            for (int j=0;j<inter_num;++j){
                double l=left+step*j,r=l+step;
                Tpoint o;
                double tmp=solve(p[i],l,r,o);
                if (tmp+eps<res){
                    res=tmp;
                    best=o;
                }
            }
        }
    }
    if (res>1e20){
        puts("impossible");
    }else{
//printf("my_res  =   %.10f\n",res);
        best.show();
    }
    return 0;
}

