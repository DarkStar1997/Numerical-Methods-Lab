#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double fabs(double x)
{
    return x<0?-x:x;
}
double eval_pol(double *pol, int degree, double point)
{
	double ans=0;
	for(int i=degree; i>=0; i--)
		ans=ans*point+pol[i];
	return ans;
}
double* derivative(double *pol, int degree)
{
    double *pol1=(double*)malloc(degree*sizeof(double));
    for(int i=0; i<degree; i++)
        pol1[i]=(i+1)*pol[i+1];
    return pol1;
}
void main()
{
    int n; printf("Enter the degree of the polynomial\n");
    scanf("%d", &n);
    double *arr=(double*)malloc((n+1)*sizeof(double));
    printf("Enter the coefficients:\n");
    for(int i=0; i<=n; i++)
        scanf("%lf", arr+i);
    double a;
    printf("Enter the starting value:\n");
    scanf("%lf", &a);
    printf("Enter the number of digits after decimal point\n");
    int num; scanf("%d", &num);
    double eps=pow(10,-num);
    double *darr=derivative(arr, n);
    double h=eval_pol(arr, n, a)/eval_pol(darr, n-1, a);
    while(fabs(h)>=eps)
    {
        h=eval_pol(arr, n, a)/eval_pol(darr, n-1, a);
        a=a-h;
    }
    printf("Value of the root is: %.*lf\n", num, a);
    free(arr); free(darr);
}