#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
struct Point
{
    double x,y;

    Point(double xx=0,double yy=0):x(xx),y(yy){}//构造函数

    Point operator + (Point p) {return Point(x+p.x,y+p.y);}//点加
    Point operator - (Point p) {return Point(x-p.x,y-p.y);}
    Point operator * (double a) {return Point(x*a,y*a);}
    Point operator / (double a) {return Point(x/a,y/a);}

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

struct Segment//线段
{
    Point p1,p2;
    Segment(Point p1=0,Point p2=0):p1(p1),p2(p2){}
};
typedef Segment Line;



double CrossPoint(Point a,Point b,double y)
{
    if(a.x==b.x)
        return a.x;
    else
        return b.x-(a.x-b.x)*(b.y-y)/(a.y-b.y);
}

struct Len
{
    double x1;
    double x2;
    bool operator < (Len tem)
    {
        return x1<tem.x1;
    }
}len[105];

int main()
{
    Segment H,P,O[105];
    int n,flag;
    double ans;
    while(scanf("%lf%lf%lf",&H.p1.x,&H.p2.x,&H.p1.y)&&H.p1.y)
    {
        memset(len,0,sizeof(len));
        H.p2.y=H.p1.y;
        scanf("%lf%lf%lf",&P.p1.x,&P.p2.x,&P.p1.y);
        P.p2.y=P.p1.y;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf%lf",&O[i].p1.x,&O[i].p2.x,&O[i].p1.y);
            O[i].p2.y=O[i].p1.y;
        }
        Point tem1,tem2;
        int s=0;
        for(int i=1;i<=n;i++)
        {
            if(O[i].p1.y<H.p1.y&&O[i].p1.y>P.p1.y)//错误
            {
                s++;
                len[s].x1=CrossPoint(O[i].p1,H.p2,P.p1.y);
                len[s].x2=CrossPoint(O[i].p2,H.p1,P.p1.y);
            }
        }
        flag=0,ans=0;
        sort(len+1,len+s+1);
        len[0].x2=P.p1.x;
        len[s+1].x1=P.p2.x;
        double max_right=P.p1.x;
        for(int i=1;i<=s+1;i++)
        {
            if(len[i].x1>max_right)
            {
                ans=max(ans,len[i].x1-max_right);//错误
                flag=1;
            }
            max_right=max(max_right,len[i].x2);
        }
        if(flag)
            printf("%.2f\n",ans);
        else
            printf("No View\n");
    }
}
