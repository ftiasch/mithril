#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define SIZE(a) ((int)(a).size())

const double eps    =   1e-8;
const double pi     =   acos(-1.0);

inline int Sign(double x)
{
    if (x<-eps) return -1;
    return x>eps;
}

inline double sqr(double x)
{
    return x*x;
}

struct Point
{
    double x,y,z;
    Point(){x=y=z=0;}
    Point(double x,double y,double z):x(x),y(y),z(z){}
    inline double norm()
    {
        return x*x+y*y+z*z;
    }
    inline double length()
    {
        return sqrt(norm());
    }
    
    inline void read()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
};

inline Point operator +(const Point &a,const Point &b){return Point(a.x+b.x,a.y+b.y,a.z+b.z);}
inline Point operator -(const Point &a,const Point &b){return Point(a.x-b.x,a.y-b.y,a.z-b.z);}
inline bool operator <(const Point &a,const Point &b){return Sign(a.x-b.x)<0 || Sign(a.x-b.x)==0 && Sign(a.y-b.y)<0 || Sign(a.x-b.x)==0 && Sign(a.y-b.y)==0 && Sign(a.z-b.z)<0;}
inline bool operator ==(const Point &a,const Point &b){return Sign(a.x-b.x)==0 && Sign(a.y-b.y)==0 && Sign(a.z-b.z)==0;}
inline Point operator *(const Point &a,const double &b){return Point(a.x*b,a.y*b,a.z*b);}
inline Point operator /(const Point &a,const double &b){return Point(a.x/b,a.y/b,a.z/b);}
inline Point det(const Point &a,const Point &b)
{
    return Point(a.y*b.z-a.z*b.y, -( a.x*b.z-a.z*b.x ),a.x*b.y-a.y*b.x);
}

inline double dot(const Point &a,const Point &b)
{
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
//====================================================

int mark[1005][1005];
Point info[1005];
int n,cnt;

double mix(const Point &a,const Point &b,const Point &c)
{
    return dot(a,det(b,c));
}

double area(int a,int b,int c)
{
    return (info[b]-info[a],info[c]-info[a]).length();
}

double volume(int a,int b,int c,int d)
{
    return mix(info[b]-info[a],info[c]-info[a],info[d]-info[a]);
}

struct Face
{
    int a,b,c;
    Face(){}
    Face(int a,int b,int c):a(a),b(b),c(c){}
    int& operator [](int k){
        if (k==0) return a;
        if (k==1) return b;
        return c;
    }
};

vector<Face> face;

inline void insert(int a,int b,int c)
{
    face.push_back(Face(a,b,c));
}

inline void add(int v)
{
    vector<Face> tmp;
    int a,b,c;
    ++cnt;    
    for (int i=0;i<SIZE(face);++i){
        a=face[i][0];
        b=face[i][1];
        c=face[i][2];
        if (Sign(volume(v,a,b,c))<0)
            mark[a][b]=mark[b][a]=mark[b][c]=mark[c][b]=mark[c][a]=mark[a][c]=cnt;
        else
            tmp.push_back(face[i]);
    }
    face=tmp;
    for (int i=0;i<SIZE(tmp);++i){
        a=face[i][0];
        b=face[i][1];
        c=face[i][2];
        if (mark[a][b]==cnt) insert(b,a,v);
        if (mark[b][c]==cnt) insert(c,b,v);
        if (mark[c][a]==cnt) insert(a,c,v);
    }
}

inline int Find()
{
    for (int i=2;i<n;++i){
        Point ndir=det(info[0]-info[i],info[1]-info[i]);
        if (ndir==Point()) continue;
        swap(info[i],info[2]);
        for (int j=i+1;j<n;++j){
            if (Sign(volume(0,1,2,j))!=0){
                swap(info[j],info[3]);
                insert(0,1,2);
                insert(0,2,1);
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    for (;scanf("%d",&n)==1;){
        for (int i=0;i<n;++i) info[i].read();
        sort(info,info+n);
        n=unique(info,info+n)-info;
        
        face.clear();
        random_shuffle(info,info+n);
        
        if (Find()){
            memset(mark,0,sizeof(mark));
            cnt=0;
            for (int i=3;i<n;++i) add(i);
            Point ans(0,0,0),o=info[0];
            double total=0;
            for (int i=0;i<SIZE(face);++i){
                double volume=fabs(mix(info[face[i][0]]-o,info[face[i][1]]-o,info[face[i][2]]-o));
                total+=volume;
                ans=ans+(o+info[face[i][0]]+info[face[i][1]]+info[face[i][2]])/4.0*volume;
            }
            ans=ans/total;
            
            double len=(ans-info[0]).length();
            for (int i=0;i<SIZE(face);++i){
                Point ndir=det(info[face[i][1]]-info[face[i][0]],info[face[i][2]]-info[face[i][0]]);
                len=min(len,fabs(dot(ans-info[face[i][0]],ndir))/ndir.length());
            }
            printf("%.3f\n",len);
        }
    }
    return 0;
}

