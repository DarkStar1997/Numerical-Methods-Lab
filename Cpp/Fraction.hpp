#include <iostream>
#include <utility>
#include <string>
template<typename T>
struct Fract;
namespace rmg
{
    template<typename T>
    T gcd(T x, T y)
    {
        if(y==0)
            return x;
        T z;
        while((z=x%y)!=0)
        {
            x=y;
            y=z;
        }
        return y;
    }
    template<typename T>
    T lcm(T x, T y)
    {
        if(x==0 && y==0)
            return 0;
        return x*y/gcd<T>(x, y);
    }
    template<typename T>
    inline T abs(const T& x)
    {
        T y=x<0?-x:x;
        return y;
    }
    template<typename T>
    Fract<T> process(const std::string&);
}
template<typename T>
struct Fract
{
    T first, second;
    Fract()
    {
        first=0;
        second=1;
    }
    Fract(T x, T y)
    {
        first=x;
        second=y;
        reduce();
    }
    void reduce()
    {
        T a=rmg::gcd(rmg::abs(first), rmg::abs(second));
        first/=a;
        second/=a;
        if(first==0)
            second=1;
        if((first<0 && second<0) || second<0)
        {
            first=-first;
            second=-second;
        }
    }
    Fract<T> operator+(const Fract<T> &y)
    {
        T denom=rmg::lcm(rmg::abs(second), rmg::abs(y.second));
        T num=(denom/second)*first+(denom/y.second)*y.first;
        Fract<T> ans=Fract<T>(num, denom);
        ans.reduce();
        return ans;
    }
    Fract<T> operator-(const Fract<T> &y)
    {
        T denom=rmg::lcm(rmg::abs(second), rmg::abs(y.second));
        T num=(denom/second)*first-(denom/y.second)*y.first;
        Fract<T> ans=Fract<T>(num, denom);
        ans.reduce();
        return ans;
    }
    Fract<T> operator*(const Fract<T> &y)
    {
        T num=first*y.first;
        T denom=second*y.second;
        Fract<T> ans(num, denom);
        ans.reduce();
        return ans;
    }
    Fract<T> operator/(const Fract<T> &y)
    {
        T num=first*y.second;
        T denom=second*y.first;
        Fract<T> ans(num, denom);
        ans.reduce();
        return ans;
    }
    bool operator<(const Fract<T> &y)
    {
        return (first*y.second)<(second*y.first);
    }
    bool operator>(const Fract<T> &y)
    {
        return (first*y.second)>(second*y.first);
    }
    bool operator<=(const Fract<T> &y)
    {
        return (first*y.second)<=(second*y.first);
    }
    bool operator>=(const Fract<T> &y)
    {
        return (first*y.second)>=(second*y.first);
    }
    bool operator==(Fract<T> &y)
    {
        return (first*y.second)==(second*y.first);
    }
    void abs()
    {
        first=rmg::abs(first);
        second=rmg::abs(second);
        reduce();
    }
};
template<typename T>
std::ostream& operator<<(std::ostream &out, Fract<T> &x)
{
    x.reduce();
    if(x.first!=0)
    {
        if(x.second!=1)
            out<<x.first<<"/"<<x.second;
        else
            out<<x.first;
    }
    else
        out<<0;
    return out;
}
template<typename T>
Fract<T> rmg::process(const std::string &str)
{
    auto pos=str.find('/', 0);
    bool flag=false;
    if(pos!=std::string::npos)
    {
        T num=0, denom=0;
        auto n=str.length();
        for(size_t i=0; i<n; i++)
        {
            if(str[i]=='-')
            {
                flag=true;
                continue;
            }    
            if(i==pos)
                continue;
            else if(i<pos)
                num=num*10+str[i]-'0';
            else
                denom=denom*10+str[i]-'0';
        }
        return Fract<T>(flag?-num:num, denom);            
    }
    else if((pos=str.find('.',0))==std::string::npos)
    {
        T num=0, denom=1;
        for(const auto& i:str)
            if(i=='-')
                flag=true;
            else
                num=num*10+i-'0';
        return Fract<T>(flag?-num:num, denom);
    }
    else
    {
        T num=0, denom=1;
        auto n=str.length();
        for(size_t i=0; i<n; i++)
        {
            if(i==pos)
                continue;
            if(str[i]=='-')
                flag=true;
            else
                num=num*10+str[i]-'0';
            if(i>pos)
                denom*=10;
        }
        return Fract<T>(flag?-num:num, denom);
    }
}