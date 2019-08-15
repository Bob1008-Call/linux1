#include <iostream>
using namespace std;
bool IsPrime(int n) //是否是质数
{
    bool Is = false;
    if(n == 1 || n == 2)
    {
        return Is;
    }
    for(int i = 3;i<n;++i)
    {
        if(n != i && n%i == 0)
        {
            Is = true;
        }
    }
    return Is;
}

int Greatest_divisor(int max,int min)//求最小公倍数
{

    int Remain = max%min;
    if(Remain == 0)
    {
        return min;
    }
    return Greatest_divisor(min,Remaind);
}

int main()
{
    int m,n;
    cin>>m;
    cin>>n;
    if(m == n)
    {
        cout<<m<<endl;
    }
    if(m>n)
    {
        int result = m*n/(Greatest_divisor(m,n));
        cout<<result<<endl;
    }
    if(m<n)
    {
        int result = m*n/(Greatest_divisor(n,m));
        cout<<result<<endl;
    }
    return 0;
}

