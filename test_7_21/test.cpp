#include<iostream>

using namespace std;

class Base

{

public:

Base()

{

_data1 = 1;

}

virtual void FunTest1()

{

cout << "Base::FunTest1()" << endl;

}

private:

int _data1;

};

class C1 :virtual public  Base

{

public:

C1()

{

_data2 = 2;

}

virtual void FunTest2()

{

cout << "C1::FunTest2()" << endl;

}

private:

int _data2;

};

class C2 : virtual public Base

{

public:

C2()

{

_data3 = 3;

}

virtual void FunTest3()

{

cout << "C2::FunTest3()" << endl;

}

int _data3;

};

class Derived :public C1, public C2

{

public:

Derived()

{

_data4 = 4;

}

virtual void FunTest4()

{

cout << "Derived::FunTest4()" << endl;

}

int _data4;

};


void SizeTest()
{
  cout << sizeof(Base) << endl;
  cout << sizeof(C1) << endl;
  cout << sizeof(c2) << endl;
  cout << sizeof(Derived) << endl;
}
int main()

{

  SizeTest();

return 0;

}
