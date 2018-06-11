#include <gmpxx.h>
#include "Fraction.hpp"
#include <vector>
template <typename T>
T compute(std::vector<T> &a, std::vector<T> &x, size_t n, T &val)
{
    T ans=a[0], p=T(1);
    for(int i=1; i<n; i++)
    {
        p=p*(val-x[i-1]);
        ans=ans+a[i]*p;
    }
    return ans;
}
template<typename T>
void read(T &x)
{
    std::cin>>x;
}
template<typename T>
void read(Fract<T> &x)
{
    std::string tmp; std::cin>>tmp;
    x=rmg::process<mpz_class>(tmp);
}
template <typename T>
T eval_pol(std::vector<T> &pol, int degree, T point)
{
    T ans(0);
    for(int i=degree; i>=0; i--)
        ans=ans*point+pol[i];
    return ans;
}
int main()
{
    using type1=mpz_class;
    using type2=Fract<type1>;
    // using type1=double;
    // using type2=double;
    std::cout<<"Enter the number of points:\n";
    size_t n; std::cin>>n;
    std::vector<type2> x(n), y(n);
    std::cout<<"Enter the points as pairs (x,y)\n";
    for(int i=0; i<n; i++)
    {
        read<type1>(x[i]);
        read<type1>(y[i]);
    }
    std::vector<type2> coeff(n), tmp(n);
    coeff[0]=y[0];
    tmp[0]=y[0];
    for(int i=1; i<n; i++)
    {
        for(int j=0; j<n-i; j++)
        {
            type2 x_0, x_1;
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
    std::cout<<"Required coefficients:\n";
    for(auto& i:coeff)
        std::cout<<i<<'\n';
    std::cout<<"Enter the value to be computed\n";
    type2 tmp_x; read<type1>(tmp_x);
    tmp_x=compute<type2>(coeff, x, n, tmp_x);
    std::cout<<tmp_x<<'\n';
    std::vector<std::vector<type2>> A(n, std::vector<type2>(n));
    for(int i=0; i<n; i++)
		if(i==0)
			A[0][i]=type2(1);
		else
			A[0][i]=-x[i-1];
	for(int i=0; i<n; i++)
		if(i==0)
			A[1][i]=type2(0);
		else
			A[1][i]=type2(1);
	for(int i=2; i<n; i++)
		for(int j=0; j<n; j++)
			A[i][j]=type2(0);
    std::vector<std::vector<type2> > Tmp=A;
    for(int i=1; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            std::vector<type2> t_tmp(2+i);
            for(int k=0; k<2+i; k++)
            {
                t_tmp[k]=Tmp[k][j];
                Tmp[k][j]=type2(0);
            }
            for(int l=0; l<=1; l++)
                for(int k=0; k+l<2+i; k++)
                    Tmp[k+l][j]=Tmp[k+l][j]+A[l][i]*t_tmp[k];
        }
    }
    std::vector<type2> coeff1(n);
    for(int i=0; i<n; i++)
    {
        coeff1[i]=type2(0);
        for(int j=i; j<n; j++)
            coeff1[i]=coeff1[i]+coeff[j]*Tmp[i][j];
    }
    std::cout<<"Formatted coefficients:\n";
    for(int i=0; i<n; i++)
    {
        std::cout<<coeff1[i];
        std::cout<<'\n';
    }
    std::cout<<"Comparing given values and computed values:-\n";
    std::cout<<"Given x\t\t\tGiven y\t\t\tComputed y\n";
    for(int i=0; i<n; i++)
    {
        std::cout<<x[i]; std::cout<<"\t\t\t";
        std::cout<<y[i]; std::cout<<"\t\t\t";
        type2 temp=eval_pol<type2>(coeff1, n-1, x[i]);
        std::cout<<temp; std::cout<<'\n';
    }
}