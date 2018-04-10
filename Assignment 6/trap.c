#include <stdio.h>
#include <stdlib.h>
double func(double x)
{
	//return 4*x-3*x*x;
	return x/(1+x);
}
void main()
{
	printf("Enter the number of points:\n");
	int n; scanf("%d", &n);
	double x[n], y[n];
/*	printf("Enter the points as pairs of (x, y)\n");*/
/*	for(int i=0; i<n; i++)*/
/*		scanf("%lf %lf", x+i, y+i);*/
	printf("Enter the x values:\n");
	for(int i=0; i<n; i++)
	{
		scanf("%lf", x+i);
		y[i]=func(x[i]);
	}
	double h=x[1]-x[0], ans=h/2*(y[0]+y[n-1]);
	for(int i=1; i<n-1; i++)
		ans=ans+h*y[i];
	printf("The answer is: %lf\n", ans);
}
