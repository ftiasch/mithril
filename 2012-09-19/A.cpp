#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

const double pi		=	acos(-1.0);
const double eps	=	1e-8;

struct point
{
	double x,y;
	point(){}
	point(double x,double y):x(x),y(y){}
	void rotate90()
	{
		swap(x,y);
		x=-x;
		return;
/*		double si=sin(a),co=cos(a);		//si=1	co=0
		double x1=x,y1=y;
		x=x1*co-y1*si;
		y=x1*si+y1*co;*/
	}
	inline double norm()
	{
		return sqrt(x*x+y*y);
	}
};

inline point operator +(const point &a,const point &b){return point(a.x+b.x,a.y+b.y);}
inline point operator -(const point &a,const point &b){return point(a.x-b.x,a.y-b.y);}
inline point operator *(const point &a,const double &b){return point(a.x*b,a.y*b);}
inline point operator /(const point &a,const double &b){return point(a.x/b,a.y/b);}
inline double det(const point &a,const point &b){return a.x*b.y-a.y*b.x;}
inline double dot(const point &a,const point &b){return a.x*b.x+a.y*b.y;}
//====================================================================================

inline double getArea(double a,double b,double c)
{
	if (a>c) swap(a,c);
	if (b>c) swap(b,c);
	if (a+b-c<eps) return 0;
	double p=(a+b+c)/2.0;
	double s=sqrt( p*(p-a)*(p-b)*(p-c) );
	return s;
}

inline void move(point a,point b,point &na,point &nb,double w)
{
	point dir=b-a;
	dir.rotate90();
	double len=dir.norm();
	dir=dir*(w/len);
	na=a+dir;
	nb=b+dir;
}

inline bool cross(point a,point b,point c,point d,point &e)
{
	double s1=det(b-a,c-a);
	double s2=det(b-a,d-a);
	if (fabs(s1-s2)<1e-10) return false;
	e=(c*s2-d*s1)/(s2-s1);
	return true;
}

int main()
{
	freopen("baguette.in","r",stdin);
	freopen("baguette.out","w",stdout);

	double w,ab,bc,cd,da,ac;
	
	scanf("%lf",&w);
	scanf("%lf%lf%lf%lf%lf",&ab,&bc,&cd,&da,&ac);

	double hb=getArea(ac,bc,ab)*2/ac;
	double hd=getArea(ac,cd,da)*2/ac;
	
//printf("%lf %lf\n",hb,hd);
	
	point a(0,0),c(0,ac);
	point b(-hb,sqrt(ab*ab-hb*hb));
	point d(hd,sqrt(da*da-hd*hd));
	
	if (fabs((a-b).norm()-ab)>eps || fabs((b-c).norm()-bc)>eps){
		b.y=-b.y;
	}
	
	if (fabs((a-d).norm()-da)>eps || fabs((d-c).norm()-cd)>eps){
		d.y=-d.y;
	}
	
	point na1,na2,na3,na4,nb1,nb2,nb3,nb4;
	
	move(a,b,na1,nb1,w);
	move(b,c,na2,nb2,w);
	move(c,d,na3,nb3,w);
	move(d,a,na4,nb4,w);
	
	point na,nb,nc,nd,e;
	vector<point> p;
	if (cross(na1,nb1,na4,nb4,e)) p.push_back(e);
	if (cross(na1,nb1,na2,nb2,e)) p.push_back(e);
	if (cross(na2,nb2,na3,nb3,e)) p.push_back(e);
	if (cross(na3,nb3,na4,nb4,e)) p.push_back(e);
	
	double ans=0;
	for (int i=0;i<p.size();++i){
		ans+=(p[i]-p[(i+1)%p.size()]).norm();
	}
	
	printf("%.10f\n",ans);
	
	
	return 0;
}

