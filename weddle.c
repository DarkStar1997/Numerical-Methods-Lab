#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    double x[100];
    double y[100];
    int i;
    printf("Enter the value of x and y :\n");
    for(i=0;i<=n;i++)
    {
        scanf("%lf%lf",&x[i],&y[i]);
    }
    double h=x[1]-x[0];
    double ans=(y[0]+y[n]);
    for(i=1;i<n;i++)
    {
        if((i%6)==0)
            ans+=2*y[i];
        else if(i%6==3)
                ans+=6*y[i];
        else if((i%6==2) || (i%6)==4)
                ans+=y[i];
        else
            ans+=(5*(y[i]));
    }
    ans=ans*(0.3*h);
    printf("ans =%lf",ans);
    return 0;
}
