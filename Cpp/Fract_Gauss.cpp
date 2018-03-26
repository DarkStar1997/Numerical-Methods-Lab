#pragma once
#include <gmpxx.h>
#include "Fraction.hpp"
#include <vector>
template<typename T>
int upper_triangular(std::vector<std::vector<Fract<T>>> &arr, int m, int n)
{
    int sign=1;
    for(int i=0; i<m; i++)
    {
        Fract<T> max(rmg::abs(arr[i][i].first), arr[i][i].second); int pos=i;
        for(int j=i+1; j<m; j++)
            if(arr[j][i].first!=0)
            {
                max=Fract<T>(rmg::abs(arr[j][i].first), arr[j][i].second); pos=j;
                break;
            }
        if(pos!=i)
        {
            swap(arr[i], arr[pos]);
            sign=-sign;
        }
        if(max.first==0)
            return 0;
        for(int j=i+1; j<m; j++)
        {
            Fract<T> x=arr[j][i]/arr[i][i];
            for(int k=i; k<n; k++)
                arr[j][k]=arr[j][k]-x*arr[i][k];
        }
    }
    return sign;
}
int main()
{
    using data=mpz_class;
    std::cout<<"Enter the number of unknowns\n";
    int n; std::cin>>n;
    std::vector<std::vector<Fract<data>>> Aug(n, std::vector<Fract<data>>(n+1));
    std::string str;
    std::cout<<"Enter the coefficient matrix:\n";
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            std::cin>>str;
            Aug[i][j]=rmg::process<data>(str);
        }
    std::cout<<"Enter the solution vector:\n";
    for(int i=0; i<n; i++)
    {
        std::cin>>str;
        Aug[i][n]=rmg::process<data>(str);
    }
    if(upper_triangular(Aug, n, n+1))
    {
        std::vector<Fract<data>> X(n);
        for(int i=n-1; i>=0; i--)
        {
            Fract<data> sum(0,1);
            for(int j=n-1; j>i; j--)
                sum=sum+(X[j]*Aug[i][j]);
            X[i]=(Aug[i][n]-sum)/Aug[i][i];
        }
        std::cout<<"Required solution vector:\n";
        for(int i=0; i<n; i++)
            std::cout<<X[i]<<"\n";
    }
    else
        std::cout<<"Unique solution not possible\n";
}