#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

#define EPS 1e-12//根据题目需求修改

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
    bool operator !=(const Point &p)
    {
        return !(fabs(x-p.x)<EPS&&fabs(y-p.y)<EPS);
    }
};
typedef Point Vector;//向量

double cross(Vector a,Vector b)
{
    return a.x*b.y-a.y*b.x;
}

double dot(Vector a,Vector b)//向量内积
{
    return a.x*b.x+a.y*b.y;
}

struct Segment//线段
{
    Point p1,p2;
    Segment(Point p1=0,Point p2=0):p1(p1),p2(p2){}
};
typedef Segment Line;

bool Iscross(Segment s1,Segment s2)
{
    Point a=s1.p1,b=s1.p2,c=s2.p1,d=s2.p2;
    if(Judge(cross(b-a,c-a)*cross(b-a,d-a),0.0)==-1&&Judge(cross(d-c,a-c)*cross(d-c,b-c),0.0)==-1)//规范相交
        return 1;
    else if(Judge(cross(b-a,c-a),0.0)==0&&Judge(dot(c-b,c-a),0.0)<1)
        return 1;
    else if(Judge(cross(b-a,d-a),0.0)==0&&Judge(dot(d-b,d-a),0.0)<1)
        return 1;
    else if(Judge(cross(d-c,a-c),0.0)==0&&Judge(dot(a-c,a-d),0.0)<1)
        return 1;
    else if(Judge(cross(d-c,b-c),0.0)==0&&Judge(dot(b-c,b-d),0.0)<1)
        return 1;
    return 0;
}

Point CrossPoint(Segment s1,Segment s2)
{
    if(s1.p1==s2.p1||s1.p1==s2.p2)
        return s1.p1;
    if(s1.p2==s2.p1||s1.p1==s2.p2)
        return s1.p2;
    Vector a=s1.p2-s1.p1;
    Vector b=s2.p1-s1.p1;
    Vector c=s2.p2-s1.p1;
    double d1=cross(a,b);
    double d2=cross(a,c);
    return (s2.p1*d2-s2.p2*d1)/(d2-d1);
}

Point getHigh(Segment s)
{
    if(Judge(s.p1.y,s.p2.y)==1)
        return s.p1;
    else
        return s.p2;
}


bool Iscover(Segment s1,Segment s2)
{
    Point t=CrossPoint(s1,s2);
    Point p1=getHigh(s1);
    Point p2=getHigh(s2);
    if(p1.x==p2.x)
        return 1;
    double k1=(p1.y-t.y)/(p1.x-t.x);
    double k2=(p2.y-t.y)/(p2.x-t.x);
    if(k1*k2>0&&k1>k2&&p1.x-t.x>=p2.x-t.x)
        return 1;
    if(k1*k2>0&&k2>k1&&p2.x-t.x>=p1.x-t.x)
        return 1;
    return 0;
}

bool on(Segment s1,Segment s2)
{
    Point t1=CrossPoint(s1,s2);
    if(t1==s1.p1&&t1!=s2.p1&&t1!=s2.p2)
        return 1;
    if(t1==s1.p2&&t1!=s2.p1&&t1!=s2.p2)
        return 1;
    if(t1==s2.p1&&t1!=s1.p1&&t1!=s1.p2)
        return 1;
    if(t1==s2.p2&&t1!=s1.p1&&t1!=s1.p2)
        return 1;
    return 0;
}

double Count(Segment s1,Segment s2)
{
    Point t1=CrossPoint(s1,s2);
    Point t2;
    Point p1=getHigh(s1);
    Point p2=getHigh(s2);
    if(Judge(t1.y,p1.y)>-1||Judge(t1.y,p2.y)>-1)
        return 0.0;
    if((p2.x-t1.x)*(p1.x-t1.x)<=0)
    {
        if(Judge(p1.y,p2.y)==1)
        {
            Point p3(p1.x,p2.y);
            t2=CrossPoint(s1,Segment{p2,p3});
            return fabs(t2.x-p2.x)*fabs(p2.y-t1.y)*0.5;
        }
        else
        {
            Point p3(p2.x,p1.y);
            t2=CrossPoint(s2,Segment{p1,p3});
            return fabs(t2.x-p1.x)*fabs(p1.y-t1.y)*0.5;
        }
    }
    else
    {
        if(Judge(p1.y,p2.y)==1)
        {
            Point p3(t1.x,p2.y);

            if(Iscross(s1,Segment{p2,p3}))
                t2=CrossPoint(s1,Segment{p2,p3});
            else
            {
                p3.x=p1.x;
                p3.y=p2.y;
                t2=CrossPoint(s1,Segment{p2,p3});
            }
            return fabs(t2.x-p2.x)*fabs(t1.y-p2.y)*0.5;
        }
        else
        {
            Point p3(t1.x,p1.y);
            if(Iscross(s2,Segment{p1,p3}))
                t2=CrossPoint(s2,Segment{p1,p3});
            else
            {
                p3.x=p2.x;
                p3.y=p1.y;
                t2=CrossPoint(s2,Segment{p1,p3});
            }
            return fabs(t2.x-p1.x)*fabs(t1.y-p1.y)*0.5;
        }
    }

}
int main()
{
    int t,flag;
    Segment s1,s2;
    scanf("%d",&t);
    while(t--)
    {
        flag=1;
        scanf("%lf%lf%lf%lf",&s1.p1.x,&s1.p1.y,&s1.p2.x,&s1.p2.y);
        scanf("%lf%lf%lf%lf",&s2.p1.x,&s2.p1.y,&s2.p2.x,&s2.p2.y);
        if((s1.p1.y==s1.p2.y)||(s2.p1.y==s2.p2.y))
            flag=0;
        else if(Iscross(s1,s2)==0)
            flag=0;
        else if(Iscover(s1,s2))
            flag=0;
        if(flag==0)
        {
            printf("0.00\n");
            continue;
        }
        printf("%.2f\n",Count(s1,s2)+EPS);
    }
}
