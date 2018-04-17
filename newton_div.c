#include <stdio.h>
#include <stdlib.h>
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
int main()
{
	printf("Enter the number of points:\n");
	int n; scanf("%d", &n);
	double x[n], y[n];
	printf("Enter the points as pairs (x,y)\n");
	for(int i=0; i<n; i++)
		scanf("%lf %lf", x+i, y+i);
	double coeff[n], tmp[n];
	coeff[0]=y[0];
	tmp[0]=y[0];
	for(int i=1; i<n; i++)
	{
		for(int j=0; j<n-i; j++)
		{
			double x_0, x_1;
			if(i==1)
			{
				x_0=y[j];
				x_1=y[j+1];
			}
			else
			{
				x_0=tmp[j];
				x_1=tmp[j+1];
			}
			tmp[j]=(x_0-x_1)/(x[j]-x[j+i]);
		}
		coeff[i]=tmp[0];
	}
	printf("Required coefficients:\n");
	for(int i=0; i<n; i++)
		printf("%lf\n", coeff[i]);
	printf("Enter the value to be computed\n");
	double tmp_x; scanf("%lf", &tmp_x);
	printf("%lf\n", compute(coeff, x, n, tmp_x));
}
