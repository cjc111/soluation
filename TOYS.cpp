#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
using namespace std;

#define EPS 1e-8//根据题目需求修改

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
typedef Segment Line;

bool Isinit(Segment s1,Segment s2,Point p)//通过向量的外积判断在不在这个区域里面。
{
    Vector a=p-s1.p1;
    Vector b=s1.p2-s1.p1;
    Vector c=p-s2.p1;
    Vector d=s2.p2-s2.p1;
    if(Judge(cross(b,a)*cross(d,c),0.0)==-1)
        return 1;
    return 0;
}
///////////////
int sum[5005];
Segment s[5005];
int n,m,t=0;
//////////////全局变量

int main()
{
    while(scanf("%d",&n))
    {
        if(n==0)
            break;
        if(t++)
            printf("\n");//最后一个答案后面不输出空格，不过这题没有卡这个输出
        memset(sum,0,sizeof(sum));
        scanf("%d%lf%lf%lf%lf",&m,&s[0].p1.x,&s[0].p1.y,&s[n+1].p2.x,&s[n+1].p2.y);
        s[0].p2.x=s[0].p1.x;
        s[0].p2.y=s[n+1].p2.y;
        s[n+1].p1.x=s[n+1].p2.x;
        s[n+1].p1.y=s[0].p1.y;//把题目没有给的左下角和右上角两个点补上
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf",&s[i].p1.x,&s[i].p2.x);
            s[i].p1.y=s[0].p1.y;
            s[i].p2.y=s[0].p2.y;
        }
        Point tem;
        for(int i=1;i<=m;i++)
        {
            scanf("%lf%lf",&tem.x,&tem.y);
            for(int i=0;i<=n;i++)
            {
                if(Isinit(s[i],s[i+1],tem))
                {
                    sum[i]++;
                    break;
                }
            }
        }
        for(int i=0;i<=n;i++)
        {
            printf("%d: %d\n",i,sum[i]);
        }
    }

}
