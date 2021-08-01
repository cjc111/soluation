#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
#define EPS 1e-9
struct Point
{
    double x,y;

    Point(double xx=0,double yy=0):x(xx),y(yy){}

    Point operator + (Point p) {return Point(x+p.x,y+p.y);}//点加
    Point operator - (Point p) {return Point(x-p.x,y-p.y);}
    Point operator * (double a) {return Point(x*a,y*a);}
    Point operator / (double a) {return Point(x/a,y/a);}
};
typedef Point Vector;

struct Segment
{
    Point p1,p2;
    Segment(Point p1,Point p2):p1(p1),p2(p2){}
};

double dot(Vector a,Vector b)//向量内积
{
    return a.x*b.x+a.y*b.y;
}

Point project(Segment s,Point p)
{
    Vector v(s.p2-s.p1);
    double r=dot(p-s.p1,v)/(v.x*v.x+v.y*v.y);
    return s.p1+v*r;
}

int main()
{
    double x1,y1,x2,y2,x,y;
    int q;
    scanf("%lf%lf%lf%lf%d",&x1,&y1,&x2,&y2,&q);
    Point p1(x1,y1),p2(x2,y2),p;
    Segment s(p1,p2);
    while(q--)
    {
        scanf("%lf%lf",&x,&y);
        p.x=x,p.y=y;
        Point ans=project(s,p);
        printf("%.8f %.8f\n",ans.x,ans.y);
    }
    return 0;

}
