#include <iostream>

class Base
{
  static int a;
};

int a = 10;

class Derived: public Base
{
  static int a;
};

void Print()
{
  std::cout<<a<<std::endl;
}
int main()
{
  Print();
  return 0;
}
