#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
int main()
{
	printf("Enter the number of unknowns\n");
	int n; scanf("%d", &n);
	double **Aug=allocate(n, n+1);
	printf("Enter the coefficient matrix\n");
	input(Aug, n, n);
	printf("Enter the solution vector\n");
	for(int i=0; i<n; i++)
		scanf("%lf", &Aug[i][n]);
	int flag=upper_triangular(Aug, n, n+1);
	if(flag)
	{
		double *X=(double*)malloc(n*sizeof(double));
		for(int i=n-1; i>=0; i--)
		{
			double sum=0.0;
			for(int j=n-1; j>i; j--)
				sum=sum+(X[j]*Aug[i][j]);
			X[i]=(Aug[i][n]-sum)/Aug[i][i];
		}
		printf("Required solution vector:-\n");
		for(int i=0; i<n; i++)
			printf("X%d=%lf\n", i, X[i]);
		free(X);
	}
	else
		printf("Unique solution not possible\n");
	myfree(Aug, n, n+1);
}
