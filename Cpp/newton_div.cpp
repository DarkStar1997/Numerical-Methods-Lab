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
}