#include <iostream>
using namespace std;

class A
{
public:
  void Print()
  {
    cout<<_a<<endl;
  }
  
  void Show()
  {
    cout<<"Show()"<<endl;
  }
private:
  int _a;
};

int main()
{
  A* p = NULL;
  p->Show();
  return 0;
}
