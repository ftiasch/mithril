#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int iter_limit    =   30;

struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}


    Point operator +=(const Point &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point operator -=(const Point &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Point operator /=(double k) {
        x /= k;
        y /= k;
        return *this;
    }
    
    inline double norm()
    {
        return sqrt(x*x+y*y);
    }
};

istream &operator >>(istream &in, Point &p) {
    scanf("%lf%lf", &p.x, &p.y);
    return in;
}

ostream &operator <<(ostream &out, const Point &p) {
    printf("%.12f %.12f", p.x, p.y);
    return out;
}

Point points[8];

const double EPS = 1e-9;

int sign(double x) {
    return x < -EPS ? -1 : x > EPS;
}

inline Point operator -(const Point &a,const Point &b)
{
    return Point(a.x-b.x,a.y-b.y);
}

inline Point operator *(const Point &a,const double &b)
{
    return Point(a.x*b,a.y*b);
}

inline double det(const Point &a,const Point &b)
{
    return a.x*b.y-a.y*b.x;
}

inline bool pointInRec(const Point &o,const Point &a,const Point &b,const Point &c,const Point &d)
{
    double area=fabs(det(a-o,b-o))+fabs(det(b-o,c-o))+fabs(det(c-o,d-o))+fabs(det(d-o,a-o));
    area/=2;
    
    area-=(a-b).norm()*(c-b).norm();
    return sign(area)==0;
}

int main() {
    while (true) {
        Point sum;
        for (int i = 0; i < 8; ++ i) {
            cin >> points[i];
            sum.x += fabs(points[i].x);
            sum.y += fabs(points[i].y);
        }
        points[8]=points[4];
        
        if (sign(sum.x) == 0 && sign(sum.y) == 0) {
            break;
        }
        while (1) {
            sum = Point(0, 0);
            for (int i = 0; i < 4; ++ i) {
                sum += points[i];
            }
            for (int i = 4; i < 8; ++ i) {
                sum -= points[i];
            }
            sum /= 4;
            
            if (sign(sum.x) == 0 && sign(sum.y) == 0) {
                break;
            }
            for (int i = 0; i < 4; ++ i) {
                Point next = points[i]-sum;
                if (pointInRec(next,points[4],points[5],points[6],points[7])){
                    points[i]=next;
                }else{
                    double l=0,r=1;
                    for (int _=0;_<iter_limit;++_){
                        double mid=(l+r)/2;
                        next=points[i]-sum*mid;
                        if (pointInRec(next,points[4],points[5],points[6],points[7])){
                            l=mid;
                        }else{
                            r=mid;
                        }
                    }
                    points[i]=points[i]-sum*l;
                }
            }
        }
        
        for (int i=0;i<4;++i){
            cout << points[i] << endl;
        }
    }
    return 0;
}
