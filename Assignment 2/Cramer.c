#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"
int main()
{
	int n; printf("Enter the number of unknowns\n"); scanf("%d", &n);
	double **A=allocate(n,n);
	printf("Enter the coefficient matrix\n");
	input(A, n, n);
	printf("Enter the solution vector\n");
	double *B=(double*)malloc(n*sizeof(double));
	for(int i=0; i<n; i++)
		scanf("%lf", B+i);
	double **D=allocate(n, n); copyOf(A, D, n, n);
	double d=determinant(D, n);
	if(d==0.0)
		printf("Unique solution not possible\n");
	else
	{
		double *X=(double*)malloc(n*sizeof(double));
		for(int i=0; i<n; i++)
		{
			copyOf(A, D, n, n); column_replace(D,n,B,i);
			X[i]=determinant(D, n)/d;
		}
		printf("Required solution vector:-\n");
		for(int i=0; i<n; i++)
			printf("X%d=%lf\n", i, X[i]);
		free(X);
	}
	myfree(A, n, n); free(B); myfree(D, n, n);
	return 0;
}
