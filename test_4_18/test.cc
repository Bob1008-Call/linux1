#include <iostream>
class Base
{
public:
  int a;
  virtual void A(){ std::cout<<"Base::A"<<std::endl; }
  virtual void B(){ std::cout<<"Base::B"<<std::endl; }
  virtual void C(){ std::cout<<"Base::C"<<std::endl; }
};

int main()
{
  std::cout<<sizeof(Base)<<std::endl;
  return 0;
}



