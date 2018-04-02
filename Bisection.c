#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double eval_pol(double *pol, int degree, double point)
{
	double ans=0;
	for(int i=degree; i>=0; i--)
		ans=ans*point+pol[i];
	return ans;
}
void main()
{
    int n; printf("Enter the degree of the polynomial\n");
    scanf("%d", &n);
    double *arr=(double*)malloc((n+1)*sizeof(double));
    printf("Enter the coefficients:\n");
    for(int i=0; i<=n; i++)
        scanf("%lf", arr+i);
    double a, b;
    printf("Enter the lower and upper limits:\n");
    scanf("%lf %lf", &a, &b);
    printf("Enter the numer of digits after decimal point:\n");
    int num; scanf("%d", &num);
    double eps=pow(10,-num);
    double c=a;
    while((b-a)>=eps)
    {
        c=a+(b-a)/2;
        if(eval_pol(arr, n, c)==0)
            break;
        else if(eval_pol(arr, n, c)*eval_pol(arr, n, a)<0)
            b=c;
        else
            a=c;
    }
    printf("Value of the root is: %.*lf\n", num, c);
    free(arr);
}