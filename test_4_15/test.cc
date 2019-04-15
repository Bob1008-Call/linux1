#include <iostream>

using namespace std;

class Base {

public:

	int a;

	virtual void f() { cout << "Base::f" << endl; }

	virtual void g() { cout << "Base::g" << endl; }

	virtual void h() { cout << "Base::h" << endl; }
};

int main()
{
  cout<<sizeof(Base)<<endl;
}
