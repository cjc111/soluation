#include <iostream>
#include <stdio.h>
#include <math.h>
#include <queue>
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
    Point(double xx=0,double yy=0):x(xx),y(yy){}//构造函数加    Point operator - (Point p) {return Point(x-p.x,y-p.y);}
    Point operator - (Point p) {return Point(x-p.x,y-p.y);}
};
typedef Point Vector;//向量

double cross(Vector a,Vector b)//向量外积
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

bool Iscross(Point a,Point b,Point c,Point d)
{
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

Segment s[100005];

queue<int> ans;
int main()
{
    int sum,f,flag;
    while(scanf("%d",&sum))
    {
        if(sum==0)
            break;
        for(int i=1;i<=sum;i++)
            scanf("%lf%lf%lf%lf",&s[i].p1.x,&s[i].p1.y,&s[i].p2.x,&s[i].p2.y);
        for(int i=1;i<sum;i++)
        {
            flag=0;
            for(int j=i+1;j<=sum;j++)
            {
                if(Iscross(s[j].p1,s[j].p2,s[i].p1,s[i].p2))
                {
                  flag=1;
                  break;
                }
            }
            if(!flag)
                ans.push(i);
        }
        ans.push(sum);
        printf("Top sticks: ");
        f=1;
        while(!ans.empty())
        {
            if(f)
                printf("%d",ans.front());
            else
                printf(", %d",ans.front());
            f=0;
            ans.pop();
        }
        printf(".\n");

    }

}
