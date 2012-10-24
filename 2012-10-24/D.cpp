#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const long double eps    =   1e-8;

struct Tpoint
{
    long double x,y;
    Tpoint(){}
    Tpoint(long double x,long double y):x(x),y(y){}
    long double norm(){return sqrtl(x*x+y*y);}
    Tpoint rotate(long double ang)
    {
        long double co=cosl(ang),si=sinl(ang);
        return Tpoint(co*x-si*y,si*x+co*y);
    }
    Tpoint rotate90()
    {
        return Tpoint(-y,x);
    }
    void show()
    {
        printf("%.10f %.10f\n",(double)x,(double)y);
    }
};

inline bool operator <(const Tpoint &a,const Tpoint &b){return a.x+eps<b.x || fabs(a.x-b.x)<eps && a.y+eps<b.y;}
inline Tpoint operator +(const Tpoint &a,const Tpoint &b){return Tpoint(a.x+b.x,a.y+b.y);}
inline Tpoint operator -(const Tpoint &a,const Tpoint &b){return Tpoint(a.x-b.x,a.y-b.y);}
inline Tpoint operator *(const Tpoint &a,const long double &b){return Tpoint(a.x*b,a.y*b);}
inline Tpoint operator /(const Tpoint &a,const long double &b){return Tpoint(a.x/b,a.y/b);}
inline long double dot(const Tpoint &a,const Tpoint &b){return a.x*b.x+a.y*b.y;}
inline long double det(const Tpoint &a,const Tpoint &b){return a.x*b.y-a.y*b.x;}
//========================================================================================

inline int sign(long double x)
{
    if (x<-eps) return -1;
    return x>eps;
}

inline long double sqr(long double x)
{
    return x*x;
}

inline bool circleCrossCircle(Tpoint p1,long double r1,Tpoint p2,long double r2,Tpoint &cp1,Tpoint &cp2)
{
    double dist=(p1-p2).norm();
    if (dist>r1+r2+eps) return false;
    if (dist+eps<fabs(r1-r2)) return false;
    long double mx=p2.x-p1.x,sx=p2.x+p1.x,mx2=mx*mx;
    long double my=p2.y-p1.y,sy=p2.y+p1.y,my2=my*my;
    long double sq=mx2+my2,d=-(sq - sqr(r1-r2) ) * (sq - sqr(r1+r2));
    if (d+eps*eps<0) return false;
    if (d<eps*eps) d=0;
    else d=sqrtl(d);
    
    long double x=mx*( (r1+r2)*(r1-r2) + mx*sx) + sx*my2;
    long double y=my*( (r1+r2)*(r1-r2) + my*sy) + sy*mx2;
    long double dx=mx*d,dy=my*d;
    sq*=2;
    cp1.x=(x-dy)/sq;cp1.y=(y+dx)/sq;
    cp2.x=(x+dy)/sq;cp2.y=(y-dx)/sq;
    return true;
}

inline bool circleCrossLine(Tpoint o,long double r,long double x,long double &y1,long double &y2)
{
    if (o.x-r<x+eps && x+eps<o.x+r){
        long double dx=x-o.x;
        long double dy=sqrt(r*r-dx*dx);
//cout << o.y << " " << dx  << " "<< dy << endl;
        y1=o.y+dy;
        y2=o.y-dy;
        return true;
    }
    return false;
}

const int maxn  =   25;
const int maxm  =   1005;

const Tpoint vertical = Tpoint(0,-1);

Tpoint p[maxn],answer[maxm];
long double len[maxn];
bool live[maxn];
int n,m,order[maxn];

struct Query
{
    long double time;
    int i;
}query[maxm];

inline bool byTime(const Query &a,const Query &b)
{
    return a.time<b.time;
}

inline int isStable(Tpoint ball,long double EPS)
{
    for (int i=0;i<n;++i){
        if (live[i]){
            long double dist=(ball-p[i]).norm();
            if (dist>len[i]+eps){
                return -1;//too far!!!
            }
        }
    }
    bool left=false,right=false;
    for (int i=0;i<n;++i){
        if (live[i]){
            long double dist=(ball-p[i]).norm();
            if (fabsl(dist-len[i])<EPS){
                if (fabsl(ball.x-p[i].x)<EPS){
                    return 0;//stable
                }
                if (p[i].x<ball.x){
                    left=true;
                }else{
                    right=true;
                }
            }
        }
    }
    if (left && right) return 0;//stable
    return 1;//need to move more
}

inline Tpoint getInitPos()
{
    for (int i=0;i<n;++i){
        Tpoint down(p[i].x,p[i].y-len[i]);
        if (isStable(down,eps)==0){
            return down;
        }
        Tpoint cp1,cp2;
        for (int j=0;j<i;++j){
            long double d=(p[i]-p[j]).norm();
            if (d<eps){
                //coincide!
                continue;
            }
            if (circleCrossCircle(p[i],len[i],p[j],len[j],cp1,cp2)){
                if (cp1.y<eps && isStable(cp1,eps)==0) return cp1;
                if (cp2.y<eps && isStable(cp2,eps)==0) return cp2;
            }
        }
    }
    assert(false);
}

