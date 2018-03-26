#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include<math.h>
int check(double **A, int n)
{
	for(int i=0; i<n; i++)
	{
		double ans=A[i][0], sum=fabs(ans); int pos=i;
		for(int j=1; j<n; j++)
		{
			if(fabs(ans)<fabs(A[i][j]))
			{
				ans=A[i][j];
				pos=j;
			}
			sum=sum+fabs(A[i][j]);
		}
		if(fabs(ans)<sum-fabs(ans))
			return 0;
		else
		{
			if(pos!=i)
				swap(&A[i], &A[pos]);
		}
	}
	return 1;
}
double run(double *X, double **A, double *B, int n)
{
	double tmp;
	for(int i=0; i<n; i++)
	{
		double sum=0;
		for(int j=0; j<n; j++)
			if(j==i)
				continue;
			else
				sum=sum+A[i][j]*X[j];
		tmp=X[i];
		X[i]=(B[i]-sum)/A[i][i];
	}
	return tmp;
}
void main()
{
	printf("Enter the number of unknowns\n");
	int n; scanf("%d", &n);
	double **A=allocate(n, n);
	double *B=(double*)malloc(n*sizeof(double));
	double *X=(double*)malloc(n*sizeof(double));
	printf("Enter the coefficients:\n");
	input(A, n, n);
	printf("Enter the column vector\n");
	for(int i=0; i<n; i++)
		scanf("%lf", B+i);
	printf("Enter the number of digits to be calculated after the decimal point (<=9)\n");
	int digits; scanf("%d", &digits);   long d=(long)pow(10,digits);
	char disp_str[]="%.xlf\n"; disp_str[2]=digits+'0';
	//char disp_str[]="%.10lf\n";
	if(check(A, n))
	{
		double tmp=run(X, A, B, n);
		printf("After iteration %d, the values are:\n", 1);
		for(int j=0; j<n; j++)
			printf(disp_str, X[j]);
		printf("****         %lf\n", fabs(tmp*d-X[n-1]*d));
		for(int i=2; fabs(tmp*d-X[n-1]*d)>1.0; i++)
		{
			printf("****         %lf\n", fabs(tmp*d-X[n-1]*d));
			tmp=run(X, A, B, n);
			printf("After iteration %d, the values are:\n", i);
			for(int j=0; j<n; j++)
				printf(disp_str, X[j]);
		}
		printf("****         %lf\n", fabs(tmp*d-X[n-1]*d));
	}
	else
		printf("System of equations not diagonally dominant\n");
	myfree(A, n, n);
	free(B); free(X);
}
