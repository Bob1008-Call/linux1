#include <iostream>
using namespace std;
template<typename T1,typename T2>
class Data<T1,T2>
{
  public:
    Data();
  private:
    T1 _d1;
    T2 _d2;
    T1* _d3;
    T2* _d4;
};

template <class T1,class T2>
Data<T1, T2>::Data()
{
  cout << "Data<T1*,T2*>" <<endl;
}


