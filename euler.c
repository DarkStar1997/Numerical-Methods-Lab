#include<stdio.h>
float fun(float x,float y)
{
    return x+y;
}
int main()
{
    float a,b,x,y,h,t,k;
    printf("Enter the values of x0, y0, h and xn\n");
    scanf("%f%f%f%f",&a,&b,&h,&t);
    x=a;
    y=b;
    printf("x\t\ty\n");
    while(x<=t)
    {
        k=h*fun(x,y);
        y=y+k;
        x=x+h;
        printf("%f\t%f\n",x,y);
    }
}