#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

#define EPS 1e-10//根据题目需求修改

int Judge(double a,double b)//用来判断大小关系，消去误差。
{
    if(fabs(a-b)<EPS)
        return 0;
    if(a>b)
        return 1;
    else
        return -1;
}

struct Point
{
    double x,y;

    Point(double xx=0,double yy=0):x(xx),y(yy){}//构造函数

    Point operator + (Point p) {return Point(x+p.x,y+p.y);}//点加
    Point operator - (Point p) {return Point(x-p.x,y-p.y);}
    Point operator * (double a) {return Point(x*a,y*a);}
    Point operator / (double a) {return Point(x/a,y/a);}

    bool operator ==(const Point &p)
    {
        return (fabs(x-p.x)<EPS&&fabs(y-p.y)<EPS);
    }
};
typedef Point Vector;//向量

double dot(Vector a,Vector b)//向量内积
{
    return a.x*b.x+a.y*b.y;
}

double cross(Vector a,Vector b)//向量外积
{
    return a.x*b.y-a.y*b.x;
}

double dis(Point a)//计算点到原点的距离，也可以用来计算向量的长度。
{
    return sqrt(a.x*a.x+a.y+a.y);
}

bool isOrthogonal(Vector a,Vector b)//判断是否垂直
{
    return Judge(dot(a,b),0.0);
}

bool isParallel(Vector a,Vector b)//判断是否垂直
{
    return Judge(dot(a,b),1.0);
    //return Judge(cross(a,b),0.0);这两种一样
}

struct Segment//线段
{
    Point p1,p2;
    Segment(Point p1=0,Point p2=0):p1(p1),p2(p2){}
};
typedef Segment Line;

Point project(Segment s,Point p)//求垂足
{
    Vector v(s.p2-s.p1);
    double r=dot(p-s.p1,v)/(v.x*v.x+v.y*v.y);//求出比例
    return s.p1+v*r;
}
double DisPP(Point a,Point b)//两点间的距离
{
    return dis(a-b);//可理解为求ab向量的长度
}

double DisLP(Line l,Point p)//直线l到点p的距离
{
    return dis(cross(l.p2-l.p1,p-l.p1)/dis(l.p2-l.p1));
}

bool Iscross(Point a,Point b,Point c,Point d)//判断线段ab和线段cf是否相交
{
    if(Judge(cross(b-a,c-a)*cross(b-a,d-a),0.0)==-1&&Judge(cross(d-c,a-c)*cross(d-c,b-c),0.0)==-1)
        return 1;
    return 0;
}

Point CrossPoint(Point a,Point b,Point c,Point d)
{
    double d1=cross(b-a,c-a);
    double d2=cross(b-a,d-a);
    return (s2.p1*d2-s2.p2*d1)/(d2-d1);
}

int main()
{

}
