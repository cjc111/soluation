#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;
#define EPS 1e-10//根据题目需求修改

struct Point
{
    double x,y;
    Point(double xx=0,double yy=0):x(xx),y(yy){}//构造函数
    Point operator * (double a) {return Point(x*a,y*a);}
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

struct Shapes//存放各个图形的信息
{
    int sum_segment;
    char num;
    Segment s[25];
    queue<char>q;//存放和它相交的图形的名字

    bool operator <(Shapes tem)//重载小于号，根据图形的名字来排序。
    {
        return num<tem.num;
    }

}shape[30];

//////////////////
int sum_shape=0,x;
char t,s[20];
///////////////////全局变量

int Judge(double a,double b)//用来判断大小关系，消去误差。
{
    if(fabs(a-b)<EPS)
        return 0;
    if(a>b)
        return 1;
    else
        return -1;
}

void init(char t,int sum)//多边形和三角形和线段的输入。
{
    int n=++sum_shape;
    shape[n].sum_segment=sum;
    shape[n].num=t;
    for(int i=1;i<=sum;i++)
    {
        scanf(" (%lf,%lf)",&shape[n].s[i].p1.x,&shape[n].s[i].p1.y);//先输入一个点
        if(i>=2)
        {
            shape[n].s[i].p2.x=shape[n].s[i-1].p1.x;//
            shape[n].s[i].p2.y=shape[n].s[i-1].p1.y;//把第i个点和上一个点的连在一起形成第i-1个边。
        }
    }
    shape[n].s[1].p2.x=shape[n].s[sum].p1.x;
    shape[n].s[1].p2.y=shape[n].s[sum].p1.y;//再把第一个点和最后一个点连在一起，形成第i个边
    //如果是线段的情况，会形成两个相同的边，不影响答案。
}

void Swap(Point a,Point b)
{
    Point tem=a;
    a=b;
    b=tem;
}

void s_init(char t,char type)//矩形的输入
{
    int n=++sum_shape;
    shape[n].sum_segment=4;
    shape[n].num=t;
    Point a,c,b,d;
    if(type=='s')//正方形
    {
        scanf(" (%lf,%lf)",&a.x,&a.y);
        scanf(" (%lf,%lf)",&c.x,&c.y);
        /////////////////////////////
        b.x=(a.x+c.x-a.y+c.y)/2;
        b.y=(a.y+c.y+a.x-c.x)/2;
        d.x=(a.x+c.x+a.y-c.y)/2;
        d.y=(a.y+c.y-a.x+c.x)/2;
        //////////////////////////////已知正方形对角线求另外两点。
    }
    else//长方形
    {
        scanf(" (%lf,%lf)",&a.x,&a.y);
        scanf(" (%lf,%lf)",&b.x,&b.y);
        scanf(" (%lf,%lf)",&c.x,&c.y);
        //////////////////////////////////
        if(Judge(dot((b-a),(c-a)),0.0)==0)
            Swap(a,b);
        else if((dot((b-c),(a-c)),0.0)==0)
            Swap(c,b);
        ///////////////////////////////////让b点作为直角那个点
        d.x=a.x+c.x-b.x;
        d.y=a.y+c.y-b.y;
    }
    shape[n].s[1].p1=a,shape[n].s[1].p2=b;
    shape[n].s[2].p1=b,shape[n].s[2].p2=c;
    shape[n].s[3].p1=c,shape[n].s[3].p2=d;
    shape[n].s[4].p1=d,shape[n].s[4].p2=a;
}

bool Iscross(Point a,Point b,Point c,Point d)//这题没有明确说明是怎么样的相交，但是从案例可以发现 只要有交点就算相交，是非规范相交
{
    if(Judge(cross(b-a,c-a)*cross(b-a,d-a),0.0)==-1&&Judge(cross(d-c,a-c)*cross(d-c,b-c),0.0)==-1)//规范相交
        return 1;
/////////////////////////////////////////////////////////////////////////
    else if(Judge(cross(b-a,c-a),0.0)==0&&Judge(dot(c-b,c-a),0.0)<1)
        return 1;
    else if(Judge(cross(b-a,d-a),0.0)==0&&Judge(dot(d-b,d-a),0.0)<1)
        return 1;
    else if(Judge(cross(d-c,a-c),0.0)==0&&Judge(dot(a-c,a-d),0.0)<1)
        return 1;
    else if(Judge(cross(d-c,b-c),0.0)==0&&Judge(dot(b-c,b-d),0.0)<1)
        return 1;
/////////////////////////////////////////////////////////////////////////因为案例2说明这题有两个线段在同一个线上，但是不相交这种情况，所以要加上这个判断
    return 0;
}

bool Iscross_shape(int a,int b)
{
    for(int i=1;i<=shape[a].sum_segment;i++)
    {
        for(int j=1;j<=shape[b].sum_segment;j++)
        {
            if(Iscross(shape[a].s[i].p1,shape[a].s[i].p2,shape[b].s[j].p1,shape[b].s[j].p2))//判断a图形的第i个边和b图形的第j个边是否相交
                return 1;
        }
    }
    return 0;
}

void Count()//通过遍历判断两个图形是否相交
{
    int n=sum_shape;
    sort(shape+1,shape+n+1);//先排序，这样得到的答案就都是按照字典序排的
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j)//避免和自己判断
                continue;
            if(Iscross_shape(i,j))//判断i图形和j图形是否有交点
                shape[i].q.push(shape[j].num);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(shape[i].q.empty())
            printf("%c has no intersections\n",shape[i].num);
        else
        {
            printf("%c intersects with ",shape[i].num);
            if(shape[i].q.size()==1)
            {
                printf("%c\n",shape[i].q.front());
                shape[i].q.pop();//输出完也要把队列清空，下一组图形就不用初始化，下面操作也是这个原因。
            }
            else if(shape[i].q.size()==2)//两个的情况也要专门拿出来，因为两个的时候第一个名字后面是没有逗号的。
            {
                printf("%c ",shape[i].q.front());
                shape[i].q.pop();
                printf("and %c",shape[i].q.front());
                printf("\n");
                shape[i].q.pop();
            }
            else
            {
                while(shape[i].q.size()!=2)
                {
                    printf("%c, ",shape[i].q.front());
                    shape[i].q.pop();
                }
                printf("%c, ",shape[i].q.front());
                shape[i].q.pop();
                printf("and %c",shape[i].q.front());
                shape[i].q.pop();
                printf("\n");
            }
        }
    }
    printf("\n");
}

int main()
{

    while(scanf(" %c",&t))//字符串和字符的输入前面都加了空格，可以忽略这题数据里的空格。
    {
        if(t=='-')
        {
            Count();
            sum_shape=0;
            continue;
        }
        else if(t=='.')
            break;
        scanf(" %s",s);
        if(s[0]=='l')
            init(t,2);
        else if(s[0]=='t')
            init(t,3);
        else if(s[0]=='p')
        {
            scanf(" %d",&x);
            init(t,x);
        }
        else if(t=='s')
            s_init(t,s[0]);
        else
            s_init(t,s[0]);

    }
}
