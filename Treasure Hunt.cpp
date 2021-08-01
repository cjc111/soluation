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
     Point operator - (Point p) {return Point(x-p.x,y-p.y);}
};
typedef Point Vector;//向量

double cross(Vector a,Vector b)//向量外积
{
    return a.x*b.y-a.y*b.x;
}

struct Segment//线段
{
    Point p1,p2;
    Segment(Point p1=0,Point p2=0):p1(p1),p2(p2){}
};

bool Iscross(Point a,Point b,Point c,Point d)
{
    if(Judge(cross(b-a,c-a)*cross(b-a,d-a),0.0)==-1&&Judge(cross(d-c,a-c)*cross(d-c,b-c),0.0)==-1)
        return 1;
    return 0;
}

int main()
{
    int sum,ans=500;
    Segment s[35];
    Point p;
    scanf("%d",&sum);
    for(int i=1;i<=sum;i++)
    {
        scanf("%lf%lf%lf%lf",&s[i].p1.x,&s[i].p1.y,&s[i].p2.x,&s[i].p2.y);
    }
    scanf("%lf%lf",&p.x,&p.y);
    int t1,t2;
    for(int i=1;i<=sum;i++)
    {
        t1=0,t2=0;
        for(int j=1;j<=sum;j++)
        {
            if(i==j)
                continue;
            if(Iscross(p,s[i].p1,s[j].p1,s[j].p2))
                t1++;
            if(Iscross(p,s[i].p2,s[j].p1,s[j].p2))
                t2++;
        }
        ans=min(ans,t1);
        ans=min(ans,t2);
    }
    if(sum==0)
        ans=0;
    printf("Number of doors = %d\n",ans+1);

}
