#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
int main()
{
	printf("Enter the length of the matrices\n");
	int n; scanf("%d", &n);
	double **a=allocate(n, n);
	double **b=allocate(n, n);
	printf("Enter the values of matrix A:\n");
	input(a, n, n);
	printf("Enter the values of matrix B:\n");
	input(b, n, n);
	double **ans1=add(a, b, n, n);
	printf("A+B=\n");
	print(ans1, n, n);
	double **ans2=subtract(a, b, n, n);
	printf("A-B=\n");
	print(ans2, n, n);
	double **ans3=multiply(a, b, n, n, n);
	printf("A*B=\n");
	print(ans3, n, n);
	double **ans4=transpose(a, n, n);
	printf("transpose(A)=\n");
	print(ans4, n, n);
	myfree(a, n, n);	myfree(b, n, n);	myfree(ans1, n, n);
	myfree(ans2, n, n);	myfree(ans3, n, n);	myfree(ans4, n, n);
}
