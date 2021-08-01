#include <iostream>
#include <stdio.h>
#include <math.h>
#define EPS 1e-10
using namespace std;

struct Point
{
    double x,y;
    Point(double xx=0,double yy=0):x(xx),y(yy){}
};
typedef Point Vector;

double dot(Vector a,Vector b)
{
    return a.x*b.x+a.y*b.y;
}

double cross(Vector a,Vector b)
{
    return a.x*b.y-a.y*b.x;
}

bool Equal(double a,double b)
{
    return (fabs(a-b)<EPS);
}


int main()
{
    int t;
    double x1,x2,x3,x4,y1,y2,y3,y4;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        Vector a(x2-x1,y2-y1);
        Vector b(x4-x3,y4-y3);
        if(Equal(dot(a,b),0.0)==1)
            printf("1\n");
        else if(Equal(cross(a,b),0.0)==1)
            printf("2\n");
        else
            printf("0\n");
    }
}
