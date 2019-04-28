#include <iostream>
using namespace std;

class Base
{
public:
  virtual void Func1()
  {
    cout<<"Func1()"<<endl;
  }
private:
  int _b;
};

int main()
{
  cout<<sizeof(Base)<<endl;
  return 0;
}
