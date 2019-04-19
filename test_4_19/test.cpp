#include <iostream>
using namespace std;
class Test
{
public:
  int pub;

protected:
  int pro;

private:
  int pri;
};

//int main()
//{
//  Test t;
//  t.pub = 4;
//  return 0;
//}

class A
{
public:
  void Print()
  {
    cout<<a<<endl;
  }

private:
  int a;
};

int main()
{
  cout<<sizeof(A)<<endl;
  return 0;
}
