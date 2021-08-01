#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,a1,a2,b1,b2,c1,c2,d1,d2,e1,e2,f1,f2;
    long long x1,y1,z1,x2,y2,z2;
    scanf("%d",&t);
    while(t--)
    {
        a1=0,a2=0,b1=0,b2=0,c1=0,c2=0;
        d1=0,d2=0,e1=0,e2=0,f1=0,f2=0;
        cin>>x1>>y1>>z1>>x2>>y2>>z2;
        if(abs(x1)*1000>y1*y1+z1*z1)
        {
            a1=1;
            if(x1>0)
                d1=1;
        }
        if(abs(x2)*1000>y2*y2+z2*z2)
        {
            a2=1;
            if(x2>0)
                d2=1;
        }
        if(abs(y1)*1000>x1*x1+z1*z1)
        {
            b1=1;
            if(y1>0)
                e1=1;
        }
        if(abs(y2)*1000>x2*x2+z2*z2)
        {
            b2=1;
            if(y2>0)
                e2=1;
        }
        if(abs(z1)*1000>y1*y1+x1*x1)
        {
            c1=1;
            if(z1>0)
                f1=1;
        }
        if(abs(z2)*1000>y2*y2+x2*x2)
        {
            c2=1;
            if(z2>0)
                f2=1;
        }
        if(a1==a2&&b1==b2&&c1==c2&&d1==d2&&e1==e2&&f1==f2)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;

}
