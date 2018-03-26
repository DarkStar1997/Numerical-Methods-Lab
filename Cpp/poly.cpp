#include <mpreal.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
using namespace std;
using mpfr::mpreal;
template<typename T>
vector<vector<T>> transpose(vector<vector<T>> &A, int m, int n)
{
	vector<vector<T>> At(n, vector<T>(m));
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			At[j][i]=A[i][j];
	return At;
}
template<typename T>
vector<vector<T>> extract(vector<vector<T>> &A, int n, int row, int col)
{
	vector<vector<T>> x(n-1, vector<T>(n-1)); int index=0;
	for(int i=0; i<n; i++)
	{
		if(i==row)
			continue;
		for(int j=0; j<n; j++)
		{
			if(j==col)
				continue;
			x[index/(n-1)][index%(n-1)]=A[i][j];
			index++;
		}
	}
	return x;
}
template<typename T>
int upper_triangular(vector<vector<T>> &arr, int m, int n)
{
	int sign=1;
	for(int i=0; i<m; i++)
	{
		T max=arr[i][i]>0?arr[i][i]:-arr[i][i]; int pos=i;
		for(int j=i+1; j<m; j++)
		{
			/*if(fabs(arr[j][i])>max)
			{
				max=fabs(arr[j][i]); pos=j;
			}*/
			if(arr[j][i]!=0)
			{
				max=arr[j][i]>0?arr[j][i]:-arr[j][i]; pos=j;
				break;
			}
		}
		if(pos!=i)
		{
			swap(arr[i], arr[pos]);
			sign=-sign;
		}
		if(max==0.0)
			return 0;
		for(int j=i+1; j<m; j++)
		{
			T x=arr[j][i]/arr[i][i];
			for(int k=i; k<n; k++)
				arr[j][k]=arr[j][k]-x*arr[i][k];
		}
	}
	return sign;
}
template<typename T>
T determinant(vector<vector<T>> arr, int n)
{
	T ans=1.0;
	int flag=upper_triangular(arr, n, n);
	if(flag!=0)
	{
		for(int i=0; i<n; i++)
			ans*=arr[i][i];
		ans*=flag;
	}
	else
		ans=0.0;
	return ans;
}
template<typename T>
vector<vector<T>> multiply( vector<vector<T>> a, vector<vector<T>> b, int m, int n, int k)
{
	vector<vector<T>> c(m, vector<T>(k));
	for(int i=0; i<m; i++)
		for(int j=0; j<k; j++)
		{
			c[i][j]=0;
			for(int l=0; l<n; l++)
				c[i][j]+=a[i][l]*b[l][j];
		}
	return c;
}
template<typename T>
vector<vector<T>> inverse(vector<vector<T>> A, int n)
{
	vector<vector<T>> Adj(n, vector<T>(n));
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			auto x=extract(A, n, i, j);
			auto y=determinant(x, n-1);
			if((i+j)&1)
				Adj[i][j]=-y;
			else
				Adj[i][j]=y; 
		}
	}
	auto inv=transpose(Adj, n, n);
	vector<vector<T>> Ac(n, vector<T>(n));
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			Ac[i][j]=A[i][j];
	auto det=determinant(Ac, n);
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			inv[i][j]/=det;
	return inv;
}
template<typename T>
T eval_pol(vector<vector<T>> pol, int degree, T point)
{
	T ans=0;
	for(int i=degree; i>=0; i--)
		ans=ans*point+pol[i][0];
	return ans;
}
int main()
{
	const int digits=50;
	mpreal::set_default_prec(mpfr::digits2bits(digits));
	cout.precision(50);
	cout<<"Enter the number of points\n";
	int n; cin>>n;
	cout<<"Enter the degree of the polynomial\n";
	int deg; cin>>deg;
	vector<vector<mpreal>> x(n, vector<mpreal>(deg+1, 0));
	vector<vector<mpreal>> y(n, vector<mpreal>(1, 0));
	cout<<"Enter the points\n";
	for(int i=0; i<n; i++)
		cin>>x[i][1]>>y[i][0];
	for(int i=0; i<n; i++)
		x[i][0]=1;
	for(int i=2; i<=deg; i++)
		for(int j=0; j<n; j++)
			x[j][i]=pow(x[j][1], i);
	auto xt=transpose<mpreal>(x, n, deg+1);
	auto tmp=multiply<mpreal>(xt, x, deg+1, n, deg+1);
	auto tmpi=inverse<mpreal>(tmp, deg+1);
	auto tmp1=multiply<mpreal>(tmpi, xt, deg+1, deg+1, n);
	auto theta=multiply<mpreal>(tmp1, y, deg+1, n, 1);
	cout<<"Required polynomial coefficients\n";
	for(int i=0; i<=deg; i++)
		cout<<theta[i][0]<<"\n";
	printf("Comparing given and values and computed values:-\n");
	printf("Given x\t\t\tGiven y\t\t\tComputed y\n");
	for(int i=0; i<n; i++)
		cout<<x[i][1]<<"\t\t"<<y[i][0]<<"\t\t"<<eval_pol<mpreal>(theta, deg, x[i][1])<<"\n";
}
