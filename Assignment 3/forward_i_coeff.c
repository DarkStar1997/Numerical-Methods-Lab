#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
double eval_pol(double *pol, int degree, double point)
{
	double ans=0;
	for(int i=degree; i>=0; i--)
		ans=ans*point+pol[i];
	return ans;
}
void main()
{
	int n; printf("Enter the number of points\n");
	scanf("%d", &n);
	double *X=(double*)malloc(n*sizeof(double));
	double *Y=(double*)malloc(n*sizeof(double));
	double *theta=(double*)malloc(n*sizeof(double));
	printf("Enter the points and theta values as triplets: (x, y, theta)\n");
	for(int i=0; i<n; i++)
		scanf("%lf %lf %lf", X+i, Y+i, theta+i);
	double **A=allocate(n, n);
	for(int i=0; i<n; i++)
		if(i==0)
			A[0][i]=1;
		else
			A[0][i]=-X[i-1];
	for(int i=0; i<n; i++)
		if(i==0)
			A[1][i]=0;
		else
			A[1][i]=1;
	for(int i=2; i<n; i++)
		for(int j=0; j<n; j++)
			A[i][j]=0;
	double **tmp=allocate(n, n);
	copyOf(A, tmp, n, n);
	for(int i=1; i<n-1; i++)
	{
		for(int j=i+1; j<n; j++)
		{
			double *t_tmp=(double*)malloc((2+i)*sizeof(double));
			for(int k=0; k<2+i; k++)
			{
				t_tmp[k]=tmp[k][j];
				tmp[k][j]=0;
			}
			for(int l=0; l<=1; l++)
				for(int k=0; k+l<2+i; k++)
					tmp[k+l][j]+=A[l][i]*t_tmp[k];
			free(t_tmp);
		}
	}
	double* coeff=(double*)malloc(n*sizeof(double));
	for(int i=0; i<n; i++)
	{
		coeff[i]=0;
		for(int j=i; j<n; j++)
			coeff[i]=coeff[i]+theta[j]*tmp[i][j];
	}
	printf("Required coefficients are:\n");
	for(int i=0; i<n; i++)
		printf("%lf\n", coeff[i]);
	//print(tmp, n, n);
	printf("Comparing given values and computed values:-\n");
	printf("Given x\t\t\tGiven y\t\t\tComputed y\n");
	for(int i=0; i<n; i++)
		printf("%lf\t\t\t%lf\t\t\t%lf\n", X[i], Y[i], eval_pol(coeff, n-1, X[i]));
	free(X); free(Y); free(theta);
	myfree(A, n, n); myfree(tmp, n, n);
}
