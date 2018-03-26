#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double compute(double *a, double *x, int n, double val)
{
	double ans=a[0], p=1.0;
	for(int i=1; i<n; i++)
	{
		p*=(val-x[i-1]);
		ans=ans+a[i]*p;
	}
	return ans;
}
void main()
{
	printf("Enter the number of points\n");
	int n; scanf("%d", &n);
	/*for(int i=1; i<=n; i++)
	{
		int a=1; printf("%d ", a);
		for(int j=1; j<=i; j++)
		{
			a=a*(i-j+1)/j;
			printf("%d ", a);
		}
		printf("\n");
	}*/
	double *x=(double*) malloc(n*sizeof(double));
	double *y=(double*) malloc(n*sizeof(double));
	double *a=(double*) malloc(n*sizeof(double));
	printf("Enter the points: \n");
	for(int i=0; i<n; i++)
		scanf("%lf %lf", x+i, y+i);
	a[0]=y[0]; double denom=1.0, diff=x[1]-x[0];
	for(int i=1; i<n; i++)
	{
		double delta=1.0;
		denom*=i;
		for(int j=0; j<=i; j++)
		{
			if(j==0)
				//printf("%lf ", delta);
				a[i]=a[i]+y[i];
			else
			{
				delta=delta*(i-j+1)/j;
				//printf("%lf ", j&1?-delta:delta);
				a[i]=a[i]+delta*(j&1?-y[i-j]:y[i-j]);
			}
		}
		a[i]/=(denom*pow(diff, i));
		//printf("\n");
	}
	/*printf("Coefficients: \n");
	for(int i=0; i<n; i++)
		printf("%lf\n", a[i]);
	printf("Computed values: \n");
	for(int i=0; i<n; i++)
		printf("%lf\n", compute(a, x, n, x[i]));*/
	printf("Coefficients\t\tGiven X values\t\tGiven Y values\t\tComputed Y values\n");
	for(int i=0; i<n; i++)
		printf("%lf\t\t%lf\t\t%lf\t\t%lf\n", a[i], x[i], y[i], compute(a, x, n, x[i]));
	free(x); free(y); free(a);
}