inline int getTight(Tpoint ball)
{
    int ret=-1,cnt=0;
    long double best=1e100;
    while (ret==-1){
        for (int i=0;i<n;++i){
            if (live[i]){
                long double dist=(ball-p[i]).norm();
                if (fabsl(dist-len[i])<eps){
                    ++cnt;
                    if (len[i]+eps<best){
                        best=len[i];
                        ret=i;
                    }
                }
            }
        }
        //EPS*=2;
    }
//printf("cnt= %d\n",cnt);
    return ret;
}

inline bool byY(const Tpoint &a,const Tpoint &b)
{
    return a.y>b.y;
}

int main()
{
    cin >> n >> m;
    memset(live,true,sizeof(live));
    for (int i=0;i<n;++i){
        cin >> p[i].x;
        p[i].y=0;
    }
    for (int i=0;i<n;++i){
        cin >> len[i];
    }
    for (int i=0;i<n-1;++i){
        cin >> order[i];
    }
    for (int i=0;i<m;++i){
        cin >> query[i].time;
        query[i].i=i;
    }
    sort(query,query+m,byTime);
    
    Tpoint ball=getInitPos();
    long double currentTime=0;
    int index=0;
    for (int _=0;_<n-1;++_){
        int u=order[_]-1;
        live[u]=false;
        
        if (true){
            //fall downv
            vector<Tpoint> candidates;
            for (int i=0;i<n;++i){
                if (live[i]){
                    long double y1,y2;
                    if (circleCrossLine(p[i],len[i],ball.x,y1,y2)){
                        if (y1<eps){
                            candidates.push_back(Tpoint(ball.x,y1));
                        }
                        if (y2<eps){
                            candidates.push_back(Tpoint(ball.x,y2));
                        }
                    }
                }
            }
            sort(candidates.begin(),candidates.end(),byY);
            Tpoint nextPos=ball;
            for (int i=0;i<candidates.size();++i){
                if (isStable(candidates[i],eps)>=0){
                    nextPos=candidates[i];
                }else{
                    break;
                }
            }
            long double l=ball.y-nextPos.y;
            long double nextT=currentTime+l;
            while (index<m && query[index].time<=nextT+eps){
                answer[query[index].i]=ball+vertical*(query[index].time-currentTime);
                ++index;
            }
            ball=nextPos;
            currentTime=nextT;
        }
        
        if (true){
            //swing to the vertical
            for (int times=1;isStable(ball,eps)!=0;++times){
                int tie=getTight(ball);
                assert(tie!=-1);
                Tpoint down=p[tie]+vertical*len[tie];
                Tpoint cp1,cp2;
                Tpoint dir=ball-p[tie];
                vector<Tpoint> candidates;
                candidates.push_back(down);
                for (int i=0;i<n;++i){
                    if (live[i] && (p[i]-p[tie]).norm()>eps){
                        if (circleCrossCircle(p[i],len[i],p[tie],len[tie],cp1,cp2)){
                            if (cp1.y<eps){
                                int s1=sign(det(cp1-p[tie],ball-p[tie])/len[tie]);
                                int s2=sign(det(cp1-p[tie],down-p[tie])/len[tie]);
                                if (s1*s2<0){
                                    candidates.push_back(cp1);
                                }
                            }
                            cp1=cp2;
                            if (cp1.y<eps){
                                int s1=sign(det(cp1-p[tie],ball-p[tie])/len[tie]);
                                int s2=sign(det(cp1-p[tie],down-p[tie])/len[tie]);
                                if (s1*s2<0){
                                    candidates.push_back(cp1);
                                }
                            }
                        }
                    }
                }
                sort(candidates.begin(),candidates.end(),byY);
                Tpoint nextPos=ball;
                for (int i=0;i<candidates.size();++i){
                    if (isStable(candidates[i],eps)>=0){
                        nextPos=candidates[i];
                    }else{
                        break;
                    }
                }
                
                long double ang=asinl(det(ball-p[tie],nextPos-p[tie])/len[tie]/len[tie]);
                long double nextT=currentTime+fabsl(ang*len[tie]);
                while (index<m && query[index].time<=nextT+eps){
                    long double cur=(query[index].time-currentTime)/fabsl(ang*len[tie])*ang;
                    answer[query[index].i]=p[tie]+dir.rotate(cur);
                    ++index;
                }
                ball=nextPos;
                currentTime=nextT;
            }
        }
    }
    while (index<m){
        answer[query[index].i]=ball;
        ++index;
    }
    
    for (int i=0;i<m;++i){
        answer[i].show();
    }
    
    return 0;
}
